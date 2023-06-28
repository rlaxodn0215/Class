#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"IntStack.h"

void main()
{
	IntStack s;

	if (Initialize(&s, 4) == -1)
	{
		puts("스택 생성에 실패했습니다,");
		return 1;
	}

	while (1)
	{
		int menu, x;
		printf("현재 데이터 수: %d / %d\n", Size(&s), Capacity(&s));
		printf("(1)푸시, (2)팝, (3)피크, (4)출력, (5)모두 지우기, (6)검색, (0)종료 : ");
		scanf("%d", &menu);

		if (menu == 0)
		{
			Terminate(&s);
			break;
		}

		switch (menu)
		{
		case 1:
		{
			printf("데이터: ");
			scanf("%d", &x);

			if (Push(&s, x)==-1)
			{
				printf("데이터를 더 이상 집어넣을 수 없습니다.\n");
			}

		}
			break;
		case 2:
		{
			if (Pop(&s, &x) == -1)
			{
				printf("뽑아낼 데이터가 없습니다.\n");
			}

			else
			{
				printf("뽑아낸 데이터는 %d 입니다.\n", x);
			}
		}
			break;
		case 3:
		{
			if (Peek(&s, &x) == -1)
			{
				printf("스택의 맨 위 데이터가 없습니다.\n");
			}

			else
			{
				printf("스택의 맨 위 데이터는 %d 입니다.\n",x);
			}
		}

			break;
		case 4:
		{
			Print(&s);
		}
			break;
		case 5:
		{
			Clear(&s);
		}
			break;
		case 6:
		{
			printf("찾고자 하는 값: ");
			scanf("%d", &x);
			int data=Search(&s, x);
			if (data == -1)
			{
				printf("해당 데이터는 없습니다\n");
			}

			else
			{
				printf("%d는 s[%d]에 있습니다", x, data);
			}
		}
			break;
		default:
			printf("번호를 잘못 입력하였습니다. 다시 입력해 주세요\n");
			break;
		}

		printf("\n");
	}
}