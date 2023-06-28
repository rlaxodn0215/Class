#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<math.h>

using namespace std;

int main()
{
	//struct Pizza
	//{
	//	string name;
	//	int diameter;
	//	double weight;
	//};

	////Q7
	//Pizza pizza;

	//cout << "피자 회사의 이름 : ";
	//getline(cin, pizza.name);
	//cout << "피자의 지름(cm) : ";
	//cin>>pizza.diameter;
	//cout << "피자의 중량(kg) : ";
	//cin>> pizza.weight;

	//cout << endl;
	//cout << "피자 회사의 이름 : " << pizza.name << endl;
	//cout << "피자의 지름 : " << pizza.diameter <<"cm" << endl;
	//cout << "피자의 중량 : " << pizza.weight <<"kg" << endl;

	////Q8
	//Pizza* pizza = new Pizza;

	//cout << "피자의 지름(cm) : ";
	//cin >> pizza->diameter;
	//cin.get();
	//cout << "피자 회사의 이름 : ";
	//getline(cin, pizza->name);
	//cout << "피자의 중량(kg) : ";
	//cin >> pizza->weight;

	//cout << endl;
	//cout << "피자 회사의 이름 : " << pizza->name << endl;
	//cout << "피자의 지름 : " << pizza->diameter << "cm" << endl;
	//cout << "피자의 중량 : " << pizza->weight << "kg" << endl;
	//delete pizza;

	/*int x=0;

	cout << "대입표현식 x=100의 값은 ";
	cout << (x = 100) << endl;

	cout << (x > 3) << endl;

	cout.setf(ios_base::boolalpha);

	cout << (x < 3) << endl;*/

	/*string word, reverseWord;
	cout << "단어를 입력하시오 : ";
	cin>>word;

	for (int i = word.size() - 1; i >= 0; i--)
	{
		reverseWord += word[i];
	}

	int count = 0;
	for (int i = 0; i < word.size(); i++)
	{
		if (reverseWord[i] == word[i])
			count++;
	}

	if (count == word.size())
	{
		cout << "거꾸로 출력한 문자 : " << reverseWord << endl;
		cout << "회문입니다." << endl;
	}

	else
	{
		cout << "거꾸로 출력한 문자 : " << reverseWord << endl;
		cout << "회문이 아닙니다." << endl;
	}*/

	/*string word;
	cout << "단어를 하난 입력하세요 : ";
	cin >> word;

	char temp;
	int i, j;
	for (j = 0, i = word.size() - 1; j < i; --i, ++j)
	{
		temp = word[i];
		word[i] = word[j];
		word[j] = temp;
	}

	cout << word << endl;*/

	/*int pr[3] = { 1,2,3 };

	for (int& a : pr)
	{
		a += 3;
	}

	for (int a : pr)
	{
		cout << a << endl;
	}*/

	/*char ch;
	int count = 0;
	cin.get(ch);

	while (ch != '#')
	{
		cout << ch;
		++count;
		cin.get(ch);
	}

	cout << endl << count << "문자를 읽었습니다." << endl;*/

	/*int n;

	cout << "라인 숫자 입력 (1~10) : ";
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < 2*n; j++)
		{

			if (j>n-i && j<n+i)
				cout << abs(n - j) + 1;

			else
				cout << ' ';
			
		}
		cout << endl;
	}*/
	

	////Q7
	//struct Car
	//{
	//	char name[20];
	//	int year;
	//};

	//int carNum;
	//cout << "몇 대의 차를 목록으로 관리하시겠습니까? ";
	//cin >> carNum;

	//Car* car = new Car[carNum];

	//int n = 0;
	//while (n<carNum)
	//{
	//	cout << "자동차 #" << n+1 << endl;
	//	cout << "제작 업체: ";
	//	cin >> car[n].name;
	//	cout << "제작년도: ";
	//	cin >> car[n].year;
	//	n++;
	//}

	//cout << endl << "현재 귀하가 보유하고 있는 자동차의 목록은 다음과 같습니다." << endl;

	//for (int i = 0; i < carNum; i++)
	//{
	//	cout << car[i].year << "년형 " << car[i].name << endl;
	//}


	//delete[] car;
	//

	////Q8.
	//char sentence[100];
	//int num=0;

	//cout << "영어 단어들을 입력하세요 (끝내려면 done을 입력) : ";
	//cin.getline(sentence,100);
	//
	//int i = 0,j = 0;
	//while (1)
	//{
	//	char word[20]="";

	//	i = 0;
	//	while (sentence[i+j] !=' ' && i+j<strlen(sentence))
	//	{
	//		word[i] = sentence[i+j];
	//		i++;
	//	}
	//	j += i+1;

	//	if (!(strcmp(word, "done")))
	//	{
	//		break;
	//	}

	//	num++;
	//}

	//cout << "총 " << num << " 단어가 입력되었습니다." << endl;

	return 0;
}