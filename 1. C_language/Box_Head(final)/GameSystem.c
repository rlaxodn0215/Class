#include"GameSystem.h"

void GotoXY(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void StartScene()
{
	system("title Box Head"); //콘솔창 제목
	system("mode con cols=100 lines=25"); //콘솔 창 크기 가로 :100, 세로 : 25

	CONSOLE_CURSOR_INFO consoleCursorInfo;

	consoleCursorInfo.bVisible = 0; //콘솔 창에 커서 안보이게 하기
	consoleCursorInfo.dwSize = 1;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

	int n=0;
	while (n!=1)
	{
		system("cls");

		printf("\n");
		printf("                   ######           ####          #    #                        \n");
		printf("                   #     #         #    #          #  #                         \n");
		printf("                   ######          #    #           ##                          \n");
		printf("                   #     #         #    #          #  #                         \n");
		printf("                   ######           ####          #    #                        \n");
		printf("                                                                                \n");
		printf("           #     #        ######             #             #####                \n");
		printf("           #     #        #                 # #            #    #               \n");
		printf("           #######        ######           #####           #     #              \n");
		printf("           #     #        #               #     #          #    #               \n");
		printf("           #     #        ######         #       #         #####                \n\n");

		GotoXY(35,14);
		printf("1. Start");
		GotoXY(35, 16);
		printf("2. Rank");
		GotoXY(35, 18);
		printf("3. Exit");

		GotoXY(30, 20);
		printf("숫자를 눌러주세요 : ");
		scanf("%d", &n);
		getchar();
		switch (n)
		{
		case 1:
			system("cls");
			break;
		case 2:
		{
			system("cls");
			char name[25];
			int point;

			FILE* rank;
			rank = fopen("Rank.txt", "r");
			if (rank == EOF) return 1;

			GotoXY(28, 1);
			printf("등수\t    이름\t\t점수\n");

			for (int i = 0; i < 9; i++)
			{
				int res = fscanf(rank, "%s%d", name, &point);
				if (res == EOF) break;

				GotoXY(28, 3+2*i);
				printf("%d등\t\t%10s\t\t%4d\n",i+1, name, point);
			}

			int a=1;
			GotoXY(75, 22);
			printf("0. 메인 화면으로 : ");
			while (a)
			{
				scanf("%d", &a);
			}
			getchar();
			fclose(rank);
			
		}
			break;
		case 3:
			exit(1);
			break;
		default:
			break;
		}
	}

}

void DrawMap(char (*map)[60])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 60; j++)
		{
			if (map[i][j] == '1')
			{
				GotoXY(j, i);
				printf("#");
			}
		}
	}
	
}

void SpawnXY(int* posX, int* posY, char(*map)[60])
{
	int X;
	int Y;

	while (1)
	{
		X = rand() % 60;
		Y = rand() % 20;

		if (map[Y][X] == '0')
			break;
	}

	*posX = X;
	*posY = Y;
}

void SpawnAmmo(char(*map)[60])
{
	int x, y;
	SpawnXY(&x, &y, map);
	map[y][x] = 'A';
	GotoXY(x, y);
	printf("A");
}

void GameResult(Player* player, int victory)
{
	if (victory == 0)
	{
		GotoXY(61, 1);
		printf("HP : %3d", 0);
		GotoXY(70, 11);
		printf("G A M E  O V E R");
	}

	else if(victory==1)
	{
		GotoXY(70, 11);
		printf("Y O U  W I N ! !");
	}

	// 플레이어 이름 입력
	GotoXY(61, 14);
	printf("이름을 입력하세요 : ");
	fgets(player->name, sizeof(player->name), stdin);

	FILE *rank;

	rank = fopen("Rank.txt", "r");
	if (rank == NULL) return 1;

	typedef struct
	{
		char name[25];
		int points;
		struct Rank *nextRank;

	}Rank;

	Rank R[10]={"",0,NULL};

	//최근 데이터는 0번째에 저장
	strcpy(R[0].name, player->name);
	R[0].name[strlen(R[0].name) - 1] = '\0';
	R[0].points = player->points;
	R[0].nextRank = &R[1];

	for(int i=1;i<10;i++) //11등까지 저장
	{
		char str[25] = { 0, };
		int point;

		int res = fscanf(rank, "%s%d", str, &point);
		if (res == EOF) break;

		strcpy(R[i].name, str);
		R[i].points = point;
		R[i].nextRank = &R[i+1];
		if (&R[i + 1] == NULL) break;
	}

	fclose(rank);


	//내림차순 정렬

	for (int i = 0; i < 9; i++)
	{
		for (int j = i+1; j < 10; j++)
		{
			if (R[i].points < R[j].points)
			{
				char temp[25];
				strcpy(temp, R[i].name);
				int tempNum = R[i].points;

				strcpy(R[i].name, R[j].name);
				R[i].points = R[j].points;

				strcpy(R[j].name, temp);
				R[j].points = tempNum;
			}
		}
	}

	//Rank.txt에 저장 (10위까지만)
	rank = fopen("Rank.txt", "w");
	if(rank==NULL) return 1;

	for (int i = 0; i < 9; i++)
	{
		if (!(strcmp(R[i].name, ""))) break;
		fprintf(rank, "%s\t\t%d\n", R[i].name, R[i].points);
	}

	fclose(rank);

}