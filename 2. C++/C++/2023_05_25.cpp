#include<iostream> //istream + ostream
#include<climits>

using namespace std;

int main()
{

	//char ch = 'M';
	//int i = ch;
	//cout << ch << "�� ASCII �ڵ��" << i << "�Դϴ�." << endl;

	//cout << "�� ���� �ڵ忡 1�� ���غ��ڽ��ϴ�." << endl;
	//ch = ch + 1;

	//i = ch;

	//cout << ch << "�� ASCII �ڵ��" << i << "�Դϴ�." << endl;

	//cout << "cout.put(ch)�� ����Ͽ� char�� ���� ch�� ȭ�鿡 ��� : ";
	//cout.put(ch);

	//cout.put('!');

	//cout << endl << "����" << endl;

	//wchar_t st;//�����ڵ�
	

	/*
	Q1. p.129 1.


	*/

	/*int height;

	cout << "Ű �Է� :___cm\b\b\b\b\b";
	cin >> height;

	const double meter = (double)height / 100;
	const int centimeter = height ;

	cout << meter << "m " << endl;
	cout << centimeter << "cm" << endl;*/

	////3��
	//int a, b, c;//��, ��, ��
	//double decal;

	//cout << "������ ��, ��, �� ������ �Է��Ͻÿ�:" << endl;
	//cout << "����, ������ �Է��ϼ��� : ";
	//cin >> a;
	//cout << "������, �а��� �Է��Ͻÿ� : ";
	//cin >> b;
	//cout << "������, �ʰ��� �Է��Ͻÿ� : ";
	//cin >> c;

	//decal = (double)a + (double)b / 60 + (double)c / (60 * 60);

	//cout << a << "��, " << b << "��, " << c << "��, = "<<decal<<"��" << endl;

	////5��
	//long long int WorldPeople, USPeople;
	//cout << "���� �α����� �Է��Ͻÿ� : ";
	//cin >> WorldPeople;
	//cout << "�̱��� �α����� �Է��Ͻÿ� : ";
	//cin >> USPeople;

	//cout << "���� �α������� �̱��� �����ϴ� ������ " << (double)USPeople * 100 / WorldPeople << "%�̴�." << endl;

	////7��
	//double mpg, lpk;

	//cout << "���� ��Ÿ��(liter per 100km) :";
	//cin >> lpk;
	//
	//mpg = (62.14*3.875) * (1/lpk);

	//cout << "�̱� ��Ÿ��(mile per gallon) : " << mpg;

    int n = 110011;
    int k = 10;

    int answer = 0;
    string number = "";

    // k������ �ٲ� ���� ���ڿ��� ����
    while (1)
    {
        number += (n % k) + 48;
        n /= k;
        if (n == 0) break;
    }

    for (int i = 0; i < (number.size() / 2); i++)
    {
        char temp = number[i];
        number[i] = number[number.size() - i - 1];
        number[number.size() - i - 1] = temp;
    }

    // 0�� ���ö� ���� ���� count�� �� �Ҽ����� �Ǵ��ؼ� answer++ 
    string checkNum = "";
    int ptr = 0;
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != '0')
        {
            checkNum += number[i];
            ptr++;
        }

        if (number[i] == '0' || i == number.size() - 1)
        {
            //�Ҽ����� �Ǵ�.
            //if (checkNum[ptr - 1] == '2')
            //{
            //   checkNum = "";
            //    ptr = 0;
            //    continue;
            //}

            int num = 0;
            int n = 1;
            for (int i = ptr - 1; i >= 0; i--)
            {
                num += (checkNum[i] - 48) * n;
                n *= 10;
            }

            if (num != 1 && num!=0)
            {
                int j;
                for (j = 3; j * j < num; j += 2)
                {
                    if (num % j == 0)
                    {
                        checkNum = "";
                        ptr = 0;
                        break;
                    }
                }

                if (j * j > num) answer++;
            }
            checkNum = "";
            ptr = 0;
        }
    }

	return 0;
}