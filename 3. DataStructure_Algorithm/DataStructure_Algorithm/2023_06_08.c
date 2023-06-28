#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<math.h>
#include<time.h>
#include"IntQueue.h"

int main()
{
	IntQueue Que;
	Initialize(&Que, 4);

	while (1)
	{
		int menu;
		printf("현재 데이터 수: %d / %d\n", Que.num, Que.max);
		printf("(1)인큐, (2)디큐, (3)피크, (4)출력, (5)검색, (6)모두 지우기, (0)종료 : ");
		scanf("%d", &menu);

		if (menu == 0)
		{
			printf("\n프로그램을 종료합니다.\n");
			Terminate(&Que);
			break;
		}

		switch (menu)
		{
		case 1:
		{
			int n;
			printf("입력할 데이터: ");
			scanf("%d", &n);
			Enque(&Que, n);
		}
			break;
		case 2:
		{
			int n;
			Deque(&Que, &n);
			printf("제거된 데이터는 %d 입니다.\n", n);
		}
			break;
		case 3:
		{
			int n;
			Peek(&Que, &n);
			if(Peek(&Que, &n)==0)
			printf("맨 앞 데이터는 %d 입니다.\n", n);
		}
			break;
		case 4:
		{
			Print(&Que);
		}
			break;
		case 5:
		{
			int n;
			printf("검색할 데이터: ");
			scanf("%d", &n);

			int x=Search(&Que, n);
			if (x == -1)
			{
				printf("해당 데이터는 없습니다.\n");
			}

			else
			{
				printf("해당 데이터는 Que[%d]에 있습니다.\n",x);
			}
		}
			break;
		case 6:
		{
			Clear(&Que);
		}
			break;
		default:
		{
			printf("번호를 잘못 입력하였습니다. 다시 입력해 주세요\n");
		}
			break;
		}
	}
	return 0;
}