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

typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode;

typedef struct
{
    QNode *front;
    QNode *rear;
} LinkQueue;

Status InitQueue(LinkQueue *Q)
{
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));
    Q->rear->next = NULL;
    return OK;
}

Status ClearQueue(LinkQueue *Q)
{
    QNode *p = Q->front->next;
    while (p)
    {
        QNode *tmp = p->next;
        p = p->next;
        free(tmp);
    }
    return OK;
}

Status QueueEmpty(const LinkQueue *Q)
{
    if (Q->front->next == NULL)
        return TRUE;
    return FALSE;
}

int QueueLength(const LinkQueue *Q)
{
    QNode *p = Q->front;
    int count = 0;
    while (p != Q->rear)
    {
        p = p->next;
        count++;
    }
    return count;
}

Status GetHead(const LinkQueue *Q, ElemType *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    *E = Q->front->next->data;
    return OK;
}

Status EnQueue(LinkQueue *Q, const ElemType *E)
{
    Q->rear->next = (QNode *)malloc(sizeof(QNode));
    Q->rear = Q->rear->next;
    Q->rear->data = *E;
    return OK;
}

Status DeQueue(LinkQueue *Q, ElemType *E)
{
    if (QueueEmpty(Q))
        return ERROR;
    QNode *p = Q->front->next;
    *E = p->data;
    Q->front->next = p->next;
    free(p);
    return OK;
}