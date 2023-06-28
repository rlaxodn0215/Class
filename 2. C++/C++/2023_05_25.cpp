#include<iostream> //istream + ostream
#include<climits>

using namespace std;

int main()
{

	//char ch = 'M';
	//int i = ch;
	//cout << ch << "의 ASCII 코드는" << i << "입니다." << endl;

	//cout << "이 문자 코드에 1을 더해보겠습니다." << endl;
	//ch = ch + 1;

	//i = ch;

	//cout << ch << "의 ASCII 코드는" << i << "입니다." << endl;

	//cout << "cout.put(ch)를 사용하여 char형 변수 ch를 화면에 출력 : ";
	//cout.put(ch);

	//cout.put('!');

	//cout << endl << "종료" << endl;

	//wchar_t st;//유니코드
	

	/*
	Q1. p.129 1.


	*/

	/*int height;

	cout << "키 입력 :___cm\b\b\b\b\b";
	cin >> height;

	const double meter = (double)height / 100;
	const int centimeter = height ;

	cout << meter << "m " << endl;
	cout << centimeter << "cm" << endl;*/

	////3번
	//int a, b, c;//도, 분, 초
	//double decal;

	//cout << "위도를 도, 분, 초 단위로 입력하시오:" << endl;
	//cout << "먼저, 도각을 입력하세요 : ";
	//cin >> a;
	//cout << "다음에, 분각을 입력하시오 : ";
	//cin >> b;
	//cout << "끝으로, 초각을 입력하시오 : ";
	//cin >> c;

	//decal = (double)a + (double)b / 60 + (double)c / (60 * 60);

	//cout << a << "도, " << b << "분, " << c << "초, = "<<decal<<"도" << endl;

	////5번
	//long long int WorldPeople, USPeople;
	//cout << "세계 인구수를 입력하시오 : ";
	//cin >> WorldPeople;
	//cout << "미국의 인구수를 입력하시오 : ";
	//cin >> USPeople;

	//cout << "세계 인구수에서 미국이 차지하는 비중은 " << (double)USPeople * 100 / WorldPeople << "%이다." << endl;

	////7번
	//double mpg, lpk;

	//cout << "유럽 스타일(liter per 100km) :";
	//cin >> lpk;
	//
	//mpg = (62.14*3.875) * (1/lpk);

	//cout << "미국 스타일(mile per gallon) : " << mpg;

    int n = 110011;
    int k = 10;

    int answer = 0;
    string number = "";

    // k진수로 바꾼 수를 문자열로 저장
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

    // 0이 나올때 까지 수를 count한 후 소수인지 판단해서 answer++ 
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
            //소수인지 판단.
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