#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

struct Node
{
    char* data;
    struct Node *prev, *next;
};

void initLinkList(struct Node **head)
{
    (*head) = NULL;
}

void addToHead(struct Node **head, char* data)
{
    if((*head) == NULL)///there is nothing in list
    {
        (*head) = malloc(sizeof(struct Node));
        (*head)->prev = NULL;
        (*head)->next = NULL;
        (*head)->data = data;
    }
    else
    {
        struct Node *temp = malloc(sizeof(struct Node));

        temp->prev = NULL;
        temp->data = data;
        temp->next = (*head);
        (*head)->prev = temp;
        (*head) = temp;
    }

}

void addToTail(struct Node **head, char* data)
{
    if((*head) == NULL)///there is nothing in the list
    {
        (*head) = (struct Node*)malloc(sizeof(struct Node));
        (*head)->data = data;
        (*head)->prev = NULL;
        (*head)->next = NULL;
        return;
    }

    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp = (*head);

    while(temp->next != NULL)///trying to find the tail of the list
    {
        temp = temp->next;
    }

    struct Node *newadded = (struct Node*)malloc(sizeof(struct Node));

    newadded->data = data;
    newadded->next = NULL;
    newadded->prev = temp;

    temp->next = newadded;
}

void deleteData(struct Node **head, char* data)
{
    struct Node *now =(*head), *pre;

    while((now != NULL) && (now->data != data))
    {
        pre = now;
        now = now->next;
    }

    if(now->data == NULL) {}

    else if(now == (*head))///the first thing need to be deleted
    {
        if(now->next == NULL)///there is only one thing in the queue
        {
            initLinkList(head);
        }
        else
        {
            (*head) = now->next;
            (*head)->prev = NULL;
        }
    }

    else
    {
        pre->next = now->next;
    }
}

void deleteDatas(struct Node **head, char* data, int n)
{
    for(int i = n; i > 0; i--)
    {
        deleteData(head, data);
    }
}

void display(struct Node *head)
{
    struct Node *temp = head;

    printf("%c", '(');

    while(temp != NULL)
    {
        if(temp->data == NULL)
        {
            break;
        }
        else if(temp->next == NULL)
        {
            printf("%s", temp->data);
        }

        else
        {
            printf("%s, ", temp->data);
        }

        temp = temp->next;
    }
    printf(")\n");
}

void push(struct Node **stack, char data[20])
{
    addToTail(stack, data);
}

char* pop(struct Node **stack)
{
    if((*stack) == NULL)///the stack is empty
    {
        return NULL;
    }
    else if((*stack)->next == NULL)
    {
        char* useless = (*stack)->data;
        (*stack) = NULL;

        return useless;
    }

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp = (*stack);

    while(temp->next != NULL && temp != NULL)
    {
        temp = temp->next;
    }
    char* useless = temp->data;
    temp->prev->next = NULL;

    return useless;
}

char top(struct Node *stack)
{
    if(stack == NULL)
    {
        return NULL;
    }
    struct Node *temp = stack;

    while(temp && temp->next)
    {
        temp = temp->next;
    }
    return *(temp->data);
}

int isEmpty(struct Node *stack)
{
    if(stack == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int size(struct Node *stack)
{
    int count = 0;
    while(stack != NULL)
    {
        count++;
        stack = stack->next;
    }

    return count;
}

char* initialString(char *str, int n)
{
    for(int i = 0; i < n; i++)
    {
        str[i] = '\0';
    }
    return str;
}

int prec(char c)
{
    if(c == '^')
    {
        return 3;
    }
    else if(c == '*' || c == '/')
    {
        return 2;
    }
    else if(c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int infixTopostfix(char *infix, struct Node **postfix, int flag)
{
    int count_ = 0, cnt_t = 0, cnt_s = 0;///count the number of '(' and ')'
    struct Node* symbol = (struct Node*)malloc(sizeof(struct Node));
    char **t = (char **)calloc(20, sizeof(char*));
    char **s = (char **)calloc(20, sizeof(char*));
    initLinkList(&symbol);

    for(int i = 0; i < strlen(infix); i++)
    {
        //printf("the infix[i] = %c\n", infix[i]);
        int c = 0;
        if(infix[i] == '-' && infix[i+1] == '-')
        {
            *(t+cnt_t) = (char *)calloc(20, sizeof(char));
            for(int j = i+2, k = 0; isdigit(infix[j]) || infix[j] == '.' || infix[j] == '-'; j++, k++)
            {
                *(*(t+cnt_t)+k) = infix[j];
                i = j;
            }
            if(*(t+cnt_t)[0] != '\0')
            {
                push(postfix, *(t+cnt_t));
                push(&symbol, "+");
                cnt_t++;
            }
            i++;///beccause the i after the loop will be the last one position in the loop, but i want the last+1 one
        }
        if((infix[i] == '-' && isdigit(infix[i+1]) && !isdigit(infix[i-1])) || isdigit(infix[i]) || infix[i] == '.')
        {
            *(t+cnt_t) = (char *)calloc(20, sizeof(char));
            for(int j = i, k = 0; isdigit(infix[j]) || infix[j] == '.' || infix[i] == '-'; j++, k++)
            {
                *(*(t+cnt_t)+k) = infix[j];
                i = j;
            }
            push(postfix, *(t+cnt_t));
            cnt_t++;
        }
        else if((!isdigit(infix[i]) && !isdigit(infix[i+1]) && infix[i+1] != '(') && infix[i] != '(' && infix[i] != ')')
        {
            flag = 1;
            return flag;
        }
        else if(infix[i] == '(')
        {
            char *c = (char *)calloc(1, sizeof(char));
            *c = infix[i];
            push(&symbol, c);
            //printf("@");
            //display(symbol);
            count_++;
        }
        else if(infix[i] == ')')
        {
            count_--;
            while(!isEmpty(symbol) && top(symbol) != '(')
            {
                char *c = (char *)calloc(1, sizeof(char));
                *c = top(symbol);
                push(postfix, c);
                pop(&symbol);
            }
            if(isEmpty(symbol))
            {
                continue;
            }
            pop(&symbol);
        }
        else
        {
            while(prec(infix[i]) <= prec(top(symbol)))
            {
                *(s+cnt_s) = (char *)calloc(1, sizeof(char));

                *(*(s+cnt_s)) = top(symbol);
                push(postfix, *(s+cnt_s));
                pop(&symbol);

                cnt_s++;
            }
            *(s+cnt_s) = (char *)calloc(1, sizeof(char));
            *(*(s+cnt_s)) = infix[i];
            push(&symbol, *(s+cnt_s));
            cnt_s++;
        }
    }
    while(!isEmpty(symbol))
    {
        char *c = (char *)calloc(1, sizeof(char));
        *c = top(symbol);
        push(postfix, c);
        pop(&symbol);
    }
    if(count_ < 0 || count_ > 0)
    {
        flag = 1;
        return flag;
    }
    if(flag != 1)
    {
        return 0;
    }
    return 0;
}

void Reverse(char *str, char *tmp, int k)
{
    //printf("tmp = %s\n", tmp);
    for(int i = strlen(tmp)-1; i >= 0; i--)
    {
        str[k++] = tmp[i];
    }
    //printf("str = %s\n", str);
}

char* convert(int i, int flag)
{
    char *tmp=(char *)malloc(sizeof(char)*20);
    initialString(tmp, 20);
    int l = 0, f = 0;
    if(i == 0)
    {
        if((flag == 1 || flag == 3) && l < 6)
        {
            while(l < 6)
            {
                tmp[l++] = '0';
            }
        }
        else
        {
            tmp[l++] = '0';
        }
    }
    if(flag >= 2)
    {
        i *= -1;
        if(flag == 2)
        {
            f = 1;
        }
    }
    else if((flag == 1 || flag == 3) && i / 100000 == 0)
    {
        flag = 4;
    }
    else if(flag >= 2)
    {
        flag = 5;
    }
    while(i)
    {
        tmp[l++] = i % 10 + '0';
        i = i / 10;
    }
    if(flag == 4)
    {
        tmp[l++] = '0';
    }
    if(f)
    {
        tmp[l++] = '-';
    }


    return tmp;
}

char* doubleTostring(double num)
{
    int i = num, k = 0, flag = 0;
    double d = num - i;
    char *str = (char *)calloc(20, sizeof(char));
    if(num < 0)
    {
        flag = 2;
    }
    Reverse(str, convert(i, flag), k);

    str[strlen(str)] = '.';
    k = strlen(str);
    for(int j = 0; j < 6; j++)
    {
        d *= 10;
    }
    int d_ = d;
    flag++;///float part
    Reverse(str, convert(d_, flag), k);
    return str;
}

char* Round(char *num)
{
    //printf("before round = %s\n", num);
    char *tmp = (char *)malloc(sizeof(char)*20);
    int k = 0;
    for(int i = 0; i < strlen(num); i++)
    {
        if(num[i] == '.')
        {
            if((num[i+3] == '5' && num[i+4] != '0') || num[i+3] >= '6')
            {
                num[i+2] = (char)(num[i+2] + 1);
            }
            else if(num[i+3] == '5')
            {
                if((int)(num[i+2]) % 2 == 1)
                {
                    num[i+2] = (char)(num[i+2] + 1);
                }
            }
            for(int j = 0; j <= i+2; j++)
            {
                tmp[k] = num[j];
                k++;
            }
        }
    }
    //printf("after round = %s\n", tmp);
    return tmp;
}

char* calculate(struct Node *postfix, int flag)
{
    double ans;

    struct Node *temp = postfix;

    while(temp->next != NULL)
    {
        while(temp->prev != NULL)
        {
            temp = temp->prev;
        }
        while(isdigit(temp->data[0]) || isdigit(temp->data[1]))
        {
            temp = temp->next;
        }

        double num_1 = atof(temp->prev->data);
        double num_2 = atof(temp->prev->prev->data);

        //printf("the num_1 = %lf\nthe num_2 = %lf\n", num_1, num_2);

        if(*(temp->data) == '^')
        {
            ans = pow(num_2, num_1);
            //printf("^^^ = %lf\n", ans);
        }
        else if(*(temp->data) == '/')
        {
            if(num_1 == 0)
            {
                flag = 1;
                break;
            }
            ans = num_2 / num_1;
            //printf("/// = %lf\n", ans);
        }
        else if(*(temp->data) == '*')
        {
            ans = num_2 * num_1;
            //printf("*** = %lf\n", ans);
        }
        else if(*(temp->data) == '+')
        {
            ans = num_2 + num_1;
            //printf("+++ = %lf\n", ans);
        }
        else if(*(temp->data) == '-')
        {
            ans = num_2 - num_1;
            //printf("--- = %lf\n", ans);
        }

        temp->prev = temp->prev->prev->prev;

        temp->data = Round(doubleTostring(ans));

    }
    char *Ans = temp->data;
    //printf("ans = %s\n", Ans);
    return Ans;
}

int main()
{
    char *infix = (char *)malloc(sizeof(char)*100);

    while(scanf("%s", infix) != EOF)
    {
        struct Node *postfix = malloc(sizeof(struct Node));
        initLinkList(&postfix);

        int flag = 0;
        flag = infixTopostfix(infix, &postfix, flag);
        if(flag)
        {
            printf("ERROR\n");
            flag = 0;
            continue;
        }

        //printf("My postfix = ");
        //display(postfix);

        printf("%s\n", calculate(postfix, flag));
        if(flag)
        {
            printf("ERROR\n");
            flag = 0;
            continue;
        }
    }
}
