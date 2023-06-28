#include "Stock.h"
#include<iostream>

using namespace std;

Stock::Stock()
{
	cout << "����Ʈ �����ڰ� ȣ��Ǿ����ϴ�" << endl;
	company = "no name";
	shares = 0;
	share_val = 0.0;
	total_val = 0.0;

}
Stock::Stock(const std::string& co, long n, double pr)
{
	//cout << co << "�� ����ϴ� �����ڰ� ȣ��Ǿ����ϴ�" << endl;
	company = co;

	if (n < 0)
	{
		cerr << "�ֽ��� ������ �� �� ��������, " << company << " shares�� 0���� �����մϴ�," << endl;
		shares = 0;
	}
	else
	{
		shares = n;
	}

	share_val = pr;
	set_tot();
}
Stock::~Stock()
{
	//cout << "�ȳ�, " << company << endl;
}

void Stock::acquire(const std::string& co, long n, double pr)
{
	company = co;
	if (n < 0)
	{
		cout << "�ֽ��� ���� ������ �� �� ��������, "
			<< company << " shares�� 0���� �����մϴ�." << endl;
		shares = 0;
	}

	else
	{
		shares = n;
	}

	share_val = pr;
	set_tot();
}
void Stock::buy(long num, double price)
{
	if (num < 0) 
	{
		cout << "���� �ֽ� ���� ������ �� �� ��������, �ŷ��� ��ҵǾ����ϴ�" << endl;
	}

	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}
void Stock::sell(long num, double price)
{
	if (num < 0)
	{
		cout << "�ŵ� �ֽ� ���� ������ �� �� ��������, �ŷ��� ��ҵǾ����ϴ�." << endl;
	}
	else if (num>shares)
	{
		cout << "���� �ֽĺ��� ���� �ֽ��� �ŵ��� �� ��������, �ŷ��� ��ҵǾ����ϴ�." << endl;
	}
	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}
}
void Stock::update(double price)
{
	share_val = price;
	set_tot();
}
void Stock::show()
{
	cout << "ȸ���: " << company
		<< " �ֽ� ��: " << shares << endl
		<< " �ְ�: $" << share_val
		<< " �ֽ� �� ��ġ: $" << total_val << endl;
}

const Stock& Stock::topval(const Stock& s) const
{
	if (s.total_val > total_val)
		return s;
	else
	{
		return *this;
	}
}