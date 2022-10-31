#include<stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
    (*head) = NULL;
}

void addToHead(struct Node **head, int data)
{
    if ((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        (*head)->prev = newNode;
        newNode->next = (*head);
        (*head) = (*head)->prev;
    }
}

void addToTail(struct Node **head, int data)
{
    if ((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        struct Node *cur = (*head);
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = newNode;
        newNode->prev = cur;
    }
}

void deleteData(struct Node **head, int data)
{

    struct Node *cur = (*head);
    while (cur != NULL)
    {
        if (cur->data == data)
        {
            if (cur->next == NULL && cur->prev == NULL)
            {
                (*head) = NULL;
                return;
            }
            if (cur->prev != NULL)
                cur->prev->next = cur->next;
            else
            {
                (*head) = cur->next;
                cur->next->prev = NULL;
            }
            if (cur->next != NULL)
                cur->next->prev = cur->prev;
            else
            {
                cur = cur->prev;
                cur->next = NULL;
            }
            break;
        }
        cur = cur->next;
    }
}

void deleteDatas(struct Node **head, int data, int n)
{
    if (n != 0)
    {
        deleteData(head, data);
        deleteDatas(head, data, n - 1);
    }
}

void display(struct Node *head)
{
    struct Node *cur = head;
    printf("(");
    printf("%d", cur->data);
    cur = cur->next;
    while (cur != NULL)
    {
        printf(", %d", cur->data);
        cur = cur->next;
    }
    printf(")\n");
}

void enqueue(struct Node **queue, int data)
{
    addToTail(queue, data);
}

int dequeue(struct Node **queue)
{
    int n = (*queue)->data;
    deleteData(queue, (*queue)->data);
    return n;
}

int front(struct Node *queue)
{
    return queue->data;
}

int isEmpty(struct Node *queue)
{
    if (queue == NULL)
        return 1;
    return 0;
}