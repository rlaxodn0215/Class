#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include<list>
#include<iterator>
#include<set>

using namespace std;

//struct Review
//{
//	string title;
//	int rating;
//};
//
//bool operator<(const Review& r1, const Review& r2)
//{
//	if (r1.title < r2.title)
//		return true;
//	else if (r1.title == r2.title && r1.rating < r2.rating)
//		return true;
//	else
//		return false;
//}
//bool worseThan(const Review& r1, const Review& r2)
//{
//	if (r1.rating < r2.rating)
//		return true;
//	else
//		return false;
//
//}
//
//bool FillReview(Review& rr)
//{
//	cout << "å ������ �Է��ϼ���(�������� quit�� �Է�): ";
//	getline(cin, rr.title);
//	if (rr.title == "quit")
//	{
//		return false;
//	}
//
//	cout << "å ���(0-10)�� �Է��Ͻʽÿ�: ";
//	cin >> rr.rating;
//
//	if (!cin)
//		return false;
//
//	while(cin.get() != '\n')
//	{
//		continue;
//	}
//
//	return true;
//}
//
//void ShowReview(const Review& rr)
//{
//	cout << rr.rating << "\t" << rr.title << endl;
//}

//void outint(int n) { cout << n << " "; }

int main()
{


	//const int N = 6;
	//string s1[N] = { "buffoon","thinkers","for","heavy","can","for" };
	//string s2[N] = { "metal","any","food","elegant","deliver","for" };
	//set<string> A(s1, s1 + N);
	//set<string> B(s2, s2 + N);

	//ostream_iterator<string, char> out(cout, " ");
	//cout << "���� A: ";
	//copy(A.begin(), A.end(), out);
	//cout << endl;
	//cout << "���� B: ";
	//copy(B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A�� B�� ������: \n";
	//set_union(A.begin(),A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A�� B�� ������: \n";
	//set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A�� B�� ������: \n";
	//set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//set<string> C;
	//cout << "���� C: \n";
	//set_union(A.begin(), A.end(), B.begin(), B.end(), insert_iterator<set<string>>(C, C.begin()));
	//copy(C.begin(), C.end(), out);
	//cout << endl;

	//string s3("grungy");
	//C.insert(s3);
	//cout << "������ ���� ���� C: \n";
	//copy(C.begin(), C.end(), out);


	//list<int> one(5, 2);
	//int stuff[5] = { 1,2,4,8,6 };
	//list<int> two;
	//two.insert(two.begin(), stuff, stuff + 5);
	//int more[6] = { 6,4,2,4,6,5 };
	//list<int> three(two);
	//three.insert(three.end(), more, more + 6);
	//cout << "����Ʈ one: ";
	//for_each(one.begin(), one.end(), outint);
	//cout << endl << "����Ʈ two: ";
	//for_each(two.begin(), two.end(), outint);
	//cout << endl << "����Ʈ three: ";
	//for_each(three.begin(), three.end(), outint);
	//three.remove(2);
	//cout << endl << "���� ���� ����Ʈ three: ";
	//for_each(three.begin(), three.end(), outint);
	//cout << endl << "����Ʈ one: ";
	//for_each(one.begin(), one.end(), outint);
	//three.unique();
	//cout << endl << "����ȭ ���� ����Ʈ three: ";
	//for_each(three.begin(), three.end(), outint);
	//three.sort();
	//three.unique();
	//cout << endl << "���İ� ����ȭ ���� ����Ʈ three: ";
	//for_each(three.begin(), three.end(), outint);
	//two.sort();
	//three.merge(two);
	//cout << endl << "���ĵ� ����Ʈ two�� ����Ʈ three�� �պ�: ";
	//for_each(three.begin(), three.end(), outint);
	//cout << endl;

	//vector<Review> books;
	//Review temp;
	//while (FillReview(temp))
	//{
	//	books.push_back(temp);
	//}

	//if (books.size() > 0)
	//{
	//	cout << "�����մϴ�. ����� ������ ���� " << books.size() << "���� å ����� �Է��ϼ̽��ϴ�.\n" << "���\t����\n";

	//	for_each(books.begin(), books.end(), ShowReview);

	//	sort(books.begin(), books.end());
	//	cout << "å ������ �������� ����: \n���";
	//}

	//int num = books.size();

	//if (num > 0)
	//{
	//	cout << "�����մϴ�. ����� ������ ���� �Է��ϼ̽��ϴ�. \n" << "���\t����\n";
	//	for (int i = 0; i < num; i++)
	//	{
	//		ShowReview(books[i]);
	//	}

	//	cout << "�� �� �� ����Ѵ�: \n" << "���\t����\n";

	//	vector<Review>::iterator pr;
	//	for (pr = books.begin(); pr != books.end(); pr++)
	//	{
	//		ShowReview(*pr);
	//	}

	//	vector<Review> oldlist(books);

	//	if (num > 3)
	//	{
	//		books.erase(books.begin() + 1, books.begin() + 3);
	//		cout << "������ ��: \n";
	//		for (pr = books.begin(); pr != books.end(); pr++)
	//		{
	//			ShowReview(*pr);
	//		}
	//	}
	//	books.swap(oldlist);
	//	cout << "oldlist�� books�� ��ȯ�� ��: \n";
	//	for (pr = books.begin(); pr != books.end(); pr++)
	//	{
	//		ShowReview(*pr);
	//	}


	//}

	//else
	//	cout << "�Է��� ���� ����, ���� ���� �����ϴ�.\n";

	//vector<int> rating(NUM);
	//vector<string> titles(NUM);

	//cout << NUM << "���� å ����� å ��� (0-10)�� �Է��ϼ���.\n";
	//int i;

	//for (i = 0; i < NUM; i++)
	//{
	//	cout << i + 1 << "���� å ������ �Է��ϼ���: ";
	//	getline(cin, titles[i]);
	//	cout << i + 1 << "�� å�� ��� (0-10)�� �Է��ϼ���: : ";
	//	cin >> rating[i];
	//	cin.get();
	//}

	//cout << "�����մϴ�. ����� ������ ���� �Է��ϼ̽��ϴ�: \n"
	//	<< "���\t����\n";

	//for (i = 0; i < NUM; i++)
	//{
	//	cout << rating[i] << "\t" << titles[i] << endl;
	//}

	//string one("Lottery Winner!");
	//cout << one << endl;
	//string two(20, '$');
	//cout << two << endl;
	//string three(one);
	//cout << three << endl;
	//one += " Oops!";
	//cout << one << endl;
	//two = "Sorry! that was ";
	//three[0] = 'P';
	//string four;
	//four = two + three;
	//cout << four << endl;
	//char alls[] = "All's well that ends well";
	//string five(alls, 20);
	//cout << five << "!\n";
	//string six(alls + 6, alls + 10);
	//cout << six << ", ";
	//string seven(&five[6], &five[10]);
	//cout << seven << "...\n";
	//string eight(four, 7, 16);
	//cout << eight << "in motion" << endl;

	//string empty;
	//string small = "bit";
	//string larger = "Elephants are a girl's best friend";
	//cout << "ũ��\n";
	//cout << "\tempty: " << empty.size()	<< endl;
	//cout << "\tsmall: " << small.size() << endl;
	//cout << "\tlarger: " << larger.size() << endl;
	//cout << "�뷮: \n";
	//cout << "\tempthy: " << empty.capacity() << endl;
	//cout << "\tsmall: " << small.capacity() << endl;
	//cout << "\tlarger: " << larger.capacity() << endl;
	//empty.reserve(50);
	//cout << "empty.reserve(50) ���� �뷮: " << empty.capacity() << endl;

	return 0;
}