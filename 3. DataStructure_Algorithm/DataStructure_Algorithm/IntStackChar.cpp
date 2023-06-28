#include<stdio.h>
#include<stdlib.h>
#include"IntStackChar.h"

int Initialize(IntStackChar* s, int max)
{
	s->ptr = 0;
	s->stk = (char*)calloc(max, sizeof(char));

	if (s->stk == NULL)
	{
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int Push(IntStackChar* s, char x)
{
	if (s->ptr >= s->max)
	{
		return -1;
	}
	s->stk[s->ptr] = x;
	s->ptr++;

	return 0;
}
int Pop(IntStackChar* s, char* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}

	s->ptr--;
	*x = s->stk[(s->ptr)];

	return 0;
}

int Peek(const IntStackChar* s, char* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}

	*x = s->stk[s->ptr - 1];

	return 0;
}

void Clear(IntStackChar* s)
{
	s->ptr = 0;
}

int Capacity(const IntStackChar* s)
{
	return (s->max);
}
int Size(const IntStackChar* s)
{
	return (s->ptr);
}
int IsEmpty(const IntStackChar* s)
{
	return (s->ptr <= 0);
}
int IsFull(const IntStackChar* s)
{
	return (s->ptr >= s->max);
}
int Search(const IntStackChar* s, char x)
{
	for (int i = s->ptr - 1; i >= 0; i--)
	{
		if (s->stk[i] == x)
		{
			return i;
		}
	}

	return -1;
}

void Print(const IntStackChar* s)
{

	for (int i = 0; i < s->ptr; i++)
	{
		printf("%d ", s->stk[i]);
	}

	putchar('\n');
}
void Terminate1(IntStackChar* s)
{
	if (s->stk != NULL)
	{
		free(s->stk);
	}

	s->max = s->ptr = 0;
}