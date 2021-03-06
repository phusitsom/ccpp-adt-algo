#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    int size;
} LinkedList;

Node *new_node(int data)
{
    Node *node = NULL;
    node = (Node *)malloc(sizeof(Node *));
    node->data = data;
    node->next = NULL;

    return node;
}

LinkedList *new_linkedlist()
{
    LinkedList *list = NULL;
    list = (LinkedList *)malloc(sizeof(LinkedList *));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

Node *get_node(LinkedList *list, int index)
{

    if (list->head == NULL || index < 0 || index > list->size)
    {
        return NULL;
    }

    if (index == 0)
    {
        return list->head;
    }

    if (index == list->size - 1)
    {
        return list->tail;
    }

    Node *curr_node = list->head;

    for (int i = 0; i < index; ++i)
        curr_node = curr_node->next;

    return curr_node;
}

int get(LinkedList *list, int index) { return get_node(list, index)->data; }

void set(LinkedList *list, int index, int data)
{
    if (index < 0 || index > list->size - 1)
        return;

    get_node(list, index)->data = data;
}

void append(LinkedList *list, int data)
{
    Node *node = new_node(data);
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->size = 1;
        return;
    }
    list->tail->next = node;
    list->tail = node;
    ++list->size;
}

void insert(LinkedList *list, int index, int data)
{
    if (index < 0 || index > list->size)
    {
        return;
    }

    if (index == list->size)
    {
        append(list, data);
        return;
    }

    Node *node = new_node(data);
    if (index == 0)
    {
        node->next = list->head;
        list->head = node;
        ++list->size;
        return;
    }

    Node *curr_node = list->head;
    for (int i = 0; i < index - 1; i++)
    {
        curr_node = curr_node->next;
    }
    node->next = curr_node->next;
    curr_node->next = node;
    ++list->size;
}

int sum(LinkedList *list)
{
    int total = 0;
    Node *curr_node = list->head;
    while (curr_node != NULL)
    {
        total += curr_node->data;
        curr_node = curr_node->next;
    }
    return total;
}

void display(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("\n");
        return;
    }
    Node *curr_node = list->head;
    while (curr_node != NULL)
    {
        printf("%d", curr_node->data);
        curr_node = curr_node->next;
        if (curr_node != NULL)
        {
            printf("-> ");
        }
    }
    printf("\n");
}

void display_from_node(Node *node)
{
    if (node == NULL)
    {
        printf("\n");
        return;
    }
    while (node != NULL)
    {
        printf("%d", node->data);
        node = node->next;
        if (node != NULL)
        {
            printf("-> ");
        }
    }
    printf("\n");
}

void display_info(LinkedList *list)
{
    display(list);
    printf("size: %d\n", list->size);
}

int search(LinkedList *list, int data)
{
    int i = 0;
    Node *curr_node = list->head;
    while (curr_node != NULL)
    {
        if (curr_node->data == data)
        {
            return i;
        }
        curr_node = curr_node->next;
        ++i;
    }
    return -1;
}

Node *search_node(LinkedList *list, int data)
{
    int i = 0;
    Node *curr_node = list->head;
    while (curr_node != NULL)
    {
        if (curr_node->data == data)
        {
            return curr_node;
        }
        curr_node = curr_node->next;
        ++i;
    }
    return NULL;
}

int pop(LinkedList *list, int index)
{
    int data;

    if (index < 0 || index > list->size)
    {
        return data;
    }

    Node *curr_node = list->head;

    if (index == 0)
    {
        data = curr_node->data;
        list->head = curr_node->next;
        free(curr_node);
        --list->size;
        return data;
    }

    Node *prev_node = NULL;

    for (int i = 0; i < index; i++)
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    prev_node->next = curr_node->next;
    data = curr_node->data;
    free(curr_node);
    --list->size;
    return data;
}

int remove_item(LinkedList *list, int data)
{
    int index;
    Node *prev_node = NULL;
    Node *curr_node = list->head;

    if (curr_node->data == data)
    {
        list->head = curr_node->next;
        free(curr_node);
        --list->size;
        return 1;
    }

    while (curr_node != NULL)
    {
        if (curr_node->data == data)
            break;
        prev_node = curr_node;
        curr_node = curr_node->next;
        ++index;
    }

    if (curr_node == NULL)
    {
        return 0;
    }

    prev_node->next = curr_node->next;
    free(curr_node);
    --list->size;
    return 1;
}

void bubble_sort(LinkedList *list)
{
    struct Node *curr_node;
    struct Node *end_node = NULL;
    int temp_data;
    int swap;

    if (list->head == NULL)
        return;

    do
    {
        swap = 0;
        curr_node = list->head;

        while (curr_node->next != end_node)
        {
            if (curr_node->data > curr_node->next->data)
            {
                temp_data = curr_node->data;
                curr_node->data = curr_node->next->data;
                curr_node->next->data = temp_data;
                swap = 1;
            }
            curr_node = curr_node->next;
        }
        end_node = curr_node;
    } while (swap);
}

void reverse(LinkedList *list)
{
    Node *prev_node = NULL;
    Node *curr_node = list->head;
    Node *next_node = NULL;

    while (curr_node != NULL)
    {
        next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    list->head = prev_node;
}