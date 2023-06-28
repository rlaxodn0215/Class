#include"IntQueueChar.h"
#include<stdio.h>
#include<stdlib.h>

int Initialize(IntQueueChar* q, int max)
{
	q->que = (char*)calloc(max, sizeof(char));

	if (q->que == NULL)
	{
		printf("메모리 할당에 실패하였습니다.\n");
		return -1;
	}

	q->max = max;
	q->num = 0;
	q->front = 0;
	q->rear = max;

	return 0;
}

int Enque(IntQueueChar* q, char x)
{
	if (q->num !=q->max)
	{
		q->que[q->front+q->num] = x;
		q->num++;
		return 0;
	}
	
	else
	{
		printf("데이터가 다 차서 더이상 데이터를 넣을 수 없습니다.\n");
		return -1;
	}

}

int Deque(IntQueueChar* q, char* x)
{
	if (q->num <= 0)
	{
		printf("제거할 데이터가 없습니다.\n");
		return -1;
	}

	else
	{
		*x = q->que[q->front];
		q->front = ((q->front++) % q->max);
		q->rear = ((q->rear++) % q->max);
		q->num--;
	}

}

int Peek(const IntQueueChar* q, char* x)
{
	if (q->num <= 0)
	{
		printf("보여줄 데이터가 없습니다.\n");
		return -1;
	}

	else
	{
		*x = q->que[q->front];
		return 0;
	}
}

void Clear(IntQueueChar* q)
{
	q->front = 0;
	q->num = 0;
	q->rear = q->max;
}

int Capacity(const IntQueueChar* q)
{
	return q->max;
}

int Size(const IntQueueChar* q)
{
	return q->num;
}

int IsEmpty(const IntQueueChar* q)
{
	return (q->num<=0);
}

int IsFull(const IntQueueChar* q)
{
	return (q->num >= q->max);
}

int Search(const IntQueueChar* q, char x)
{
	for (int i = 0; i < q->num; i++)
	{
		if (q->que[(q->front + i) % q->max] == x)
		{
			return i;
		}
	}

	return -1;
}

void Print(const IntQueueChar* q)
{
	for (int i = 0; i < q->num; i++)
	{
		printf("%d ", q->que[(q->front + i) % q->max]);
	}

	printf("\n");
}

void Terminate(IntQueueChar* q)
{
	if (q->que != NULL)
	{
		free(q->que);
		q->que = NULL;
	}

	return;
}
