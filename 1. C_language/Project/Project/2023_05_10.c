#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>


int main()
{
	//int score[3][4];
	//int total;
	//double avg;
	//int i, j;

	//for (i = 0; i < 3; i++)
	//{
	//	printf("4과목의 점수 입력 : ");
	//	for (j = 0; j < 4; j++)
	//	{
	//		scanf("%d", &score[i][j]);
	//	}
	//}

	//for (i = 0; i < 3; i++)
	//{
	//	total = 0;
	//	for (j = 0; j < 4; j++)
	//	{
	//		total += score[i][j];
	//	}

	//	avg = total / 4.0;
	//	printf("총점 : %d, 평균 : %.2lf\n", total, avg);
	//}

	/*char animal[5][20];
	int i;
	int count;

	count = sizeof(animal) / sizeof(animal[0]);

	for (i = 0; i < count; i++)
	{
		scanf("%s", animal[i]);
	}

	for (i = 0; i < count; i++)
	{
		printf("%s  ", animal[i]);
	}*/

	/*int score[2][3][4] = {
		{{72, 80, 95, 60}, {68, 98,83, 90},{75,72,84,90}},
		{{66, 85, 90, 88}, {95, 92, 88, 95}, {43, 72, 56, 75}}
	};
	
	int i, j, k;

	for (i = 0; i < 2; i++)
	{
		printf("%d반 점수...\n", i + 1);
		for (int j = 0; j < 3; j++)
		{
			for (k = 0; k < 4; k++)
			{
				printf("%5d", score[i][j][k]);
			}

			printf("\n");
		}

		printf("\n");
	}*/

	/*
		Q1.	다음과 같은 A행렬을 B행렬과 같은 형태가 되도록 
		프로그램을 작성하라

		A행렬				B행렬

		1 2 3 4				5 1
		5 6 7 8				6 2
							7 3
							8 4
	*/


	/*int matrix[3][4] = { 0 };

	int row = sizeof(matrix) / sizeof(matrix[0]);
	int col = sizeof(matrix[0]) / sizeof(matrix[0][0]);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}

	printf("\n");

	for (int i = 0; i <col ; i++)
	{
		for (int j = row -1; j >= 0; j-- )
		{
			printf("%2d ", matrix[j][i]);
		}

		printf("\n");
	}*/


/*
	Q2. 배열에 숫자를 다음과 같은 방법으로 채워지도록 프로그램을 작성하라
	시계방향으로 M*M의 2차원 배열에 숫자가 채워지도록 한다.

	ex) M=3
	
	1 2 3
	8 9 4
	7 6 5

	Q3. p.413 도전 실전 예제


	Q4. 다음과 같이 배열에 숫자가 채워지도록 프로그램을 작성하라.(N X N의 경우로만 작성)

	ex> N = 3;
		1 2 6
		3 5 7
		4 8 9
	
*/

	int m = 3;	
	int arr[3][3] = { 0 };
	//printf("10이하의 자연수를 입력하세요 : ");
	//scanf("%d", &m);
	int row = 0;
	int col = 0;
	int count = 1;
	int way = 0;


	while (count < m * m)
	{
		//오른쪽으로 한 칸
		if (way == 0)
		{
			arr[row][col] = count;
			col++;
			count++;
			way++;
		}

		//왼쪽 아래 대각선

		if (way == 1)
		{
			while (row < m && row >= 0 && col < m && col >= 0)
			{
				arr[row][col] = count;
				count++;
				row++;
				col--;
			}
		}

		//아래로 한 칸
		if (way == 2)
		{
			col++;
			arr[row][col] = count;
			count++;
		}

		//오른쪽 위 대각선
		if (way == 3)
		{
			while (row < m && row>0 && col < m && col >= 0)
			{
				col++;
				row--;
				arr[row][col] = count;
				count++;
			}
		}

		row++;
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; i++)
		{
			printf("%3d", arr[i][j]);

		}
	}



	//int arr[5][6] = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20}};

	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 5; j++)
	//	{
	//		arr[i][5] += arr[i][j];
	//	}

	//	arr[4][5] += arr[i][5];
	//}


	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		arr[4][i] += arr[j][i];
	//	}

	//	arr[4][5] += arr[4][1];
	//}


	//for (int i = 0; i < 5; i++)
	//{
	//	for (int j = 0; j < 6; j++)
	//	{
	//		printf("%5d", arr[i][j]);
	//	}
	//	printf("\n");
	//}


	//int M = 3;
	//int Matrix[3][3] = {0};
	//int row = 0;
	//int col = 0;
	//int count = 1;

	//while (count <= M * M)
	//{
	//	
	//	while (Matrix[row][col] == 0 && col < M)
	//	{
	//		Matrix[row][col] = count;
	//		count++;
	//		col++;
	//	}

	//	row++;
	//	col--;

	//	while (Matrix[row][col] == 0 && row < M)
	//	{
	//		Matrix[row][col] = count;
	//		count++;
	//		row++;
	//	}

	//	row--;
	//	col--;

	//	while (Matrix[row][col] == 0 && row >= 0)
	//	{
	//		Matrix[row][col] = count;
	//		count++;
	//		col--;
	//	}

	//	row--;
	//	col++;

	//	while (Matrix[row][col] == 0 && col >= 0)
	//	{
	//		Matrix[row][col] = count;
	//		count++;
	//		row--;
	//	}

	//	row++;
	//	col++;

	//}

	//for (int i = 0; i < M; i++)
	//{
	//	for (int j = 0; j < M; j++)
	//	{
	//		printf("%3d ", Matrix[i][j]);
	//	}

	//	printf("\n");
	//}
	
	/*char* pary[5];
	int i;

	pary[0] = "dog";
	pary[1] = "elephant";
	pary[2] = "horse";
	pary[3] = "tiger";
	pary[4] = "lion";

	for (i = 0; i < 5; i++)
	{
		printf("%s\n", pary[i]);
	}*/

	/*int ary1[4] = { 1,2,3,4 };
	int ary2[4] = { 11, 12, 13, 14 };
	int ary3[4] = { 21, 22, 23, 24 };
	int* pary[3] = {ary1,ary2,ary3};
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
		{
			printf("%5d", pary[i][j]);
		}

		printf("\n");
	}

	printf("\n");

	printf("ary1 = %p\n",ary1);
	printf("ary2 = %p\n",ary2);
	printf("ary3 = %p\n",ary3);*/

	return 0;
}