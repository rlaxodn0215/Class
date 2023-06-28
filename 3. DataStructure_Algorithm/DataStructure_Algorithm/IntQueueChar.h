#pragma once

typedef struct
{
	int max;
	int num;
	int front;
	int rear;
	char* que;

}IntQueueChar;

int Initialize(IntQueueChar* q, int max);

int Enque(IntQueueChar* q, char x);

int Deque(IntQueueChar* q, char* x);

int Peek(const IntQueueChar* q, char* x);

void Clear(IntQueueChar* q);

int Capacity(const IntQueueChar* q);

int Size(const IntQueueChar* q);

int IsEmpty(const IntQueueChar* q);

int IsFull(const IntQueueChar* q);

int Search(const IntQueueChar* q, char x);

void Print(const IntQueueChar* q);

void Terminate(IntQueueChar* q);