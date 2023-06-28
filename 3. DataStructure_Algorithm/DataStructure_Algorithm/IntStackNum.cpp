#include<stdio.h>
#include<stdlib.h>
#include"IntStackNum.h"

int Initialize(IntStackNum* s, int max)
{
	s->ptr = 0;
	s->stk = (double*)calloc(max, sizeof(double));

	if (s->stk == NULL)
	{
		s->max = 0;
		return -1;
	}
	s->max = max;
	return 0;
}

int Push(IntStackNum* s, double x)
{
	if (s->ptr >= s->max)
	{
		return -1;
	}
	s->stk[s->ptr] = x;
	s->ptr++;

	return 0;
}
int Pop(IntStackNum* s, double* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}

	s->ptr--;
	*x = s->stk[(s->ptr)];

	return 0;
}

int Peek(const IntStackNum* s, double* x)
{
	if (s->ptr <= 0)
	{
		return -1;
	}

	*x = s->stk[s->ptr - 1];

	return 0;
}

void Clear(IntStackNum* s)
{
	s->ptr = 0;
}

int Capacity(const IntStackNum* s)
{
	return (s->max);
}
int Size(const IntStackNum* s)
{
	return (s->ptr);
}
int IsEmpty(const IntStackNum* s)
{
	return (s->ptr <= 0);
}
int IsFull(const IntStackNum* s)
{
	return (s->ptr >= s->max);
}
int Search(const IntStackNum* s, int x)
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

void Print(const IntStackNum* s)
{

	for (int i = 0; i < s->ptr; i++)
	{
		printf("%d ", s->stk[i]);
	}

	putchar('\n');
}
void Terminate1(IntStackNum* s)
{
	if (s->stk != NULL)
	{
		free(s->stk);
	}

	s->max = s->ptr = 0;
}