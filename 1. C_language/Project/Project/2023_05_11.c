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
	Q1. �߱�����
		������ ���ڸ� �Է� �޾Ƽ� ������ ���� ���ڰ� ������
		�� ��ġ�� Ʋ���� ���� "ball"�� ����ϰ�, 
		������ ��ġ�� ������ "strike"�� ����Ѵ�
		���ڿ� ��ġ�� ���� Ʋ���� "out"�� ����ϴ� ���α׷��� �ۼ��϶�
		������ ���̰� ��Ʈ����ũ���� ������� �ʴ´�.
		������ ���ڿ� ��ġ�� �� ������ "homerun"���� ǥ���ϰ� ������ ������.
	*/

	//int Ball=0, Strike=0, Out=0;
	//int InputNums[3];
	//int AnswerNums[3];
	//int sameNum = 1;

	//printf("�߱�����\t\n");

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

	////printf("���� : %d %d %d \n", AnswerNums[0], AnswerNums[1], AnswerNums[2]);

	//while (Strike !=3)
	//{
	//	Ball = 0; Strike = 0; Out = 0;

	//	while (sameNum)
	//	{
	//		printf("3���� ���ڸ� �Է��ϼ��� (1 ~ 9) : ");
	//		scanf("%d%d%d", &InputNums[0], &InputNums[1], &InputNums[2]);

	//		if ((InputNums[0] != InputNums[1]) && (InputNums[1] != InputNums[2]) && (InputNums[0] != InputNums[2]))
	//		{
	//			sameNum = 0;
	//		}

	//		else
	//		{
	//			printf("���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ��� \n");
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

	//	printf("Strike : %d, Ball : %d, Out : %d �Դϴ�.\n", Strike, Ball, Out);

	//}

	//printf("\n HomeRun~!!");

	//int a = 10;
	//int* pi;
	//int** ppi;
	//pi = &a;
	//ppi = &pi;

	//printf("-----------------------------------------------------\n");
	//printf("����	������		&����	*����	**����\n");
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
		Q2. ������ ���� �ΰ��� int�� ������ ������ ���̰� 5�� int �� �迭��
		�����Ѵ�.

		int* maxPtr;
		init* minPtr;
		int arr[5]
		
		MasAndMin�̶� �Լ��� �����ϰ� �̸� ȣ���Ͽ� 
		�� �迭�� �� �����͸� ������ �����Ѵ�. ���ϰ��� ����.
		�� �Լ��� ȣ���� �Ϸ�Ǹ�, ������ ���� maxPtr���� ���� ū ����, 
		minPtr���� ���� ���� �迭 ����� �ּҰ��� ����Ǿ�� �Ѵ�
		���> 
			arr �ּҰ���, �ִ�, �ּ��� �ּҰ�
			maxPtr, minPtr�� ���� �ּҿ� ����� ���� ����Ͽ���
		*/

	/*int* maxPtr;
	int* minPtr;
	int arr[100];
	int num;

	printf("�Ϸ��� ������ ���� (100�� ����) :");
	scanf("%d", &num);

	for (int i = 0; i < num; i++)
	{
		printf("���� �Է� : ");
		scanf("%d", &arr[i]);
	}

	MaxAndMin(arr, &maxPtr, &minPtr,num);

	printf("arr�� �ּҰ� : %u \n", arr);
	printf("maxPtr : %u,  minPtr : %u\n", maxPtr, minPtr);
	printf("�ִ�, �ּ��� �� : %u, %u \n", *maxPtr, *minPtr);*/

	/*int sel;
	printf("01 �� ������ ��\n");
	printf("02 �� ������ ��\n");
	printf("03 �� ���� �߿��� ū �� ���\n");
	printf("���ϴ� ������ �����ϼ��� : ");
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

	printf("ù ��° ����� ���̿� Ű �Է� : ");
	scanf("%d%lf", age1, height1);
	printf("�� ��° ����� ���̿� Ű �Է� : ");
	scanf("%d%lf", age2, height2);

	swap((int*)age1, (int*)age2);
	swap((float*)height1, (float*)height2);

	printf("ù ��° ����� ���̿� Ű : %d, %.1lf\n",age_1,height_1);
	printf("�� ��° ����� ���̿� Ű : %d, %.1lf\n",age_2,height_2);*/
		
	
	//int* pi = (int*)malloc(sizeof(int));

	/*int* pi;
	int i, sum = 0;

	pi = (int*)malloc(5 * sizeof(int));
	if (pi == NULL)
	{
		printf("�޸𸮰� �����մϴ�.");
		exit(1);
	}

	printf("�ټ� ���� ���̸� �Է��ϼ��� : ");
	for (i = 0; i < 5; i++)
	{
		scanf("%d", &pi[i]);
		sum += pi[i];
	}

	printf("�ټ� ���� ��� ���� : %.1lf\n", (sum / 5.0));
	free(pi);*/

	/*
	Q4. ����� ���� ���ڿ��� �Է� �޾Ƽ� �ܾ ������ ����ϴ� ���α׷��� �ۼ��϶�
		(Quit�� �Էµ� ������ �ݺ�)

		�Է� > I am happy
		��� > happy am I

		(�޸� �Ҵ�, ���� ���� ����)
	*/
	
	char* sentence = (char*)malloc(sizeof(char)*100);

	if (sentence == NULL)
	{
		printf("�޸𸮰� �����մϴ�\n");
		exit(1);
	}

	while (1)
	{
		printf("�Է� => ");
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
//	printf("�� ������ ���� �Է��ϼ��� : ");
//	scanf("%d%d", &a, &b);
//	res = fp(a, b);
//	printf("������� : %d\n", res);
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
//	//�ִ�
//	for (int i = 1; i < length; i++)
//	{
//		maxNum = (*maxNum > arr[i]) ? maxNum : &arr[i];
//	}
//
//	//�ּڰ�
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
