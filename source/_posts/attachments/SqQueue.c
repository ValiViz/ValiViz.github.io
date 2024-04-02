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
} ElemType;

typedef struct
{
    ElemType data[MAXSIZE];
    int front;
    int rear;
} SqQueue;

Status InitQueue(SqQueue *Q)
{
    Q = (SqQueue *)malloc(sizeof(SqQueue));
    Q->front = Q->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

Status QueueEmpty(const SqQueue *Q)
{
    if (Q->front == Q->rear)
        return TRUE;
    return FALSE;
}

int QueueLength(const SqQueue *Q)
{
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

Status GetHead(const SqQueue *Q, ElemType *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    *E = Q->data[Q->front];
    return OK;
}

Status EnQueue(SqQueue *Q, const ElemType *E)
{
    if ((Q->rear + MAXSIZE) % MAXSIZE == Q->front)
        return ERROR;
    Q->data[Q->rear] = *E;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

Status DeQueue(SqQueue *Q, ElemType *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    *E = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}