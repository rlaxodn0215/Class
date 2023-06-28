#pragma once

#include<iostream>

using namespace std;

template<class Type>
class QueueTp
{
private:
	Type *items;
	int front;
	int rear;
	int num;
	int MAX;
public:
	QueueTp();
	QueueTp(int MAX);
	~QueueTp();
	void Enque(const Type& var);
	Type *Peek();
	void Deque(Type & var);
	void Print();
	bool isEmpty();
	bool isFull();
};
template<class Type>
QueueTp<Type>::QueueTp()
{
	front = 0;
	rear = 1;
	num = 0;
	MAX = 1;
	items = new Type[MAX];
	//cout << "ť ������ �߻�" << endl;
}

template<class Type>
QueueTp<Type>::QueueTp(int max)
{
	items = new Type[MAX];
	front = 0;
	rear = max;
	num = 0;
	MAX = max;
	//cout << "ť ������ �߻�" << endl;
}

template<class Type>
QueueTp<Type>::~QueueTp()
{
	//delete items;
	//cout << "ť �Ҹ��� �߻�" << endl;
}

template<class Type>
Type *QueueTp<Type>::Peek()
{
	return(&items[(front + num-1) % MAX]);
}

template<class Type>
void QueueTp<Type>:: Enque(const Type & var)
{
	if (num == MAX)
	{
		//cout << "ť�� ��� á���ϴ�." << endl;
	}

	else
	{
		items[(front + num) % MAX]=var;
		num++;
	}
}

template<class Type>
void QueueTp<Type>::Deque(Type & var)
{
	if (num == 0)
	{
		cout << "ť�� ��� �ֽ��ϴ�." << endl;
	}

	else
	{
		var = items[front];
		front=(front+1)%MAX;
		rear=(rear+1)%MAX;
		num--;
	}
}

template<class Type>
void QueueTp<Type>::Print()
{
	for (int i = (front + num-1) % MAX; i < (rear + num) % MAX; i++)
	{
		cout << items[i] << "  ";
	}
}

template<class Type>
bool QueueTp<Type>::isEmpty()
{
	return (num == 0);
}

template<class Type>
bool QueueTp<Type>::isFull()
{
	return(num == MAX);
}
