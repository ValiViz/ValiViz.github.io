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

typedef struct
{
    SElemType data[MAXSIZE];
    int top;
} SqStack;

Status InitStack(SqStack *S)
{
    S = (SqStack *)malloc(sizeof(SqStack));
    S->top = -1;
    return OK;
}

Status ClearStack(SqStack *S)
{
    S->top = -1;
    return OK;
}

Status StackEmpty(const SqStack *S)
{
    if (S->top >= 0)
        return FALSE;
    return TRUE;
}

Status GetTop(const SqStack *S, SElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top];
    return OK;
}

Status Push(SqStack *S, const SElemType *E)
{
    if (S->top >= MAXSIZE - 1)
        return ERROR;
    S->data[++S->top] = *E;
    return OK;
}

Status Pop(SqStack *S, SElemType *E)
{
    if (StackEmpty(S))
        return ERROR;
    *E = S->data[S->top--];
    return OK;
}

int StackLength(const SqStack *S)
{
    return S->top + 1;
}