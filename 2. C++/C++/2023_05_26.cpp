#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>

using namespace std;

//char* getname();

int main()
{
	//const int ArSize = 10;
	//char name[ArSize];
	//char dessert[ArSize];

	//cout << "�̸��� �Է��ϼ���: " << endl;
	//cin.get(name, ArSize).get();
	////cin.ignore();
	//cout << "�����ϴ� ����Ʈ�� �Է��ϼ���: \n";
	//cin.get(dessert, ArSize).get();
	////cin.ignore();
	//cout << "���ִ� " << dessert;
	//cout << " ����Ʈ�� �غ��ϰڽ��ϴ�. " << name << "��!\n";

	/*string s1 = "penguin";
	string s2, s3;

	cout << "string ��ü�� string ��ü�� ������ �� �ִ�: s2 = s1\n";
	s2 = s1;
	cout << "s1: " << s1 << ". s2: " << s2 << endl;
	cout << "string ��ü�� C ��Ÿ�� ���ڿ��� ������ �� �ִ�.\n";
	cout << "s2 = \"buzzard\"\n";
	s2 = "buzzard";
	cout << "s2: " << s2 << endl;
	cout << "string ��ü���� ������ �� �ִ� : s3=s1+s2\n";
	s3 = s1 + s2;
	cout << "s3: " << s3 << endl;
	cout << "string ��ü�� �߰��� �� �ִ�.\n";
	s1 += s2;
	cout << "s1 +=s2 --> s1 = " << s1 << endl;
	s2+="for a day";
	cout << "s2 += \" for a day\" --> s2 = " << s2 << endl;*/



	////_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF || _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(151);

	//double* p3 = new double[3];
	//p3[0] = 0.2;
	//p3[1] = 0.5;
	//p3[2] = 0.8;
	//cout << "p3[1]�� " << p3[1] << "�Դϴ�" << endl;
	//p3 = p3 + 1;
	//cout << "������ p3[0]�� " << p3[0] << " �̰�, ";
	//cout << "p3[1]�� " << p3[1] << "�Դϴ�." << endl;
	//p3 = p3 - 1;
	////delete[] p3;

	////_CrtDumpMemoryLeaks();

	/*double wages[3] = { 10000.0,20000.0,30000.0 };
	short stacks[3] = { 3,2,1 };

	double* pw = wages;
	short* ps = &stacks[0];

	cout << "pw = " << pw << ", *pw = " << *pw << endl;
	pw = pw + 1;
	cout << "pw�����Ϳ� 1�� ����: \n";
	cout << "pw = " << pw << ", *pw = " << *pw<< "\n\n";

	cout << "ps = " << ps << ", *ps = " << *ps << endl;
	ps = ps + 1;
	cout << "ps �����Ϳ� 1�� ����: \n";
	cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";

	cout << "�迭 ǥ��� �� ���ҿ� ����\n";
	cout << "stacks[0] = " << stacks[0]
		<< ", stacks[1] = " << stacks[1] << endl;
	cout << "������ ǥ��� �� ���ҿ� ����\n";
	cout << "*stacks = " << *stacks
		<< ", *(stacks+1) = " << *(stacks + 1) << endl;

	cout << sizeof(wages) << " = wages �迭�� ũ��" << endl;
	cout << sizeof(pw) << " = pw �������� ũ��\n";*/

	//char animal[20] = "bear";
	//const char* bird = "wren";
	//char* ps;

	//cout << animal << " and ";
	//cout << bird << endl;
	////cout<<ps<<endl;

	//cout << "������ ������ �Է��Ͻʽÿ�: ";
	//cin >> animal;
	////cin>>ps;

	//ps = animal;
	//cout << ps << "s!\n";
	//cout << "strcpy() �����: \n";
	//cout << (int*)animal << " : " << animal << endl;
	//cout << (int*)ps << " : " << ps << endl;

	//ps = new char[strlen(animal) + 1];
	//strcpy(ps, animal);
	//cout << "strcpy() ��� �� : \n";
	//cout << (int*)animal << " : " << animal << endl;
	//cout << (int*)ps << " : " << ps << endl;
	//delete[] ps;
	
	/*char* name;

	name = getname();
	cout << (int*)name << " : " << name << endl;
	delete[] name;

	name = getname();
	cout << (int*)name << " : " << name << endl;
	delete[] name;*/
	

	/*struct CandyBar
	{
		string name;
		double weight;
		int kcal;
	};*/

	//Q5.
	/*CandyBar snack = { "Mocha Munch",2.3,350 };

	cout <<"snack name : " << snack.name << endl;
	cout <<"snack weight : " << snack.weight << endl;
	cout << "snack kcal : " << snack.kcal << endl;*/

	//Q6.
	/*CandyBar snacks[3] = { {"mint",5.4,200},{"mother is alien",32.7,567},{"asdasdassddasda",44.8,987}};
	
	cout << "snacks[0] name : " << snacks[0].name << endl;
	cout << "snacks[0] weight : " << snacks[0].weight << endl;
	cout << "snacks[0] kcal : " << snacks[0].kcal << endl;
	cout << "snacks[1] name : " << snacks[1].name << endl;
	cout << "snacks[1] weight : " << snacks[1].weight << endl;
	cout << "snacks[1] kcal : " << snacks[1].kcal << endl;
	cout << "snacks[2] name : " << snacks[2].name << endl;
	cout << "snacks[2] weight : " << snacks[2].weight << endl;
	cout << "snacks[2] kcal : " << snacks[2].kcal << endl;*/


	////Q9.
	/*CandyBar *snacks = new CandyBar[3];

	snacks[0] = { "mint",5.4,200 };
	snacks[1] = { "mother is alien",32.7,567 };
	snacks[2] = { "asdasdassddasda",44.8,987 };
	
	cout << "snacks[0] name : " << snacks[0].name << endl;
	cout << "snacks[0] weight : " << snacks[0].weight << endl;
	cout << "snacks[0] kcal : " << snacks[0].kcal << endl;
	cout << "snacks[1] name : " << snacks[1].name << endl;
	cout << "snacks[1] weight : " << snacks[1].weight << endl;
	cout << "snacks[1] kcal : " << snacks[1].kcal << endl;
	cout << "snacks[2] name : " << snacks[2].name << endl;
	cout << "snacks[2] weight : " << snacks[2].weight << endl;
	cout << "snacks[2] kcal : " << snacks[2].kcal << endl;

	delete[] snacks;*/

	return 0;
}

//char* getname()
//{
//	char temp[80];
//	cout << "�̸��� �Է��ϼ��� : ";
//	cin >> temp;
//	char* pn = new char[strlen(temp) + 1];
//	strcpy(pn, temp);
//
//	return pn;
//}