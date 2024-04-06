#include"Zombie.h"

void ZombieBeacon(int posX, int posY, char(*map)[60],Zombie *zombie)
{
	GotoXY(posX, posY);
	map[posY][posX] = 'Z';
	printf("Z");
}
void ZombieMove(Player *player, Zombie *zombie,int zombieNum, char(*map)[60])
{
	//좀비가 체력이 있을때
	if (zombie[zombieNum].Hp>0)
	{		
		int existPlayer = 0;

		//시야에서 플레이어 확인
		for (int i = (zombie[zombieNum].posY - zombie->sight); i < (zombie[zombieNum].posY + zombie->sight); i++)
		{
			for (int j = (zombie[zombieNum].posX - zombie->sight*2); j < (zombie[zombieNum].posX + zombie->sight*2); j++)
			{
				if (map[i][j] == 'P')
				{
					existPlayer = 1;
				}
			}
		}

		//시야에 있으면
		if (existPlayer==1)
		{
		//플레이어 추격 및 공격
		//플레이어 공격 -> 거리 1 주변에 플레이어가 있으면 
			if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] == 'P' || map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX + 1] == 'P' ||
				map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] == 'P' || map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX - 1] == 'P' ||
				map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] == 'P' || map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX - 1] == 'P' ||
				map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] == 'P' || map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX + 1] == 'P')
			{
				ZombieAttack(player, zombie, zombieNum);
			}

			if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
				&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // 오른쪽에 벽이 없거나 플레이어가 없을때
			{
				if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 오른쪽에 있을때
				{

					//오른쪽 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // 아래쪽에 벽이 없거나 플레이어가 없을 때
					{

						if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 아래쪽에 있을때
						{
							//아래쪽 가는 로직 만들기
							//오른쪽 아래 대각선
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posY)++;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

						}
					}

					else if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // 위쪽에 벽이 없거나 플레이어가 없을때
					{

						if ((player->posY) - (zombie[zombieNum].posY) < 0) //플레이어가 위쪽에 있을때
						{
							//위로 가는 로직 만들기
							//오른쪽 위 대각선
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posY)--;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}

				}
			}

			else  //오른쪽에 벽이 있으면
			{
				if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // 아래쪽에 벽이 없거나 플레이어가 없을 때
				{

					if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 아래쪽에 있을때
					{
						//아래쪽 가는 로직 만들기
						//오른쪽 아래 대각선
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posY)++;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					}
				}

				else if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // 위쪽에 벽이 없거나 플레이어가 때
				{

					if ((player->posY) - (zombie[zombieNum].posY) < 0) //플레이어가 위쪽에 있을때
					{
						//위로 가는 로직 만들기
						//오른쪽 위 대각선
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posY)--;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}
			}



			if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1'
				&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // 왼쪽에 벽이 없거나 플레이어가 없을 때
			{

				if ((player->posX) - (zombie[zombieNum].posX) < 0) //왼쪽
				{
					//왼쪽으로 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // 아래쪽에 벽이 없거나 플레이어가 없을 때
					{

						if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 아래쪽에 있을때
						{
							//아래쪽 가는 로직 만들기
							//왼쪽 아래 대각선
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posY)++;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}

					else if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // 위쪽에 벽이 없거나 플레이어가 없을 때
					{

						if ((player->posY) - (zombie[zombieNum].posY) < 0) //플레이어가 위쪽에 있을때
						{
							//위로 가는 로직 만들기
							//왼쪽 위 대각선
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posY)--;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}


				}

			}

			else //왼쪽에 벽이 있으면
			{
				if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // 아래쪽에 벽이 없거나 플레이어가 없을 때
				{

					if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 아래쪽에 있을때
					{
						//아래쪽 가는 로직 만들기
						//왼쪽 아래 대각선
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posY)++;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}

				else if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // 위쪽에 벽이 없거나 플레이어가 없을 때
				{

					if ((player->posY) - (zombie[zombieNum].posY) < 0) //플레이어가 위쪽에 있을때
					{
						//위로 가는 로직 만들기
						//왼쪽 위 대각선
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posY)--;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}
			}


			if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1'
				&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // 위쪽에 벽이 없거나 플레이어가 없을 때
			{
				if ((player->posY) - (zombie[zombieNum].posY) < 0) //위쪽
				{
					//위로 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // 오른쪽에 벽이 없거나 플레이어가 없을 때
					{
						if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 오른쪽에 있을때
						{
							//오른쪽 가는 로직 만들기
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posX)++;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}

					else if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // 왼쪽에 벽이 없거나 플레이어가 없을 때
					{

						if ((player->posX) - (zombie[zombieNum].posX) < 0) //왼쪽
						{
							//왼쪽으로 가는 로직 만들기
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posX)--;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}
				}
			}

			else // 위쪽에 벽이 있으면
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // 오른쪽에 벽이 없거나 플레이어가 없을 때
				{
					if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 오른쪽에 있을때
					{
						//오른쪽 가는 로직 만들기
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posX)++;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}

				else if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // 왼쪽에 벽이 없거나 플레이어가 없을 때
				{

					if ((player->posX) - (zombie[zombieNum].posX) < 0) //왼쪽
					{
						//왼쪽으로 가는 로직 만들기
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posX)--;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}
			}

			if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
				&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // 아래쪽에 벽이 없거나 플레이어가 때
			{

				if ((player->posY) - (zombie[zombieNum].posY) > 0) //플레이어가 아래쪽에 있을때
				{
					//아래쪽 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // 오른쪽에 벽이 없거나 플레이어가 없을 때
					{
						if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 오른쪽에 있을때
						{
							//오른쪽 가는 로직 만들기
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posX)++;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}

					else if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // 왼쪽에 벽이 없거나 플레이어가 때
					{

						if ((player->posX) - (zombie[zombieNum].posX) < 0) //왼쪽
						{
							//왼쪽으로 가는 로직 만들기
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf(" ");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
							(zombie[zombieNum].posX)--;
							GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
							printf("Z");
							map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
						}
					}
				}
			}

			else // 아래쪽에 벽이 있으면
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // 오른쪽에 벽이 없거나 플레이어가 없을 때
				{
					if ((player->posX) - (zombie[zombieNum].posX) > 0) //플레이어가 오른쪽에 있을때
					{
						//오른쪽 가는 로직 만들기
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posX)++;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}

				else if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // 왼쪽에 벽이 없거나 플레이어가 없을 때
				{

					if ((player->posX) - (zombie[zombieNum].posX) < 0) //왼쪽
					{
						//왼쪽으로 가는 로직 만들기
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf(" ");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
						(zombie[zombieNum].posX)--;
						GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
						printf("Z");
						map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
					}
				}
			}
		}

		//시야에서 벗어나면
		else
		{
			//플레이어 추격하지 않기 => 랜덤 이동
			int randomNum = rand() % 4;

			switch (randomNum)
			{
			case 0:
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1') //오른쪽에 벽이 없을 때
				{
					//오른쪽 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
				}
			}
				break;
			case 1:
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1') //왼쪽에 벽이 없을 때
				{
					//왼쪽으로 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
				}
			}
				break;
			case 2:
			{
				if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1') //위쪽에 벽이 없을 때
				{
					//위로 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
				}
			}
				break;
			case 3:
			{
				if (map[zombie[zombieNum].posY+1][zombie[zombieNum].posX] != '1') //아래쪽에 벽이 없을 때
				{
					//아래쪽 가는 로직 만들기
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';
				}
			}
				break;
			}
			

		}
	}
}
void ZombieAttack(Player *player, Zombie *zombie, int zombieNum)
{
	player->Hp -= zombie[zombieNum].damage;
}
void ControlZombieHP(Player*player, Weapon* weapon, Zombie* zombie, int zombieNum, char(*map)[60]) //플레이어 총 맞는 것도 인식
{
	//총알이 1개 감소할 때 플레이어 사격 인식
	if(weapon->isShoot==1)
	{
		//사격 방향
		switch (weapon->way)
		{
		case 12:
		{
			int closed = 0;

			for (int i = 0; i < zombieNum; i++)
			{
				if ((zombie[i].posX == player->posX) && ((player->posY) - zombie[i].posY <= weapon->range))
				{
					closed = ((player->posY) - zombie[closed].posY < (player->posY) - zombie[i].posY) ? closed : i;
				}
			}

			if ((zombie[closed].posX == player->posX) && ((player->posY) - zombie[closed].posY <= weapon->range))
			{
				ZombieDamaged(player, weapon, zombie, closed, map);
			}
		}
			break;

		case 3:
		{
			int closed = 0;

			for (int i = 0; i < zombieNum; i++)
			{
				if ((zombie[i].posY == player->posY) && (zombie[i].posX - (player->posX) <= weapon->range * 2))
				{
					closed = (zombie[closed].posX - (player->posX) < zombie[i].posX - (player->posX)) ? closed : i;
				}
			}

			if ((zombie[closed].posY == player->posY) && (zombie[closed].posX - (player->posX) <= weapon->range * 2))
			{
				ZombieDamaged(player, weapon, zombie, closed, map);
			}

		}
			break;

		case 6:
		{
			int closed = 0;

			for (int i = 0; i < zombieNum; i++)
			{
				if ((zombie[i].posX == player->posX) && (zombie[i].posY - (player->posY) <= weapon->range))
				{
					closed = (zombie[closed].posY - (player->posY) < zombie[i].posY - (player->posY)) ? closed : i;
				}
			}

			if ((zombie[closed].posX == player->posX) && (zombie[closed].posY - (player->posY) <= weapon->range))
			{
				ZombieDamaged(player, weapon, zombie, closed, map);
			}
		}
			break;

		case 9:
		{

			int closed = 0;

			for (int i = 0; i < zombieNum; i++)
			{
				if ((zombie[i].posY == player->posY) && ((player->posX) - zombie[i].posX <= weapon->range * 2))
				{
					closed = ((player->posX) - zombie[closed].posX < (player->posX) - zombie[i].posX) ? closed : i;
				}
			}

			if ((zombie[closed].posY == player->posY) && ((player->posX) - zombie[closed].posX <= weapon->range * 2))
			{
				ZombieDamaged(player, weapon, zombie, closed, map);
			}
		}
			break;
		default:
			break;
		}

		weapon->isShoot = 0;

	}

}
void ZombieDamaged(Player* player,Weapon* weapon, Zombie* zombie, int zombieNum, char(*map)[60] )
{
	zombie[zombieNum].Hp -= weapon->damage;

	if (zombie[zombieNum].Hp <= 0)
	{
		ZombieDead(zombie,zombieNum,player,map);
	}
}
void ZombieDead(Zombie* zombie, int zombieNum, Player* player, char (*map)[60])
  {
	GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
	printf(" ");
	map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';

	//플레이어 포인트 획득
	if (zombie[zombieNum].zombieDead == 0)
	{
		player->points += zombie[zombieNum].points;
	}
	zombie[zombieNum].zombieDead = 1;

}
