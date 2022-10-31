#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};
void initLinkList(struct Node **head)
{
    *head = NULL;
}
void addToHead(struct Node **head, int data)
{
    if( (*head) == NULL ){
        (*head) = malloc( sizeof( struct Node ) );
        (*head)->data = data;
        (*head)->next = (*head)->prev = NULL;
    }

    else{
        struct  Node *newNode = malloc( sizeof( struct Node ) );
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = (*head);
        (*head)->prev = newNode;
        (*head) = newNode;
    }
}
void addToTail(struct Node **head, int data)
{
    if( *head == NULL ){
        *head = malloc( sizeof( struct Node ) );
        (*head)->data = data;
        (*head)->next = (*head)->prev = NULL;
    }

    else{
        struct Node *tail = (*head);
        while( tail->next != NULL )
            tail = tail->next;

        struct  Node *newNode = malloc( sizeof( struct Node ) );
        newNode->data = data;
        newNode->prev = tail;
        newNode->next = NULL;
        tail->next = newNode;
    }

}
void deleteData(struct Node **head, int data)
{
    struct Node *temp = *head, *h = NULL;
    int i = 0;
    while( temp != NULL ){
        if( temp->data == data ){
            if( temp == *head && temp->next == NULL ){      // if data is in head and head is the only node
                free(temp);
                *head = NULL;
            }
            else if( temp == *head ){
                temp = temp->next;
                free( temp->prev );
                (*head) = temp;
                temp->prev = NULL;
            }
            else if( temp->next == NULL ){
                temp = temp->prev;
                free( temp->next );
                temp->next = NULL;
            }
            else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free( temp );
            }

            break;
        }
        temp = temp->next;
    }
}
void deleteDatas(struct Node **head, int data, int n)
{
    struct Node *temp = *head, *h = NULL;
    int i = 0;
    while( temp != NULL && n > 0 ){
        if( temp->data == data ){
            if( temp == *head && temp->next == NULL ){      // if data is in head and head is the only node
                free(temp);
                *head = NULL;
                break;
            }
            else if( temp == *head ){       // if node is head and follows more nodes
                temp = temp->next;
                free( temp->prev );
                temp->prev = NULL;
                (*head) = temp;
            }
            else if( temp->next == NULL ){      // if node is tail
                temp = temp->prev;
                free( temp->next );
                temp->next = NULL;
                temp = NULL;
            }
            else                                    // if node is anywhere after and before the tail
            {                           
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                h = temp->next;
                free( temp );
                temp = h;
            }
            n--;
            continue;
        }
        temp = temp->next;
    }
}
void display( struct Node *head )
{
    struct Node *temp = head;
    printf("(");
    while( temp != NULL ){
        printf("%d", temp->data );
        if( temp->next != NULL )
            printf(", ");
        
        temp = temp->next;
    }

    printf(")\n");
}
void push(struct Node **stack, int data)
{
    addToHead( stack, data );
}
int pop(struct Node **stack)
{
    int temp = (*stack)->data;
    deleteData( stack, temp );

    return temp;
}
int top(struct Node *stack)
{
    return stack->data;
}
int isEmpty(struct Node *stack)
{
    if( stack == NULL )
        return 1;
    
    return 0;
}

int size(struct Node *stack)
{
    if( stack != NULL )
        return 1 + size( stack->next ); 
    
    return 0;
    
}


void moveDisksBetweenTwoPoles( struct Node **src, struct Node **dest)
{
    if ( size( *src ) == 0 )
    {
        push( src, pop( dest ) );
    }
    else if ( size( *dest ) == 0 )
    {
        push( dest, pop( src ) );
    }
    else if ( top( *src ) > top( *dest ) )
    {
        push( src, pop( dest ) );
    }
    else
    {
        push( dest, pop( src ) );
    }
}
 
void solveTheGame( int num_of_disks, struct Node **src, struct Node **aux, struct Node **dest )
{
    int i;
    struct Node **destReference = dest;
    int flagSwaped = 0;

    if ( num_of_disks % 2 == 0)
    {
        flagSwaped = 1;

        struct Node **t = dest;
        dest = aux;
        aux = t;
    }

    for (i = num_of_disks; i > 0 ; i--){
        push( src, i);
    }

    int q;
    
    for (i = 1; size( *destReference ) != num_of_disks; i++)
    {
        if (i % 3 == 1)
            moveDisksBetweenTwoPoles(src, dest);

        else if (i % 3 == 2)
            moveDisksBetweenTwoPoles(src, aux);
            
        else if (i % 3 == 0)
            moveDisksBetweenTwoPoles(dest, aux);
    }
    
    printf("%d\n", i-1);

}

int main()
{
    int nOfDisks;
    while( scanf("%d", &nOfDisks) != EOF ){
        // scanf("%d", &nOfDisks);
        struct Node *src, *aux, *dest;
        src = aux = dest = NULL;

        solveTheGame( nOfDisks, &src, &aux, &dest);
    }

    return 0;
}