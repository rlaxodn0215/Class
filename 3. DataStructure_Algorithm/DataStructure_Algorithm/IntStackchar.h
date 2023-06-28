#pragma once

typedef struct
{
	char max;
	char ptr;
	char* stk;

}IntStackChar;

int Initialize(IntStackChar* s, int max);
int Push(IntStackChar* s, char x);
int Pop(IntStackChar* s, char* x);
int Peek(const IntStackChar* s, char* x);
void Clear(IntStackChar* s);
int Capacity(const IntStackChar* s);
int Size(const IntStackChar* s);
int IsEmpty(const IntStackChar* s);
int IsFull(const IntStackChar* s);
int Search(const IntStackChar* s, char x);
void Print(const IntStackChar* s);
void Terminate1(IntStackChar* s);