#include "worker0.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void Worker::Data() const
{
	cout << "사원 이름: " << fullname << endl;
	cout << "사원 번호: " << id << endl;
}

void Worker::Get()
{
	getline(cin, fullname);
	cout << "사원 번호를 입력하시요: ";
	cin >> id;
	while (cin.get() != '\n')
	{
		continue;
	}
}

Worker::~Worker()
{
	cout << "Worker 소멸자 발생" << endl;
}


void Waiter::Data() const
{

	cout << "웨이터 등급: " << panache << endl;
}

void Waiter::Get()
{
	cout << "웨이터 등급을 입력하십시오: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;
}

void Waiter::Set()
{
	Worker::Set();
	cout << "웨이터의 이름을 입력하세요: ";
	Worker::Get();
	Get();
}

void Waiter::Show() const
{
	cout << "직종: 웨이터\n";
	Worker::Data();
	Data();
}

const char* Signer::pv[Signer::Vtypes] = { "other","alto","contralto","soprano","bass","baritone","tenor" };


void Signer::Set()
{

	cout << "가수의 이름을 입력하십시오: ";
	Worker::Get();
	Get();
}

void Signer::Show() const
{

	cout << "직종: 가수\n";
	Worker::Data();
	Data();
}

void Signer::Data() const
{
	cout << "목소리 유형: " << pv[voice] << endl;
}

void Signer::Get()
{
	cout << "가수의 목소리 유형 번호를 입력하세요:: \n";
	int i;
	for (i = 0; i < Vtypes; i++)
	{
		cout << i << ": " << pv[i] << " ";
		if (i % 4 == 3)
		{
			cout << endl;
		}
	}

	if (i % 4 != 0)
	{
		cout << endl;
	}

	cin >> voice;
	while (cin.get() != '\n')
	{
		continue;
	}
}

void SigningWaiter::Data() const
{
	Signer::Data();
	Waiter::Data();
}

void SigningWaiter::Get()
{
	Waiter::Get();
	Signer::Get();
}

void SigningWaiter::Set()
{
	cout << "가수 겸 웨이터의 이름을 입력하십시오: ";
	Worker::Get();
	Get();
}

void SigningWaiter::Show() const
{
	cout << "직종: 가수 겸 웨이터\n";
	Worker::Data();
	Data();
}
