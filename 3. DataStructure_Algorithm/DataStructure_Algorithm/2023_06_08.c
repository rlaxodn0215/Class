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
		printf("���� ������ ��: %d / %d\n", Que.num, Que.max);
		printf("(1)��ť, (2)��ť, (3)��ũ, (4)���, (5)�˻�, (6)��� �����, (0)���� : ");
		scanf("%d", &menu);

		if (menu == 0)
		{
			printf("\n���α׷��� �����մϴ�.\n");
			Terminate(&Que);
			break;
		}

		switch (menu)
		{
		case 1:
		{
			int n;
			printf("�Է��� ������: ");
			scanf("%d", &n);
			Enque(&Que, n);
		}
			break;
		case 2:
		{
			int n;
			Deque(&Que, &n);
			printf("���ŵ� �����ʹ� %d �Դϴ�.\n", n);
		}
			break;
		case 3:
		{
			int n;
			Peek(&Que, &n);
			if(Peek(&Que, &n)==0)
			printf("�� �� �����ʹ� %d �Դϴ�.\n", n);
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
			printf("�˻��� ������: ");
			scanf("%d", &n);

			int x=Search(&Que, n);
			if (x == -1)
			{
				printf("�ش� �����ʹ� �����ϴ�.\n");
			}

			else
			{
				printf("�ش� �����ʹ� Que[%d]�� �ֽ��ϴ�.\n",x);
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
			printf("��ȣ�� �߸� �Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ���\n");
		}
			break;
		}
	}
	return 0;
}