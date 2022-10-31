#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

template <class T>
class Node
{
public:
    Node() : data(), prev(), next() {}
    Node(T d) { data = d; }
    Node(T d, Node<T> *p, Node<T> *n)
    {
        data = d;
        prev = p;
        next = n;
    }

    bool setPrev(Node<T> *p)
    {
        this->prev = p;
        return true;
    }

    bool setNext(Node<T> *n)
    {
        this->next = n;
        return true;
    }
    // newly added to set current node
    bool setData(T d)
    {
        this->data = d;
        return true;
    }

    T getData()
    {
        return this->data;
    }

    Node<T> *getNext()
    {
        return this->next;
    }

    Node<T> *getPrev()
    {
        return this->prev;
    }

private:
    Node<T> *prev = NULL;
    Node<T> *next = NULL;
    T data{};
};

template <class T>
class LinkedList
{
public:
    LinkedList() : head(NULL), tail(NULL) {}

    void addToTail(T data)
    {
        if (this->head != NULL)
        {
            Node<T> *newTail = new Node<T>(data, this->tail, NULL);
            this->tail->setNext(newTail);
            this->tail = newTail;
        }
        else
        {
            this->head = this->tail = new Node<T>(data, NULL, NULL);
        }
    }

    void addToHead(T data)
    {
        if (this->head == NULL)
            this->tail = this->head = new Node<T>(data);
        else
        {
            Node<T> *newHead = new Node<T>(data, NULL, this->head);
            this->head->setPrev(newHead);
            this->head = newHead;
        }
    }

    void deleteData(T data)
    {

        if (head == NULL)
        {
        }

        else if (this->head == this->tail)
        {
            if (this->head->getData() == data)
            {
                this->head = this->tail = NULL;
            }
        }

        else
        {
            Node<T> *temp = head;
            while (temp != NULL)
            {

                if (temp->getData() != data)
                    temp = temp->getNext();

                else
                {
                    if (temp == this->head)
                    {
                        this->head->getNext()->setPrev(NULL);
                        head = this->head->getNext();
                    }
                    else if (temp == this->tail)
                    {
                        this->tail->getPrev()->setNext(NULL);
                        tail = this->tail->getPrev();
                    }
                    else
                    {
                        temp->getPrev()->setNext(temp->getNext());
                        temp->getNext()->setPrev(temp->getPrev());
                    }

                    break;
                }
            }
        }
    }

    void deleteData(T data, int n)
    {
        for (int i = 0; i < n; i++)
            this->deleteData(data);
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList<T> *n)
    {
        Node<T> *tempNode = n->getHead();

        cout << "(";

        if (tempNode != NULL)
        {
            while (tempNode != NULL)
            {
                cout << tempNode->getData();
                if (tempNode != n->getTail())
                    cout << ", ";
                tempNode = tempNode->getNext();
            }
        }
        cout << ")\n";
        return out;
    }

    Node<T> *getHead()
    {
        return this->head;
    }

    Node<T> *getTail()
    {
        return this->tail;
    }

private:
    Node<T> *head;
    Node<T> *tail;
};

template <class T>
class Stack
{
public:
    Stack()
    {
        list = new LinkedList<T>();
    }

    void push(T data)
    {
        this->list->addToHead(data);
    }

    T pop()
    {
        T defaultReturnValue{};
        if (this->list->getHead() != NULL)
        {
            T rmvedData = this->list->getHead()->getData();
            this->list->deleteData(rmvedData);
            return rmvedData;
        }

        return defaultReturnValue;
    }

    T top()
    {
        T defaultReturnValue{};
        if (this->list->getHead() != NULL)
        {
            return this->list->getHead()->getData();
        }

        return defaultReturnValue;
    }

    bool isEmpty()
    {
        if (this->list->getTail() != NULL)
            return false;

        return true;
    }

    int size()
    {
        int i = 0;

        Node<T> *curNode = this->list->getHead();

        while (curNode != NULL)
        {
            i++;
            curNode = curNode->getNext();
        }

        return i;
    }

    // getHead() function
    Node<T> *getHead()
    {
        return this->list->getHead();
    }

private:
    LinkedList<T> *list;
};

// create a struct to hold Stack of doubles and stack of aligned operands since we can not hold both in one stack

// Banker Rounding
double bankersRound(double f)
{
    double r = round(f * 100) / 100;
    double d = r - f;
    int id = (int)(d * 1000);
    if ((id != 5) && (id != -5))
        return r;
    string s = to_string(r);
    if (s[0] == '-' && (s[4] == '2' || s[4] == '4' || s[4] == '6' || s[4] == '8' || s[4] == '0'))
        return r;
    if (s[3] == '2' || s[3] == '4' || s[3] == '6' || s[3] == '8' || s[3] == '0')
        return r;
    return f - d;
}

// Takes 2 operands and an operator and returns the result rounded by banker's rounding
double calc(double num1, double num2, char op)
{

    switch (op)
    {
    case '+':
        return bankersRound(num1 + num2);
    case '-':
        return bankersRound(num1 - num2);
    case '*':
        return bankersRound(num1 * num2);
    case '/':
        return bankersRound(num1 / num2);
    case '^':
        return bankersRound(pow(num1, num2));
    default:
        return 0;
    }
}

// check presedence
int presedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// check if the expression is valid
bool isValid(string expression)
{
    if (expression[0] == '+' || expression[0] == '*' || expression[0] == '/' || expression[0] == '^')
        return false;

    if (expression[expression.length() - 1] == '+' || expression[expression.length() - 1] == '*' || expression[expression.length() - 1] == '/' || expression[expression.length() - 1] == '^')
        return false;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '+' || expression[i] == '*' || expression[i] == '/' || expression[i] == '^')
        {
            if (expression[i + 1] == '+' || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == '^')
                return false;
        }
    }

    int count = 0;
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '(')
            count++;
        else if (expression[i] == ')')
            count--;
    }

    if (count != 0)
        return false;

    return true;
}

// convert version that takes Stack
// will evaluate in evaluate function
// returns postfix as a stack of strings

Stack<string> *convert2(Stack<char> *infix)
{
    Stack<string> *postfix = new Stack<string>();
    Stack<char> *temp = new Stack<char>();

    while (!infix->isEmpty())
    {
        char curChar = infix->pop();

        if (curChar == '(')
        {
            temp->push(curChar);
        }
        else if (curChar == ')')
        {
            while (temp->top() != '(')
            {
                string tempStr = "";
                tempStr += temp->pop();
                postfix->push(tempStr);
            }
            temp->pop(); // remove '('
        }
        else if (curChar == '+' || curChar == '-' || curChar == '*' || curChar == '/' || curChar == '^')
        {
            while (!temp->isEmpty() && (presedence(temp->top()) >= presedence(curChar)))
            {
                string tempStr = "";
                tempStr += temp->pop();
                postfix->push(tempStr);
            }
            temp->push(curChar);
        }
        else
        {
            // while curChar is a number or a decimal point save it into temp variable, then push it to doubleStack
            string tempNum = "";
            while (((curChar >= '0' && curChar <= '9') || curChar == '.'))
            {
                tempNum += curChar;
                if (!infix->isEmpty())
                    curChar = infix->pop();
                else
                    curChar = ' ';
            }
            if (curChar != ' ')
                infix->push(curChar); // push back the last char that is not a number or decimal point
            postfix->push(tempNum);
        }
    }

    // push remaining operators to operatorStack
    while (!temp->isEmpty())
    {
        string tempStr = "";
        tempStr += temp->pop();
        postfix->push(tempStr);
    }

    // reverse postfix stack
    Stack<string> *temp2 = new Stack<string>();
    while (!postfix->isEmpty())
    {
        temp2->push(postfix->pop());
    }

    return temp2;
}

// evaluate postfix of string
double evaluate2(Stack<string> *postfix)
{
    Stack<double> *result = new Stack<double>();

    while (!postfix->isEmpty())
    {
        string curOp = postfix->pop();
        if (curOp == "+" || curOp == "-" || curOp == "*" || curOp == "/" || curOp == "^")
        {
            double num1 = result->pop();
            try
            {
                double num2 = result->pop();
                result->push(calc(num2, num1, curOp[0]));
            }
            catch (const std::exception &e)
            {
                result->push(calc(result->pop(), num1, curOp[0]));
            }
        }
        else
        {
            result->push(stod(curOp));
        }
    }

    return result->pop();
}

int main()
{
    string expression{};
    while (cin >> expression)
    {
        // save expression to stack
        Stack<char> *stack = new Stack<char>();
        for (int i = expression.length() - 1; i >= 0; --i)
        {
            stack->push(expression[i]);
        }

        if (isValid(expression))
        {
            Stack<string> *postfix2 = convert2(stack);
            double answer = evaluate2(postfix2);
            cout << fixed << setprecision(2) << answer << endl;
        }
        else
            cout << "ERROR" << endl;
    }
    return 0;
}