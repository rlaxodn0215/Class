#pragma once

typedef struct
{
	char max;
	char ptr;
	double* stk;

}IntStackNum;

int Initialize(IntStackNum* s, int max);
int Push(IntStackNum* s, double x);
int Pop(IntStackNum* s, double* x);
int Peek(const IntStackNum* s, double* x);
void Clear(IntStackNum* s);
int Capacity(const IntStackNum* s);
int Size(const IntStackNum* s);
int IsEmpty(const IntStackNum* s);
int IsFull(const IntStackNum* s);
int Search(const IntStackNum* s, double x);
void Print(const IntStackNum* s);
void Terminate1(IntStackNum* s);