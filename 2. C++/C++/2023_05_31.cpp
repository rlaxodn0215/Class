#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<math.h>
#include<fstream> //파일 입출력 라이브러리

using namespace std;

int main()
{
	/*double Accelation, FightSpeed, Length;

	cout << "Speed and Accelation : ";
	cin >> FightSpeed;
	cin >> Accelation;

	Length = pow(FightSpeed,2)/(2 * Accelation);

	cout << "Minimun runaway length : " << Length << endl;*/

	/*double x1, y1, x2, y2,length;

	cout << "x1 y1 : ";
	cin >> x1 >> y1;
	cout << "x2 y2 : ";
	cin >> x2 >> y2;

	length = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	cout << "length : " << length << endl;*/

	//ofstream outfile;					// 객체선언 (파일 쓰기)
	//outfile.open("cc.txt");				// 파일열기(생성)
	//outfile << "adasdsasd" << endl;		// 문자입력
	//outfile.close();					// 파일 닫기

	//ifstream infile;					// 파일 읽어오기
	//infile.open("cc.txt");
	//if (!infile.is_open())
	//{
	//	cout << "xxx is not open" << endl;
	//	return 0;
	//}
	//string str;
	//infile >> str;
	//cout << str << endl;

	//infile.close();
	//char automobile[50];
	//int year;
	//double a_price;
	//double d_price;

	//ofstream outFile;
	//outFile.open("carinfo.txt");

	//cout << "자동차 메이커와 차종을 입력하세요: ";
	//cin.getline(automobile, 50);
	//cout << "연식을 입력하세요: ";
	//cin >> year;
	//cout << "구입 가격을 입력하시오: ";
	//cin >> a_price;
	//d_price = 0.913 * a_price;

	//cout << fixed;
	//cout.precision(2);
	//cout.setf(ios_base::showpoint);
	//cout << "메이커와 차종: " << automobile << endl;
	//cout << "연식: " << year << endl;
	//cout << "구입가격$" << a_price << endl;
	//cout << "현재가격$" << d_price << endl;

	//outFile << fixed;
	//outFile.precision(2);
	//outFile.setf(ios_base::showpoint);
	//outFile << "메이커와 차종: " << automobile << endl;
	//outFile << "연식: " << year << endl;
	//outFile << "구입 가격 $" << a_price << endl;
	//outFile << "현재 가격 $" << d_price << endl;

	//outFile.close();

	//const int SIZE = 60;
	//char filename[SIZE];
	//ifstream inFile;
	//cout << "데이터 파일의 이름을 입력하세요: ";
	//cin.getline(filename, SIZE);
	//inFile.open(filename);
	//if (!(inFile.is_open()))
	//{
	//	cout << filename << " 파일을 열 수 없습니다." << endl;
	//	cout << "프로그램을 종료합니다." << endl;
	//	exit(EXIT_FAILURE);
	//}

	//double value;
	//double sum = 0.0;
	//int count = 0;
	//inFile >> value;
	//while (inFile.good())
	//{
	//	++count;
	//	sum += value;
	//	inFile >> value;
	//}

	//if (inFile.eof())
	//{
	//	cout << "파일 끝에 도달했습니다.\n";
	//}

	//else if (inFile.fail())
	//{
	//	cout<<"데이터 불일치로 입력이 종료되었습니다." << endl;
	//}

	//else
	//{
	//	cout << "알 수 없는 이유로 입력이 종료되었습니다" << endl;
	//}

	//if (count == 0)
	//{
	//	cout << "데이터가 없습니다." << endl;
	//}

	//else
	//{
	//	cout << "읽은 항목의 개수: " << count << endl;
	//	cout << "합계: " << sum << endl;
	//	cout << "평균: " << sum / count << endl;
	//}

	//inFile.close();
	
	struct BOP
	{
		string fullname;
		string title;
		string bopname;
		int preference;
	};

	char choice=0;
	while (choice !='q')
	{
		//system("cls");

		cout << "Benevolent Order of Programmers" << endl;
		cout << "a. 회원등록" << "\t\t" << "b. 실명으로 열람" << endl;
		cout << "c. 직함으로 열람" << "\t\t" << "d. BOP 아이디로 열람" << endl;
		cout << "e. 회원이 지정한 것으로 열람" << "\t\t" << "q. 종료" << endl;
		cin >> choice;

		

		switch (choice)
		{
		case 97://회원 등록
		{
			BOP* bop = new BOP;

			cout << "회원등록" << endl;
			cout << "회원 지정 열람방식 번호 입력(1.이름 2.직함 3. BOP_ID): ";
			cin >> bop->preference;
			cin.ignore();
			cout<< "이름 입력: ";
			getline(cin,bop->fullname);
			cout << "직함 입력: ";
			getline(cin,bop->title);
			cout << "BOP ID 입력: ";
			getline(cin,bop->bopname);

			cin.ignore();

			ofstream outfile;
			outfile.open("bop.txt",ios::app);
			if (!outfile.is_open())
			{
				cout << "파일을 열 수 없습니다." << endl;
				break;
			}
			outfile << bop->preference << "\t" << bop->fullname << "\t" << bop->title << "\t" << bop->bopname << endl;

			outfile.close();
			delete bop;
		}
			break;

		case 98://실명으로 열람
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "파일을 열 수 없습니다." << endl;
				break;
			}

			while (infile.good())
			{
				infile >> value;
				if (count % 4 == 1)
				{
					cout << value << endl;
				}
				++count;
			}
			
			infile.close();
		}
			break;

		case 99://직함으로 열람
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "파일을 열 수 없습니다." << endl;
				break;
			}

			while (infile.good())
			{
				infile >> value;
				if (count % 4 == 2)
				{
					cout << value << endl;
				}
				++count;
			}

			infile.close();
		}
			break;

		case 100: // BOP아이디로 열람
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "파일을 열 수 없습니다." << endl;
				break;
			}

			while (infile.good())
			{
				infile >> value;
				if (count % 4 == 3)
				{
					cout << value << endl;
				}
				++count;
			}

			infile.close();
		}
			break;
		case 101://회원이 지정한 것으로 열람
		{
			int value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "파일을 열 수 없습니다." << endl;
				break;
			}

			while (infile.good())
			{

				infile >> value;

				if (count % 4 == 0)
				{
					switch (value)
					{
					case 1:
					{
						string str;
						infile >> str; ++count;
						cout << str << endl;
						infile >> str; ++count;
						infile >> str; ++count;
					}
						break;

					case 2:
					{
						string str;
						infile >> str; ++count;
						infile >> str; ++count;
						cout << str << endl;
						infile >> str; ++count;
					}
						break;
					case 3:
						{
							string str;
							infile >> str; ++count;
							infile >> str; ++count;
							infile >> str; ++count;
							cout << str << endl;
						}
						break;
					default:
					{
						cout << "잘못된 데이터 입력이 있습니다." << endl;
					}
						break;
					}
				}
				++count;
			}
			infile.close();
		}
			break;


		case 113:
			break;
		default:
		{
			cout << "잘못된 번호를 입력하였습니다. 다시 입력해 주세요" << endl;
		}
			break;
		}

		cout << endl;
	}

	cout << "프로그램이 종료되었습니다" << endl;

	return 0;
}
