#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include <time.h>


int main()
{
	////1번
	//int InputNumber, OutputCardinal;
	//char changeNum[100]="";

	//printf("값을 입력하시오 : ");
	//scanf("%d", &InputNumber);
	//getchar();
	//printf("몇 진수로 변환 : ");
	//scanf("%d", &OutputCardinal);
	//getchar();

	//int i = 0;
	//while (1)
	//{
	//	int rest;
	//	rest=InputNumber% OutputCardinal;

	//	if (rest >= 0 && rest <= 9)
	//	{
	//		changeNum[i] = rest + 48;
	//		i++;
	//	}

	//	else
	//	{
	//		changeNum[i] = rest + 55;
	//		i++;
	//	}

	//	InputNumber /= OutputCardinal;
	//	if (InputNumber == 0) break;
	//}
	//
	//for (int i = strlen(changeNum) - 1; i >= 0; i--)
	//{
	//	printf("%c", changeNum[i]);
	//}

	//printf("\n");

	//2
	int InputCardinal, OutputCardinal;
	char InputNumber[50]="";
	char changeNum[100]="";

	printf("입력 데이터 몇 진수 : ");
	scanf("%d", &InputCardinal);
	getchar();
	printf("값을 입력하시오 : ");
	scanf("%s", &InputNumber);
	getchar();
	printf("출력 데이터 몆 진수 : ");
	scanf("%d", &OutputCardinal);
	getchar();

	int k = 0;
	int InputNumberDec=0;
	while (k<strlen(InputNumber))
	{
		char rest = InputNumber[k];

		if (rest >= 48 && rest <= 57)
		{
			InputNumberDec+= (rest-48) *(int)pow(InputCardinal, strlen(InputNumber)-k-1);
		}

		else
		{
			InputNumberDec += (rest - 55) * (int)pow(InputCardinal, strlen(InputNumber) - k - 1);
		}

		k++;
	}


	int i = 0;
	while (1)
	{
		int rest;
		rest= InputNumberDec% OutputCardinal;

		if (rest >= 0 && rest <=9)
		{
			changeNum[i] = rest + 48;
			i++;
		}

		else
		{
			changeNum[i] = rest + 55;
			i++;
		}

		InputNumberDec /= OutputCardinal;
		if (InputNumberDec == 0) break;
	}
	
	for (int i = strlen(changeNum) - 1; i >= 0; i--)
	{
		printf("%c", changeNum[i]);
	}

	printf("\n");

	return 0;
}