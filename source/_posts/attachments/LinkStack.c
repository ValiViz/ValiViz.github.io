#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE max_size（注意替换）
typedef int Status;

typedef struct
{
    （注意替换）
} SElemType;

typedef struct Node
{
    SElemType data;
    struct Node *link;
} Node;

typedef struct
{
    Node *top;
} LinkStack;

Status InitStack(LinkStack *S)
{
    S = (LinkStack *)malloc(sizeof(LinkStack));
    S->top = NULL;
    return OK;
}

Status ClearStack(LinkStack *S)
{
    Node *p = S->top;
    while (p)
    {
        Node *tmp = p;
        p = p->link;
        free(tmp);
    }
    S->top = NULL;
    return OK;
}

Status StackEmpty(const LinkStack *S)
{
    if (S->top == NULL)
        return TRUE;
    return FALSE;
}

Status GetTop(const LinkStack *S, SElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->top->data;
    return OK;
}

Status Push(LinkStack *S, const SElemType *E)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = *E;
    p->link = S->top;
    S->top = p;
    return OK;
}

Status Pop(LinkStack *S, SElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    Node *p = S->top;
    *E = p->data;
    S->top = p->link;
    free(p);
    return OK;
}

int StackLength(LinkStack *S)
{
    Node *p = S->top;
    int count = 0;
    while (p)
    {
        p = p->link;
        count++;
    }
    return count;
}