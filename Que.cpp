#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    Node()
    {
        this->prev = nullptr;
        this->next = nullptr;
    }

    Node(T data)
    {
        this->prev = nullptr;
        this->next = nullptr;
        this->data = data;
    }

    Node(T data, Node<T> *prev, Node<T> *next)
    {
        this->prev = prev;
        this->next = next;
        this->data = data;
        if (prev)
            prev->setNext(this);
        if (next)
            next->setPrev(this);
    }

    T getData()
    {
        return this->data;
    }

    Node *getNext()
    {
        return this->next;
    }

    Node *getPrev()
    {
        return prev;
    }

    void setData()
    {
        this->data = data;
    }

    void setNext(Node<T> *n)
    {
        next = n;
    }

    void setPrev(Node<T> *n)
    {
        prev = n;
    }

private:
    Node<T> *prev;
    Node<T> *next;
    T data;
};

template <class T>
class LinkedList
{
public:
    /**
     * Construct a new LinkedList object with no parameter
     */
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(T data)
    {
        Node<T> *newNode = new Node<T>(data);
        head = newNode;
        tail = newNode;
    }

    void addToTail(T data)
    {
        // check if it is the first node of the linkedList to be created
        if (tail == NULL)
        {
            // create a new node and assign it data
            Node<T> *newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
        }
        else
        {
            // node to be added to tail
            Node<T> *newNode = new Node<T>(data);
            // next of tail must point to new node
            tail->setNext(newNode);
            // newNode must point to tail
            newNode->setPrev(tail);
            // make the new node the tail by pointing tail to newNode
            tail = newNode;
        }
    }

    /**
     * Add a node to the head of the linked list
     * @param data: data to put in
     */
    void addToHead(T data)
    {
        if (head == nullptr)
        {
            // create a new node and assign it data
            Node<T> *newNode = new Node<T>(data);
            head = newNode;
            tail = newNode;
        }
        else
        {
            // node to be added to head
            Node<T> *newNode = new Node<T>(data);
            // point prev of head to newNode
            head->setPrev(newNode);
            // newNode next point to head
            newNode->setNext(head);
            // make the new node the head by pointing head to newNode
            head = newNode;
        }
    }

    void addBetween(T data, T data1, T data2)
    {
        Node<T> *previous = this->getNode(data1);
        Node<T> *next = this->getNode(data2);
        if (previous && next)
        {
            if (previous->getNext() == next)
            {
                Node<T> *newNode = new Node<T>(data, previous, next);
                cout << "inserted succesfully!\n";
            }
        }
        else
        {
            cout << "One or more nodes could not be found!\n";
        }
    }

    // getter for head
    Node<T> *getHead()
    {
        return this->head;
    }

    // getter for tail
    Node<T> *getTail()
    {
        return this->tail;
    }

    // helper to get ba particular node by its data
    Node<T> *getNode(T data)
    {
        Node<T> *node = this->head;
        while (node != nullptr)
        {
            if (node->getData() == data)
                return node;
            node = node->getNext();
        }
        return NULL;
    }
    /**
     * Delete a node from the linked list with the given data from the head
     * If there are no data to be deleted, then do nothing
     * @param data: data to delete
     */
    void deleteData(T data)
    {
        // delete node with value = data if found
        // if not found, do nothing
        // if nodes from head to tail are deleted, set head and tail to null
        Node<T> *node = this->head;
        while (node != nullptr)
        {
            if (node->getData() == data)
            {
                if (node == head)
                {
                    if (node->getNext() == nullptr)
                    {
                        head = nullptr;
                        tail = nullptr;
                    }
                    else
                    {
                        head = node->getNext();
                        head->setPrev(nullptr);
                    }
                }
                else if (node == tail)
                {
                    if (node->getPrev() == nullptr)
                    {
                        head = nullptr;
                        tail = nullptr;
                    }
                    else
                    {
                        tail = node->getPrev();
                        tail->setNext(nullptr);
                    }
                }
                else
                {
                    node->getPrev()->setNext(node->getNext());
                    node->getNext()->setPrev(node->getPrev());
                }
                delete node;
                return;
            }
            node = node->getNext();
        }
    }

    /**
     * Delete valid n nodes from the linked list with the given data from the head
     * If there are no more data to be deleted, then just skip
     * @param data: data to delete
     * @param n: max number of nodes to delete
     */
    void deleteData(T data, int n)
    {
        // delete n nodes with value = data if found
        // if not found, do nothing
        // if node is head, set head to next node or null if no next node
        // if node is tail, set tail to prev node or null if no prev node
        // if nodes from head to tail are deleted, set head and tail to null
        Node<T> *node = this->head;
        while (node != nullptr && n > 0)
        {
            if (node->getData() == data)
            {
                if (node == head)
                {
                    head = node->getNext();
                    head->setPrev(nullptr);
                }
                else if (node == tail)
                {
                    tail = node->getPrev();
                    tail->setNext(nullptr);
                }
                else
                {
                    node->getPrev()->setNext(node->getNext());
                    node->getNext()->setPrev(node->getPrev());
                }
                Node<T> *temp = node;
                node = node->getNext();
                delete temp;
                n--;
            }
            else
            {
                node = node->getNext();
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList *n)
    {
        if (!n)
        {
            out << "()\n";
            return out;
        }
        Node<T> *listIter = n->head;
        out << "(";
        while (listIter)
        {
            out << listIter->getData();
            listIter = listIter->getNext();
            if (listIter)
                out << ", ";
            else
                break;
        }

        out << ")" << endl;

        return out;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

/**
 * A Queue class
 */
template <class T>
class Queue
{
public:
    /**
     * Construct a new Queue object with no parameter
     */
    Queue()
    {
        this->list = new LinkedList<T>();
    }

    /**
     * Add a data to queue
     * @param data: data to be added to queue
     */
    void enqueue(T data)
    {
        this->list->addToTail(data);
    }

    /**
     * Remove a data from queue and return it if it is not empty
     * @return the data removed from queue
     */
    T dequeue()
    {
        if (isEmpty())
            return 0;
        T data = this->list->getHead()->getData();
        this->list->deleteData(data);
        return data;
    }
    /**
     * @return the first element in the queue if not empty
     * @return NULL if queue is empty
     */
    T front()
    {
        if (isEmpty())
            return NULL;
        return this->list->getHead()->getData();
    }

    /**
     * @return true if queue is empty, false otherwise
     */
    bool isEmpty()
    {
        return this->list->getHead() == nullptr;
    }

    //inherit << operator from LinkedList
    friend std::ostream &operator<<(std::ostream &out, Queue *n)
    {
        out << n->list;
        return out;
    }
    

private:
    LinkedList<T> *list;
};
/*
int main(){
    //create a queue
    Queue<int> *queue = new Queue<int>();
    //add 5, 6, 7, 8 to the queue
    queue->enqueue(5);
    queue->enqueue(6);
    queue->enqueue(7);
    queue->enqueue(8);
    //print the queue
    cout << queue << endl;
    //remove 2 elements from the queue
    queue->dequeue();
    queue->dequeue();
    queue->dequeue();
    queue->dequeue();
    //print the queue
    cout << queue << endl;
}
*/


