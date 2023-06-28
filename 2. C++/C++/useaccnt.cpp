#include"account.h"
#include<iostream>

using namespace std;

void main()
{
	BankAccount Kim("±èÅÂ¿ì", "12345", 500.0);

	Kim.show();

	Kim.deposit(300.0);
	Kim.show();

	Kim.withdraw(1000.0);
	Kim.show();

	Kim.withdraw(200.0);
	Kim.show();
}