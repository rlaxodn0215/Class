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

	//cout << "���� ȸ���� �̸� : ";
	//getline(cin, pizza.name);
	//cout << "������ ����(cm) : ";
	//cin>>pizza.diameter;
	//cout << "������ �߷�(kg) : ";
	//cin>> pizza.weight;

	//cout << endl;
	//cout << "���� ȸ���� �̸� : " << pizza.name << endl;
	//cout << "������ ���� : " << pizza.diameter <<"cm" << endl;
	//cout << "������ �߷� : " << pizza.weight <<"kg" << endl;

	////Q8
	//Pizza* pizza = new Pizza;

	//cout << "������ ����(cm) : ";
	//cin >> pizza->diameter;
	//cin.get();
	//cout << "���� ȸ���� �̸� : ";
	//getline(cin, pizza->name);
	//cout << "������ �߷�(kg) : ";
	//cin >> pizza->weight;

	//cout << endl;
	//cout << "���� ȸ���� �̸� : " << pizza->name << endl;
	//cout << "������ ���� : " << pizza->diameter << "cm" << endl;
	//cout << "������ �߷� : " << pizza->weight << "kg" << endl;
	//delete pizza;

	/*int x=0;

	cout << "����ǥ���� x=100�� ���� ";
	cout << (x = 100) << endl;

	cout << (x > 3) << endl;

	cout.setf(ios_base::boolalpha);

	cout << (x < 3) << endl;*/

	/*string word, reverseWord;
	cout << "�ܾ �Է��Ͻÿ� : ";
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
		cout << "�Ųٷ� ����� ���� : " << reverseWord << endl;
		cout << "ȸ���Դϴ�." << endl;
	}

	else
	{
		cout << "�Ųٷ� ����� ���� : " << reverseWord << endl;
		cout << "ȸ���� �ƴմϴ�." << endl;
	}*/

	/*string word;
	cout << "�ܾ �ϳ� �Է��ϼ��� : ";
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

	cout << endl << count << "���ڸ� �о����ϴ�." << endl;*/

	/*int n;

	cout << "���� ���� �Է� (1~10) : ";
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
	//cout << "�� ���� ���� ������� �����Ͻðڽ��ϱ�? ";
	//cin >> carNum;

	//Car* car = new Car[carNum];

	//int n = 0;
	//while (n<carNum)
	//{
	//	cout << "�ڵ��� #" << n+1 << endl;
	//	cout << "���� ��ü: ";
	//	cin >> car[n].name;
	//	cout << "���۳⵵: ";
	//	cin >> car[n].year;
	//	n++;
	//}

	//cout << endl << "���� ���ϰ� �����ϰ� �ִ� �ڵ����� ����� ������ �����ϴ�." << endl;

	//for (int i = 0; i < carNum; i++)
	//{
	//	cout << car[i].year << "���� " << car[i].name << endl;
	//}


	//delete[] car;
	//

	////Q8.
	//char sentence[100];
	//int num=0;

	//cout << "���� �ܾ���� �Է��ϼ��� (�������� done�� �Է�) : ";
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

	//cout << "�� " << num << " �ܾ �ԷµǾ����ϴ�." << endl;

	return 0;
}