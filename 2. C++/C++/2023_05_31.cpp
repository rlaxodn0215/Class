#define _CRT_SECURE_NO_WARNINGS
#include<iostream> //istream + ostream
#include<climits>
#include<string>
#include <cstring>
#include<stdlib.h>
#include<crtdbg.h>
#include<vector>
#include<math.h>
#include<fstream> //���� ����� ���̺귯��

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

	//ofstream outfile;					// ��ü���� (���� ����)
	//outfile.open("cc.txt");				// ���Ͽ���(����)
	//outfile << "adasdsasd" << endl;		// �����Է�
	//outfile.close();					// ���� �ݱ�

	//ifstream infile;					// ���� �о����
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

	//cout << "�ڵ��� ����Ŀ�� ������ �Է��ϼ���: ";
	//cin.getline(automobile, 50);
	//cout << "������ �Է��ϼ���: ";
	//cin >> year;
	//cout << "���� ������ �Է��Ͻÿ�: ";
	//cin >> a_price;
	//d_price = 0.913 * a_price;

	//cout << fixed;
	//cout.precision(2);
	//cout.setf(ios_base::showpoint);
	//cout << "����Ŀ�� ����: " << automobile << endl;
	//cout << "����: " << year << endl;
	//cout << "���԰���$" << a_price << endl;
	//cout << "���簡��$" << d_price << endl;

	//outFile << fixed;
	//outFile.precision(2);
	//outFile.setf(ios_base::showpoint);
	//outFile << "����Ŀ�� ����: " << automobile << endl;
	//outFile << "����: " << year << endl;
	//outFile << "���� ���� $" << a_price << endl;
	//outFile << "���� ���� $" << d_price << endl;

	//outFile.close();

	//const int SIZE = 60;
	//char filename[SIZE];
	//ifstream inFile;
	//cout << "������ ������ �̸��� �Է��ϼ���: ";
	//cin.getline(filename, SIZE);
	//inFile.open(filename);
	//if (!(inFile.is_open()))
	//{
	//	cout << filename << " ������ �� �� �����ϴ�." << endl;
	//	cout << "���α׷��� �����մϴ�." << endl;
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
	//	cout << "���� ���� �����߽��ϴ�.\n";
	//}

	//else if (inFile.fail())
	//{
	//	cout<<"������ ����ġ�� �Է��� ����Ǿ����ϴ�." << endl;
	//}

	//else
	//{
	//	cout << "�� �� ���� ������ �Է��� ����Ǿ����ϴ�" << endl;
	//}

	//if (count == 0)
	//{
	//	cout << "�����Ͱ� �����ϴ�." << endl;
	//}

	//else
	//{
	//	cout << "���� �׸��� ����: " << count << endl;
	//	cout << "�հ�: " << sum << endl;
	//	cout << "���: " << sum / count << endl;
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
		cout << "a. ȸ�����" << "\t\t" << "b. �Ǹ����� ����" << endl;
		cout << "c. �������� ����" << "\t\t" << "d. BOP ���̵�� ����" << endl;
		cout << "e. ȸ���� ������ ������ ����" << "\t\t" << "q. ����" << endl;
		cin >> choice;

		

		switch (choice)
		{
		case 97://ȸ�� ���
		{
			BOP* bop = new BOP;

			cout << "ȸ�����" << endl;
			cout << "ȸ�� ���� ������� ��ȣ �Է�(1.�̸� 2.���� 3. BOP_ID): ";
			cin >> bop->preference;
			cin.ignore();
			cout<< "�̸� �Է�: ";
			getline(cin,bop->fullname);
			cout << "���� �Է�: ";
			getline(cin,bop->title);
			cout << "BOP ID �Է�: ";
			getline(cin,bop->bopname);

			cin.ignore();

			ofstream outfile;
			outfile.open("bop.txt",ios::app);
			if (!outfile.is_open())
			{
				cout << "������ �� �� �����ϴ�." << endl;
				break;
			}
			outfile << bop->preference << "\t" << bop->fullname << "\t" << bop->title << "\t" << bop->bopname << endl;

			outfile.close();
			delete bop;
		}
			break;

		case 98://�Ǹ����� ����
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "������ �� �� �����ϴ�." << endl;
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

		case 99://�������� ����
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "������ �� �� �����ϴ�." << endl;
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

		case 100: // BOP���̵�� ����
		{
			string value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "������ �� �� �����ϴ�." << endl;
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
		case 101://ȸ���� ������ ������ ����
		{
			int value;
			int count = 0;

			ifstream infile;
			infile.open("bop.txt");
			if (!infile.is_open())
			{
				cout << "������ �� �� �����ϴ�." << endl;
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
						cout << "�߸��� ������ �Է��� �ֽ��ϴ�." << endl;
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
			cout << "�߸��� ��ȣ�� �Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ���" << endl;
		}
			break;
		}

		cout << endl;
	}

	cout << "���α׷��� ����Ǿ����ϴ�" << endl;

	return 0;
}
