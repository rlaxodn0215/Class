#pragma once
#include<string>


class BankAccount
{
private:
	std::string name;
	std::string acctnum;
	double balance;
public:
	BankAccount(const std::string & clint, const std::string& num, double bal = 0.0);
	void show() const;
	void deposit(double cash);
	void withdraw(double cash);
};
