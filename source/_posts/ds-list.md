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
Status InitList(SqList *plist)
{
	plist->length = 0;
	return OK;
}

Status ListEmpty(SqList list)
{
	if(list.length == 0)
		return TRUE;
	else
		return FALSE;
}

Status ClearList(SqList *plist)
{
	plist->length = 0;
	return OK;
}

Status GetElem(SqList list, int i, ElemType *pe)
{
	if (list.length == 0 || i < 0 || i >= list.length)
		return ERROR;
	*pe = list.data[i];
	return OK;
}

int LocateElem(SqList list, ElemType e)
{
	for (int i = 0; i < list.length; i++)
	{
		if (list.data[i] == e)
			return i;
	}
	return 0;
}

Status ListInsert(SqList *plist, int i, ElemType e)
{
	
	if (i >= plist->length || i < 0 || plist->length >= MAXSIZE)
		return ERROR;
	for (int j = plist->length; j > i; j--)
		plist->data[j] = plist->data[j - 1];
	plist->data[i] = e;
	plist->length++;
	return OK;
}

Status ListDelete(SqList *plist, int i, ElemType *e)
{
	if (i >= plist->length || i < 0 || plist->length <= 0)
		return ERROR;
	*e = plist->data[i];
	plist->length--;
	for (; i < plist->length; i++)
	{
		plist->data[i] = plist->data[i + 1];
	}
	return OK;
}

int ListLength(SqList list)
{
	return list.length;
}

Status ListTraverse(SqList *plist, Status (*func_visit)())
{
	if (plist->length <= 0)
		return ERROR;
	for (int i = 0; i < plist->length; i++)
		if (!func_visit(plist->data[i]))
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

# To Be Updated ...