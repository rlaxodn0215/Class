#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<vector>
#include"QueueTp.h"
#include"worker0.h"
#include<stdlib.h>
#include<crtdbg.h>

using namespace std;

const int SIZE = 5;

int main()
{
	QueueTp<Worker*> lolas(SIZE);
	Worker* worker=0;

	using std::strchr;

	int ct;
	for (ct = 0; ct < SIZE; ct++)
	{
		char choice;
		cout << "������ �Է��ϼ���: \n"
			<< "w: ������	s: ����		"
			<< "t: ���� �� ������		q: ����\n";

		cin >> choice;
		while (strchr("wstq", choice) == NULL)
		{
			cout << "w, s, t, q �߿��� �ϳ��� �����Ͻʽÿ�: ";
			cin >> choice;
		}
		if (choice == 'q') break;


		switch (choice)
		{
		case 'w':
		{
			worker = new Waiter;
			lolas.Enque(worker);

		}
			break;
		case 's':
		{
			worker = new Signer;
			lolas.Enque(worker);

		}
		break;
		case 't':
		{
			worker = new SigningWaiter;
			lolas.Enque(worker);

		}
		break;
		default:
			break;
		}

		cin.get();
		(*lolas.Peek())->Set();
	}

	cout << "\n��� ��Ȳ�� ������ �����ϴ�: \n";
	int i;
	for (i = 0; i < ct; i++)
	{
		lolas.Deque(worker);
		worker->Show();
		cout << endl;
		delete worker;
	}


	return 0;
}