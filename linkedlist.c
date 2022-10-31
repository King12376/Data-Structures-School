#include<stdio.h>
#include <stdlib.h>
struct Node     //defining  node struct with two pointers prev and next
{
    int data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)//initialiazing the head to Null (list is empty)
{
    (*head) = NULL;
}

void addToHead(struct Node **head, int data) //first check if head is empty 
{
    if ((*head) == NULL)
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));//dynamically allocate memory(create new node and set it to be the head)
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));//if a head already exists(create a new node)
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        (*head)->prev = newNode;//set newNode to be head's prev
        newNode->next = (*head);//link newNode to the head by setting it's next to point to the head
        (*head) = (*head)->prev;//set newNode to be the head.
    }
}

void addToTail(struct Node **head, int data)
{
    if ((*head) == NULL)//check if list is empty
    {
        (*head) = (struct Node *)malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));//if head already exists then create new node
        newNode->next = NULL;
        newNode->prev = NULL;
        newNode->data = data;

        struct Node *cur = (*head); //define a pointer cur that we will use to iterate over the list until we reach the end of the list
        while (cur->next != NULL)
            cur = cur->next; //set our cur pointer to the next node
        cur->next = newNode;
        newNode->prev = cur;
    }
}
void deleteData(struct Node **head, int data)
{
 if( *head == NULL )
        return;
    
    struct Node *cur = *head;
    
    while( cur != NULL){
        if(cur->data == data){
            break;
        }
        cur = cur->next;
    }
    
    if( cur == NULL )
        return;
    else{
        if( cur->next == NULL ){
            free( cur );
            *head == NULL;
        }
        if( cur->prev == NULL ){
            *head = cur->next;
            (*head)->prev = NULL;
            free( cur );
        }
        if( cur->next == NULL ){
            cur->prev == NULL;
            free( cur );
        }
        else{
            cur->prev->next = cur->next;
            cur->next->prev =  cur->prev;
            free( cur );
        }
    }

}

void deleteDatas(struct Node **head, int data, int n)
{
  	for( int i = 0; i < n; ++i ) {
    	deleteData(head, data);
    }  
}


void display(struct Node *head)
{
    struct Node *cur = head; //define current pointer and set it to be the head
    printf("(");
    printf("%d", cur->data); //first print the data cur is pointing to and set cur to the next node
    cur = cur->next;
    while (cur != NULL)
    {
        printf(", %d", cur->data);
        cur = cur->next;
    }
    printf(")\n");
}