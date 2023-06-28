#include"account.h"
#include<iostream>
using namespace std;

BankAccount::BankAccount(const std::string & clint, const std::string & num,double bal)
{
	name = clint;
	acctnum = num;
	balance = bal;
}

void BankAccount::show() const
{
	cout << "이름: " << name << endl;
	cout << "계좌: " << acctnum << endl;
	cout << "비용: " << balance << endl;
	
}
void BankAccount::deposit(double cash)
{
	if (cash < 0)
		cout << "저축값은 음수가 될 수 없습니다" << endl;
	else
	balance += cash;
}
void BankAccount::withdraw(double cash)
{
	if (balance < cash)
		cout << "돈이 부족하여 출금할 수 없습니다" << endl;
	else
	balance -= cash;
}