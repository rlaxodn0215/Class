#pragma once

typedef struct
{
	int max;
	int num;
	int front;
	int rear;
	double* que;

}IntQueueNum;

int Initialize(IntQueueNum* q, int max);

int Enque(IntQueueNum* q, double x);

int Deque(IntQueueNum* q, double* x);

int Peek(const IntQueueNum* q, double* x);

void Clear(IntQueueNum* q);

int Capacity(const IntQueueNum* q);

int Size(const IntQueueNum* q);

int IsEmpty(const IntQueueNum* q);

int IsFull(const IntQueueNum* q);

int Search(const IntQueueNum* q, double x);

void Print(const IntQueueNum* q);

void Terminate(IntQueueNum* q);