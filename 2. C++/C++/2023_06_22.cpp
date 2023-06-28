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
//	cout << "책 제목을 입력하세요(끝내려면 quit를 입력): ";
//	getline(cin, rr.title);
//	if (rr.title == "quit")
//	{
//		return false;
//	}
//
//	cout << "책 등급(0-10)을 입력하십시오: ";
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
	//cout << "집합 A: ";
	//copy(A.begin(), A.end(), out);
	//cout << endl;
	//cout << "집합 B: ";
	//copy(B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A와 B의 합집합: \n";
	//set_union(A.begin(),A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A와 B의 교집합: \n";
	//set_intersection(A.begin(), A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//cout << "A외 B의 차집합: \n";
	//set_difference(A.begin(), A.end(), B.begin(), B.end(), out);
	//cout << endl;

	//set<string> C;
	//cout << "집합 C: \n";
	//set_union(A.begin(), A.end(), B.begin(), B.end(), insert_iterator<set<string>>(C, C.begin()));
	//copy(C.begin(), C.end(), out);
	//cout << endl;

	//string s3("grungy");
	//C.insert(s3);
	//cout << "삽입한 후의 집합 C: \n";
	//copy(C.begin(), C.end(), out);


	//list<int> one(5, 2);
	//int stuff[5] = { 1,2,4,8,6 };
	//list<int> two;
	//two.insert(two.begin(), stuff, stuff + 5);
	//int more[6] = { 6,4,2,4,6,5 };
	//list<int> three(two);
	//three.insert(three.end(), more, more + 6);
	//cout << "리스트 one: ";
	//for_each(one.begin(), one.end(), outint);
	//cout << endl << "리스트 two: ";
	//for_each(two.begin(), two.end(), outint);
	//cout << endl << "리스트 three: ";
	//for_each(three.begin(), three.end(), outint);
	//three.remove(2);
	//cout << endl << "접목 후의 리스트 three: ";
	//for_each(three.begin(), three.end(), outint);
	//cout << endl << "리스트 one: ";
	//for_each(one.begin(), one.end(), outint);
	//three.unique();
	//cout << endl << "단일화 후의 리스트 three: ";
	//for_each(three.begin(), three.end(), outint);
	//three.sort();
	//three.unique();
	//cout << endl << "정렬과 단일화 후의 리스트 three: ";
	//for_each(three.begin(), three.end(), outint);
	//two.sort();
	//three.merge(two);
	//cout << endl << "정렬된 리스트 two를 리스트 three에 합병: ";
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
	//	cout << "감사합니다. 당신은 다음과 같이 " << books.size() << "개의 책 등급을 입력하셨습니다.\n" << "등급\t제목\n";

	//	for_each(books.begin(), books.end(), ShowReview);

	//	sort(books.begin(), books.end());
	//	cout << "책 제목을 기준으로 정령: \n등급";
	//}

	//int num = books.size();

	//if (num > 0)
	//{
	//	cout << "감사합니다. 당신은 다음과 같이 입력하셨습니다. \n" << "등급\t제목\n";
	//	for (int i = 0; i < num; i++)
	//	{
	//		ShowReview(books[i]);
	//	}

	//	cout << "한 번 더 출력한다: \n" << "등급\t제목\n";

	//	vector<Review>::iterator pr;
	//	for (pr = books.begin(); pr != books.end(); pr++)
	//	{
	//		ShowReview(*pr);
	//	}

	//	vector<Review> oldlist(books);

	//	if (num > 3)
	//	{
	//		books.erase(books.begin() + 1, books.begin() + 3);
	//		cout << "삭제한 후: \n";
	//		for (pr = books.begin(); pr != books.end(); pr++)
	//		{
	//			ShowReview(*pr);
	//		}
	//	}
	//	books.swap(oldlist);
	//	cout << "oldlist와 books를 교환한 후: \n";
	//	for (pr = books.begin(); pr != books.end(); pr++)
	//	{
	//		ShowReview(*pr);
	//	}


	//}

	//else
	//	cout << "입력한 것이 없어, 얻은 것이 없습니다.\n";

	//vector<int> rating(NUM);
	//vector<string> titles(NUM);

	//cout << NUM << "개의 책 제목과 책 등급 (0-10)을 입력하세요.\n";
	//int i;

	//for (i = 0; i < NUM; i++)
	//{
	//	cout << i + 1 << "번의 책 제목을 입력하세요: ";
	//	getline(cin, titles[i]);
	//	cout << i + 1 << "번 책의 등급 (0-10)을 입력하세요: : ";
	//	cin >> rating[i];
	//	cin.get();
	//}

	//cout << "감사합니다. 당신은 다음과 같이 입력하셨습니다: \n"
	//	<< "등급\t제목\n";

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
	//cout << "크기\n";
	//cout << "\tempty: " << empty.size()	<< endl;
	//cout << "\tsmall: " << small.size() << endl;
	//cout << "\tlarger: " << larger.size() << endl;
	//cout << "용량: \n";
	//cout << "\tempthy: " << empty.capacity() << endl;
	//cout << "\tsmall: " << small.capacity() << endl;
	//cout << "\tlarger: " << larger.capacity() << endl;
	//empty.reserve(50);
	//cout << "empty.reserve(50) 이후 용량: " << empty.capacity() << endl;

	return 0;
}