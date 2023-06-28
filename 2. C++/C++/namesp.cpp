#include<iostream>
#include"namesp.h"

namespace pers
{
	using std::cout;
	using std::cin;
	void getPerson(Person& rp)
	{
		cout << "�̸��� �Է��Ͻÿ�: ";
		cin >> rp.fname;
		cout << "������ �Է��ϼ���: ";
		cin >> rp.lname;
	}

	void shoePerson(const Person& rp)
	{
		std::cout << rp.lname << ", " << rp.fname;
	}
}

namespace debts
{
	void getDebt(Debt& rd)
	{
		getPerson(rd.name);
		std::cout << "��ä�� �Է��ϼ���: ";
		std::cin >> rd.amount;
	}


}