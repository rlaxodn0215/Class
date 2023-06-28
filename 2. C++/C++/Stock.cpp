#include "Stock.h"
#include<iostream>

using namespace std;

Stock::Stock()
{
	cout << "디폴트 생성자가 호출되었습니다" << endl;
	company = "no name";
	shares = 0;
	share_val = 0.0;
	total_val = 0.0;

}
Stock::Stock(const std::string& co, long n, double pr)
{
	//cout << co << "를 사용하는 생성자가 호출되었습니다" << endl;
	company = co;

	if (n < 0)
	{
		cerr << "주식은 음수가 될 수 없음으로, " << company << " shares를 0으로 살정합니다," << endl;
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
	//cout << "안녕, " << company << endl;
}

void Stock::acquire(const std::string& co, long n, double pr)
{
	company = co;
	if (n < 0)
	{
		cout << "주식의 수는 음수가 될 수 없음으로, "
			<< company << " shares를 0으로 설정합니다." << endl;
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
		cout << "매입 주식 수는 음수가 될 수 없음으로, 거래가 취소되었습니다" << endl;
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
		cout << "매도 주식 수는 음수가 될 수 없음으로, 거래가 취소되었습니다." << endl;
	}
	else if (num>shares)
	{
		cout << "보유 주식보다 많은 주식을 매도할 수 없음으로, 거래가 취소되었습니다." << endl;
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
	cout << "회사명: " << company
		<< " 주식 수: " << shares << endl
		<< " 주가: $" << share_val
		<< " 주식 총 가치: $" << total_val << endl;
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