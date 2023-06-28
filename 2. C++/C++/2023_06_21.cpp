#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<iostream>
#include<new>
#include<cstdlib>
#include"queue.h"
#include"exc_mean.h"

using namespace std;

//struct Big
//{
//	double stuff[200];
//};
// 
//double hmean(double a, double b) throw(bad_hmean)
//{
//	if (a == -b)
//		throw bad_hmean(a, b);
//	return 2.0 * a * b / (a + b);
//}
//double gmean(double a, double b) throw(bad_gmean)
//{
//	if (a < 0 || b < 0)
//		throw bad_gmean(a, b);
//	return std::sqrt(a * b);
//}

//double hmean(double a, double b)
//{
//	if (a == -b)
//		throw "잘못된 hmean() 매개변수: a==-b는 허용되지 않습니다.";
//		return 2.0 * a * b / (a + b);
//}

int main()
{
	//Big* pb;
	//try {
	//	cout << "큰 메모리 블록 대입을 요청하고 있습니다.\n";
	//	pb = new Big[10000];
	//	cout << "메모리 블록 대입 요청이 거부되었습니다.\n";
	//}

	//catch (bad_alloc& ba)
	//{
	//	cout << "예외가 감지되었습니다!\n";
	//	cout << ba.what() << endl;
	//	exit(EXIT_FAILURE);
	//}

	//cout << "메모리 블록이 성공적으로 대입되었습니다.\n";
	//pb[0].stuff[0] = 4;
	//cout << pb[0].stuff[0] << endl;
	//delete[] pb;


	//double x, y, z;

	//cout << "두 수를 입력하십시오: ";
	//while (cin >> x >> y)
	//{
	//	try {
	//		z = hmean(x, y);
	//		cout << x << ", " << y << "의 조화평균은 " << z << "입니다. \n";
	//		cout << x << ", " << y << "의 기하평균은 " <<gmean(x,y) << "입니다. \n";
	//		cout << "다른 두 수를 입력하세요 (끝냐려면 q): ";
	//	}

	//	catch (bad_hmean& bg)
	//	{
	//		bg.mesg();
	//		cout << "다시 하십시오.\n";
	//		continue;
	//	}

	//	catch (bad_gmean& hg)
	//	{
	//		cout << hg.mesg();
	//		cout << "Values used: " << hg.v1 << ", " << hg.v2 << endl;
	//		cout << "조송합니다. 더이상 진행할 수 없습니다.\n";
	//		break;
	//	}
	//}

	//cout << "프로그램을 종료합니다.\n";

	//double x, y, z;

	//cout << "두 수를 입력하십시오: ";

	//while (cin >> x >> y)
	//{
	//	try {
	//		z = hmean(x, y);
	//	}

	//	catch (const char* s)
	//	{
	//		cout << s << endl;
	//		cout << "두 수를 새로 입력하세요: ";
	//		continue;
	//	}

	//	cout << x << ", " << y << "의 조화평균은 " << z << "입니다.\n";
	//	cout << "다른 두 수를 입력하십시오(끝내려면 q): ";
	//}

	//cout << "프로그램을 종료합니다. \n";

	//queue<string> cs(2);
	//string temp;

	//while (!cs.isfull())
	//{
	//	cout << "이름을 입력하세요. 도착하신 순서대로 "
	//		"사은품을 드립니다.\n"
	//		"이름: ";
	//	getline(cin, temp);
	//	cs.enqueue(temp);
	//}

	//cout << "큐가 가득 찼으므로, 지금부터 사은품을 나누어 드리겠습니다.\n";

	//while (!cs.isempthy())
	//{
	//	cs.dequeue(temp);
	//	cout << temp << " 님 감사합니다, 안녕히 가십시오. \n";
	//}

	//Tv s42;
	//cout << "42\" TV의 초기 설정 값: \n";
	//s42.settings();
	//s42.onoff();
	//s42.chanup();

	//cout << "\n42\"TV의 변경된 설정값: \n";
	//s42.settings();

	//Remote grey;

	//grey.set_chan(s42, 10);
	//grey.volup(s42);
	//grey.volup(s42);
	//cout << "\n리보콘 사용 후 42\"Tv의 설정값: \n";
	//s42.settings();

	//Tv s58(Tv::On);
	//s58.set_mode();
	//grey.set_chan(s58, 28);
	//cout << "\n58\" TV의 설정 값: \n";
	//s58.settings();



	return 0;
}