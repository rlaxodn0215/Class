#include<iostream>
#include"namesp.h"

namespace pers
{
	using std::cout;
	using std::cin;
	void getPerson(Person& rp)
	{
		cout << "이름을 입력하시오: ";
		cin >> rp.fname;
		cout << "성씨를 입력하세요: ";
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
		std::cout << "부채를 입력하세요: ";
		std::cin >> rd.amount;
	}


}