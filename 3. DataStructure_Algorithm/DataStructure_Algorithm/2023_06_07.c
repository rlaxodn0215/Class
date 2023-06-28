#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"IntStack.h"

void main()
{
	IntStack s;

	if (Initialize(&s, 4) == -1)
	{
		puts("���� ������ �����߽��ϴ�,");
		return 1;
	}

	while (1)
	{
		int menu, x;
		printf("���� ������ ��: %d / %d\n", Size(&s), Capacity(&s));
		printf("(1)Ǫ��, (2)��, (3)��ũ, (4)���, (5)��� �����, (6)�˻�, (0)���� : ");
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
			printf("������: ");
			scanf("%d", &x);

			if (Push(&s, x)==-1)
			{
				printf("�����͸� �� �̻� ������� �� �����ϴ�.\n");
			}

		}
			break;
		case 2:
		{
			if (Pop(&s, &x) == -1)
			{
				printf("�̾Ƴ� �����Ͱ� �����ϴ�.\n");
			}

			else
			{
				printf("�̾Ƴ� �����ʹ� %d �Դϴ�.\n", x);
			}
		}
			break;
		case 3:
		{
			if (Peek(&s, &x) == -1)
			{
				printf("������ �� �� �����Ͱ� �����ϴ�.\n");
			}

			else
			{
				printf("������ �� �� �����ʹ� %d �Դϴ�.\n",x);
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
			printf("ã���� �ϴ� ��: ");
			scanf("%d", &x);
			int data=Search(&s, x);
			if (data == -1)
			{
				printf("�ش� �����ʹ� �����ϴ�\n");
			}

			else
			{
				printf("%d�� s[%d]�� �ֽ��ϴ�", x, data);
			}
		}
			break;
		default:
			printf("��ȣ�� �߸� �Է��Ͽ����ϴ�. �ٽ� �Է��� �ּ���\n");
			break;
		}

		printf("\n");
	}
}