#pragma once

template<class Item>
class queue
{
private:
	enum{Q_SIZE=10};
	class Node
	{
	public:
		Item item;
		Node* next;
		Node(const Item & i):item(i),next(0){}
	};

	Node* front;
	Node* rear;
	int items;
	const int qsize;
	queue(const queue & q):qsize(0){}
	queue & operator=(const queue& q) { return *this; }
public:
	queue(int qs = Q_SIZE);
	~queue();
	bool isempthy() const
	{
		return items == 0;
	}
	bool isfull() const
	{
		return items == qsize;
	}
	int queuecount()const
	{
		return items;
	}
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
};

template<class Item>
queue<Item>::queue(int qs) :qsize(qs)
{
	front = rear = 0;
	items = 0;
}

template<class Item>
queue<Item>::~queue()
{
	Node* temp;
	while (front != 0)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template <class Item>
bool queue<Item>::enqueue(const Item& item)
{
	if (isfull())
		return false;
	Node* add = new Node(item);

	items++;
	if (front == 0)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

template<class Item>
bool queue<Item>::dequeue(Item& item)
{
	if (front == 0)
		return false;
	item = front->item;
	items--;
	Node* temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = 0;
	return true;
}