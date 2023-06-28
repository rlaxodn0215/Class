#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>

//void swap_ptr(char** ppa, char** ppb);
//void MaxAndMin(int* arr, int **maxPtr, int **minPtr, int length);
//void func(int(*fp)(int, int));
//int sum(int a, int b);
//int mul(int a, int b);
//int Max(int a, int b);

//void swap(void** a, void** b);

int main()
{
	/*
	Q1. 야구게임
		세개의 숫자를 입력 받아서 다음과 같이 숫자가 있지만
		그 위치가 틀렸을 때는 "ball"를 출력하고, 
		숫자의 위치가 맞으면 "strike"를 출력한다
		숫자와 위치가 전부 틀리면 "out"을 출력하는 프로그램을 작성하라
		무엇이 볼이고 스트라이크인지 출력하지 않는다.
		세계의 숫자와 위치가 다 맞으면 "homerun"으로 표시하고 게임을 끝낸다.
	*/

	//int Ball=0, Strike=0, Out=0;
	//int InputNums[3];
	//int AnswerNums[3];
	//int sameNum = 1;

	//printf("야구게임\t\n");

	//srand(time(NULL));

	//while (1)
	//{
	//	for (int i = 0; i < 3; i++)
	//	{
	//		AnswerNums[i] = rand() % 9 + 1;
	//	}
	//
	//	if ((AnswerNums[0] != AnswerNums[1]) && (AnswerNums[1] != AnswerNums[2]) && (AnswerNums[0] != AnswerNums[2]))
	//	{
	//		break;
	//	}

	//}

	////printf("정답 : %d %d %d \n", AnswerNums[0], AnswerNums[1], AnswerNums[2]);

	//while (Strike !=3)
	//{
	//	Ball = 0; Strike = 0; Out = 0;

	//	while (sameNum)
	//	{
	//		printf("3개의 숫자를 입력하세요 (1 ~ 9) : ");
	//		scanf("%d%d%d", &InputNums[0], &InputNums[1], &InputNums[2]);

	//		if ((InputNums[0] != InputNums[1]) && (InputNums[1] != InputNums[2]) && (InputNums[0] != InputNums[2]))
	//		{
	//			sameNum = 0;
	//		}

	//		else
	//		{
	//			printf("같은 수를 입력하였습니다. 다시 입력하세요 \n");
	//		}
	//	}

	//	sameNum = 1;

	//	for (int i = 0; i < 3; i++)
	//	{
	//		if (InputNums[i] == AnswerNums[i])
	//		{
	//			Strike++;
	//		}

	//		else if (InputNums[i]== AnswerNums[(i+1)%3]) // 1 - 2, 2 - 0, 0 - 1
	//		{
	//			Ball++;
	//		}

	//		else if (InputNums[i] == AnswerNums[(i + 2) % 3]) 
	//		{
	//			Ball++;
	//		}

	//		else
	//		{
	//			Out++;
	//		}
	//	}

	//	printf("Strike : %d, Ball : %d, Out : %d 입니다.\n", Strike, Ball, Out);

	//}

	//printf("\n HomeRun~!!");

	//int a = 10;
	//int* pi;
	//int** ppi;
	//pi = &a;
	//ppi = &pi;

	//printf("-----------------------------------------------------\n");
	//printf("변수	변숫값		&연산	*연산	**연산\n");
	//printf("-----------------------------------------------------\n");
	//printf("	a%10d%10u\n", a, &a);
	//printf(" pi%10u%10u%10d\n", pi, &pi, *pi);
	//printf("ppi % 10u % 10u % 10u % 10u", ppi, &ppi, *ppi, **ppi);

	/*char* pa = "success";
	char* pb = "failure";

	printf("pa->%s, pb->%s\n", pa, pb);
	swap_ptr(&pa, &pb);
	printf("pa->%s, pb->%s\n", pa, pb);*/

	/*
		Q2. 다음과 같이 두개의 int형 포인터 변수와 길이가 5인 int 형 배열을
		선언한다.

		int* maxPtr;
		init* minPtr;
		int arr[5]
		
		MasAndMin이란 함수를 정의하고 이를 호출하여 
		위 배열과 두 포인터를 변수로 전달한다. 리턴값은 없다.
		이 함수의 호출이 완료되면, 포인터 변수 maxPtr에는 가장 큰 값이, 
		minPtr에는 가장 작은 배열 요소의 주소값이 저장되어야 한다
		결과> 
			arr 주소값과, 최대, 최소의 주소값
			maxPtr, minPtr이 가진 주소에 저장된 값을 출력하여라
		*/

	/*int* maxPtr;
	int* minPtr;
	int arr[100];
	int num;

	printf("일력할 정수의 개수 (100개 이하) :");
	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{
		printf("정수 입력 : ");
		scanf("%d", &arr[i]);
	}

	MaxAndMin(arr, &maxPtr, &minPtr,num);

	printf("arr의 주소값 : %u \n", arr);
	printf("maxPtr : %u,  minPtr : %u\n", maxPtr, minPtr);
	printf("최대, 최소의 값 : %u, %u \n", *maxPtr, *minPtr);*/

	/*int sel;
	printf("01 두 정수의 합\n");
	printf("02 두 정수의 곱\n");
	printf("03 두 정수 중에서 큰 값 계산\n");
	printf("원하는 연산을 선택하세요 : ");
	scanf("%d", &sel);

	switch (sel)
	{
	case 1: func(sum); break;
	case 2: func(mul); break;
	case 3: func(Max); break;
	}*/
	/*int age_1, age_2;
	float height_1, height_2;

	int *age1=&age_1, *age2=&age_2;
	float *height1=&height_1, *height2=&height_2;

	printf("첫 번째 사람의 나이와 키 입력 : ");
	scanf("%d%lf", age1, height1);
	printf("두 번째 사람의 나이와 키 입력 : ");
	scanf("%d%lf", age2, height2);

	swap((int*)age1, (int*)age2);
	swap((float*)height1, (float*)height2);

	printf("첫 번째 사람의 나이와 키 : %d, %.1lf\n",age_1,height_1);
	printf("두 번째 사람의 나이와 키 : %d, %.1lf\n",age_2,height_2);*/
		
	
	//int* pi = (int*)malloc(sizeof(int));

	/*int* pi;
	int i, sum = 0;

	pi = (int*)malloc(5 * sizeof(int));
	if (pi == NULL)
	{
		printf("메모리가 부족합니다.");
		exit(1);
	}

	printf("다섯 병의 나이를 입력하세요 : ");
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &pi[i]);
		sum += pi[i];
	}

	printf("다섯 명의 평균 나이 : %.1lf\n", (sum / 5.0));
	free(pi);*/

	/*
	Q4. 사용자 부터 문자열을 입력 받아서 단어를 역으로 출력하는 프로그램을 작성하라
		(Quit가 입력될 때까지 반복)

		입력 > I am happy
		출력 > happy am I

		(메모리 할당, 내용 복사 연습)
	*/
	
	char* sentence = (char*)malloc(sizeof(char)*100);

	if (sentence == NULL)
	{
		printf("메모리가 부족합니다\n");
		exit(1);
	}

	while (1)
	{
		printf("입력 => ");
		gets(sentence);

		if (!strcmp(sentence, "Quit")) break;

		for (int i = strlen(sentence) - 1; i >= 0; i--)
		{
			
		}

		
	}

	free(sentence);

	return 0;
}

//void swap(void** a, void** b)
//{
//	void* temp = *a;
//	*a = *b;
//	*b = temp;
//
//}

//void func(int (*fp)(int, int))
//{
//	int a, b;
//	int res;
//
//	printf("두 정수의 값을 입력하세요 : ");
//	scanf("%d%d", &a, &b);
//	res = fp(a, b);
//	printf("결과값은 : %d\n", res);
//}
//
//int sum(int a, int b) 
//{
//	return (a + b);
//}
//
//int mul(int a, int b)
//{
//	return (a * b);
//}
//
//int Max(int a, int b)
//{
//	if (a > b) 
//		return a;
//	else 
//		return b;
//}


//void MaxAndMin(int* arr, int **maxPtr, int **minPtr, int length)
//{
//	int* maxNum=&arr[0];
//	int* minNum=&arr[0];
//
//	//최댓값
//	for (int i = 1; i < length; i++)
//	{
//		maxNum = (*maxNum > arr[i]) ? maxNum : &arr[i];
//	}
//
//	//최솟값
//	for (int i = 1; i < length; i++)
//	{
//		minNum = (*minNum < arr[i]) ? minNum : &arr[i];
//	}
//
//	*maxPtr = maxNum;
//	*minPtr = minNum;
//
//
//}

//void swap_ptr(char** ppa, char** ppb)
//{
//	char* pt;
//	pt = *ppa;
//	*ppa = *ppb;
//	*ppb = pt;
//}
