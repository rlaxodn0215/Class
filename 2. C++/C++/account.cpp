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
	cout << "�̸�: " << name << endl;
	cout << "����: " << acctnum << endl;
	cout << "���: " << balance << endl;
	
}
void BankAccount::deposit(double cash)
{
	if (cash < 0)
		cout << "���ప�� ������ �� �� �����ϴ�" << endl;
	else
	balance += cash;
}
void BankAccount::withdraw(double cash)
{
	if (balance < cash)
		cout << "���� �����Ͽ� ����� �� �����ϴ�" << endl;
	else
	balance -= cash;
}