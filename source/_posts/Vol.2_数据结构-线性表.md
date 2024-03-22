---
title: 线性表(List)
date: 2024-03-12 19:20:00
tags:
  - Boilplate
categories:
  - 编程
  - 数据结构
excerpt: 零个或多个数据元素的有限序列，分为顺序存储结构和链式存储结构两大结构，其中链式存储结构分为单链表、静态链表、循环链表、双向链表等
Vol: "002"
---
# INDEX-Operations

{% note info %}
本文中的第i个元素均**从0开始**，到length-1结束。
{% endnote %}

```C
int compar(*Ea, *Eb);           // 比较元素Ea和Eb
Status visit(*E);               // 读取或更改元素E。
Status InitList(*L);            // 初始化操作，建立一个空的线性表L。
Status ListEmpty(*L);           // 若线性表为空，返回true，否则返回false。
Status ClearList(*L);           // 将线性表清空。
Status GetElem(*L, i, *E);      // 将线性表L中的第i个位置元素值返回给e。
int LocateElem(*L, *E, compar); // 在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功；否则，返回0表示失败。
Status ListInsert(*L, i, *E);   // 在线性表L中的第i个位置插入新元素e。
Status ListDelete(*L, i, *E);   // 删除线性表L中第i个位置元素，并用e返回其值。
int ListLength(*L);             // 返回线性表L的元素个数。
Status ListTraverse(*L, visit); // 依次访问线性表L的每个元素。
Status unionL(desk, src);       // 依次在线性表desk中查找线性表src的每个元素，如果查找失败，在线性表desk的末尾插入该元素。
```

# 预处理

```C
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

int compar(const void *Ea, const void *Eb)
{
    ElemType ea = *(ElemType *)Ea, eb = *(ElemType *)Eb;
    （注意替换）
}

Status visit(ElemType *E)
{
    （注意替换） return OK;
}
```

# 顺序存储

```C
typedef struct
{
    ElemType data[MAXSIZE];
    int length;
} SqList;
```

```C
Status InitList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status ListEmpty(const SqList *L)
{
    if (L->length == 0)
        return TRUE;
    else
        return FALSE;
}

Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}

Status GetElem(const SqList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    *E = L->data[i];
    return OK;
}

int LocateElem(const SqList *L, const ElemType *E, int (*compar)(const void *, const void *))
{
    for (int i = 0; i < L->length; i++)
    {
        if (compar(&L->data[i], E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(SqList *L, int i, const ElemType *E)
{

    if (i > L->length || i < 0 || L->length >= MAXSIZE)
        return ERROR;
    for (int j = L->length; j > i; j--)
        L->data[j] = L->data[j - 1];
    L->data[i] = *E;
    L->length++;
    return OK;
}

Status ListDelete(SqList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0 || L->length <= 0)
        return ERROR;
    *E = L->data[i];
    L->length--;
    for (; i < L->length; i++)
    {
        L->data[i] = L->data[i + 1];
    }
    return OK;
}

int ListLength(const SqList *L)
{
    return L->length;
}

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    for (int i = 0; i < L->length; i++)
        if (!func_visit(&L->data[i]))
            return ERROR;
    return OK;
}

Status unionL(SqList *desk, const SqList *src)
{
    ElemType e;
    for (int i = 0; i < src->length; i++)
    {
        GetElem(src, i, &e);
        if (!LocateElem(desk, &e, compar))
            if (!ListInsert(desk, desk->length, &e))
                return ERROR;
        return OK;
    }
}
```

# 链式存储

```C
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct
{
    int length;
    Node *top;
    Node *last;
} LinkList;
```

```C
Status InitList(LinkList *L)
{
    L->length = 0;
    L->top = (Node *)malloc(sizeof(Node));
    L->top->next = NULL;
    L->last = NULL;
    return OK;
}

Status ListEmpty(const LinkList *L)
{
    if (!L->length)
        return FALSE;
    return TRUE;
}

Status ClearList(LinkList *L)
{
    InitList(L);
    return OK;
}

Status GetElem(const LinkList *L, int i, ElemType *E)
{
    if (L->length == 0 || i < 0 || i >= L->length)
        return ERROR;
    Node *now = L->top->next;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    *E = now->data;
    return OK;
}

int LocateElem(const LinkList *L, const ElemType *E, int (*compar)(const void *, const void *))
{
    Node *now = L->top;
    for (int i = 0; i < L->length; i++)
    {
        now = now->next;
        if (compar(now->data, *E) == 0)
            return i;
    }
    return -1;
}

Status ListInsert(LinkList *L, int i, const ElemType *E)
{
    if (i > L->length || i < 0)
        return ERROR;
    Node *now = L->top;
    if (i == L->length)
        now = L->last;
    else
        for (int j = 0; j < i; j++)
        {
            now = now->next;
        }
    Node *tmp = now->next;
    now->next = (Node *)malloc(sizeof(Node));
    now->next->data = *E;
    if (i == L->length)
        L->last = now->next;
    now->next->next = tmp;
    L->length++;
    return OK;
}

Status ListDelete(LinkList *L, int i, ElemType *E)
{
    if (i >= L->length || i < 0)
        return ERROR;
    Node *now = L->top;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    if (i == L->length - 1)
        L->last = now;
    Node *tmp = now->next;
    now->next = now->next->next;
    *E = tmp->data;
    free(tmp);
    L->length--;
    return OK;
}

int ListLength(const LinkList *L)
{
    return L->length;
}

Status ListTraverse(LinkList *L, Status (*func_visit)(ElemType *))
{
    if (L->length <= 0)
        return ERROR;
    Node *now = L->top;
    for (int i = 0; i < L->length; i++)
    {
        now = now->next;
        if (!func_visit(&now->data))
            return ERROR;
    }
    return OK;
}

Status unionL(LinkList *desk, const LinkList *src)
{
    ElemType e;
    for (int i = 0; i < src->length; i++)
    {
        GetElem(src, i, &e);
        if (!LocateElem(desk, &e, compar))
            if (!ListInsert(desk, desk->length, &e))
                return ERROR;
        return OK;
    }
}
```

# To Be Updated...