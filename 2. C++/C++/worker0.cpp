#include "worker0.h"
#include<iostream>

using std::cout;
using std::cin;
using std::endl;

void Worker::Data() const
{
	cout << "��� �̸�: " << fullname << endl;
	cout << "��� ��ȣ: " << id << endl;
}

void Worker::Get()
{
	getline(cin, fullname);
	cout << "��� ��ȣ�� �Է��Ͻÿ�: ";
	cin >> id;
	while (cin.get() != '\n')
	{
		continue;
	}
}

Worker::~Worker()
{
	cout << "Worker �Ҹ��� �߻�" << endl;
}


void Waiter::Data() const
{

	cout << "������ ���: " << panache << endl;
}

void Waiter::Get()
{
	cout << "������ ����� �Է��Ͻʽÿ�: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;
}

void Waiter::Set()
{
	Worker::Set();
	cout << "�������� �̸��� �Է��ϼ���: ";
	Worker::Get();
	Get();
}

void Waiter::Show() const
{
	cout << "����: ������\n";
	Worker::Data();
	Data();
}

const char* Signer::pv[Signer::Vtypes] = { "other","alto","contralto","soprano","bass","baritone","tenor" };


void Signer::Set()
{

	cout << "������ �̸��� �Է��Ͻʽÿ�: ";
	Worker::Get();
	Get();
}

void Signer::Show() const
{

	cout << "����: ����\n";
	Worker::Data();
	Data();
}

void Signer::Data() const
{
	cout << "��Ҹ� ����: " << pv[voice] << endl;
}

void Signer::Get()
{
	cout << "������ ��Ҹ� ���� ��ȣ�� �Է��ϼ���:: \n";
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
	cout << "���� �� �������� �̸��� �Է��Ͻʽÿ�: ";
	Worker::Get();
	Get();
}

void SigningWaiter::Show() const
{
	cout << "����: ���� �� ������\n";
	Worker::Data();
	Data();
}
