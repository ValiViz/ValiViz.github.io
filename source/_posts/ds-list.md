---
title: 线性表(List)
date: 2024-03-12 19:20:00
tags:
  - Boilplate
categories:
  - 编程
  - 数据结构
---
# 预处理

```C
#include <stdio.h>
#include <stdlib.h>
```

```C
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE max_size（注意替换）
```

```C
typedef data_type（注意替换） ELemType;
typedef int Status;
```

# Operation

{% note info %}
本文中的第i个元素均**从0开始**，到length-1结束。
{% endnote %}

```C
Status visit(*pe); //读取或更改元素e
```

```C
Status InitList(*pL); //初始化操作，建立一个空的线性表L。
Status ListEmpty(L); //若线性表为空，返回true，否则返回false。
Status ClearList(*pL); //将线性表清空。
Status GetElem(L, i, *pe); //将线性表L中的第i个位置元素值返回给e。
int LocateElem(L, e); //在线性表L中查找与给定值e相等的元素，如果查找成功，返回该元素在表中序号表示成功；否则，返回0表示失败。
Status ListInsert(*pL, i, e); //在线性表L中的第i个位置插入新元素e。
Status ListDelete(*pL, i, *e); //删除线性表L中第i个位置元素，并用e返回其值。
int ListLength(L); //返回线性表L的元素个数。
Status ListTraverse(*pL); //依次访问线性表L的每个元素。
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
	if(L->length == 0)
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

int LocateElem(const SqList *L, const ElemType *E)
{
	for (int i = 0; i < L->length; i++)
	{
		if (L->data[i] == *E)
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

Status ListTraverse(SqList *L, Status (*func_visit)(ElemType *E))
{
	if (L->length <= 0)
		return ERROR;
	for (int i = 0; i < L->length; i++)
		if (!func_visit(L->data[i]))
			return ERROR;
	return OK;
}

Status unionL(SqList *desk, const SqList *src)
{
	ElemType e;
	for(int i = 0; i < src->length; i++)
	{
		GetElem(*src, i, &e);
		if(!LocateElem(*desk, e))
			if(!ListInsert(desk, desk->length, e))
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
    Node *first;
    Node *last;
} LinkList;
```

```C
Status InitList(LinkList *L)
{
    L->length = 0;
    L->first = NULL;
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
    Node *now = L->first;
    for (int j = 0; j < i; j++)
    {
        now = now->next;
    }
    *E = now->data;
    return OK;
}

int LocateElem(const LinkList *L, const ElemType *E)
{
    Node *now = L->first;
    for (int i = 0; i < L->length; i++)
    {
        if (now->data = *E)
            return i;
        now = now->next;
    }
    return -1;
}

Status ListInsert(LinkList *L, int i, const ElemType *E)
{
    if (i > L->length || i < 0)
		return ERROR;
    Node *tmp = L->first;
    if (i == 0)
    {
        L->first = (Node *)malloc(sizeof(Node));
        L->first->data = *E;
        L->first->next = tmp;
    }
    else if(i == L->length)
    {
        L->last->next = (Node *)malloc(sizeof(Node));
        L->last = L->last->next;
        L->last->data = *E;
        L->last->next = NULL;
    }
    else
    {
        Node *now = tmp;
        for(int j = 1; j < i; j++)
        {
            now = now->next;
        }
        tmp = now->next;
        now->next = (Node *)malloc(sizeof(Node));
        now->next->data = *E;
        now->next->next = tmp;
    }
    L->length++;
    return OK;
}
```

# To Be Updated ...