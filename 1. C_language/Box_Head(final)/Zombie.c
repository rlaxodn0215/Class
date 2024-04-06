#include"Zombie.h"

void ZombieBeacon(int posX, int posY, char(*map)[60],Zombie *zombie)
{
	GotoXY(posX, posY);
	map[posY][posX] = 'Z';
	printf("Z");
}
void ZombieMove(Player *player, Zombie *zombie,int zombieNum, char(*map)[60])
{
	//���� �� �׾�����
	if (zombie[zombieNum].zombieDead==0)
	{		
		int existPlayer = 0;

		//�þ߿��� �÷��̾� Ȯ��
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

		//�þ߿� ������
		if (existPlayer==1)
		{
		//�÷��̾� �߰� �� ����
		//�÷��̾� ���� -> �Ÿ� 1 �ֺ��� �÷��̾ ������ 
			if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] == 'P' || map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX + 1] == 'P' ||
				map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] == 'P' || map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX - 1] == 'P' ||
				map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] == 'P' || map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX - 1] == 'P' ||
				map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] == 'P' || map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX + 1] == 'P')
			{
				ZombieAttack(player, zombie, zombieNum);
			}

			if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
				&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // �����ʿ� ���� ���ų� �÷��̾ ������
			{
				if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �����ʿ� ������
				{

					//������ ���� ���� �����
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // �Ʒ��ʿ� ���� ���ų� �÷��̾ ���� ��
					{

						if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �Ʒ��ʿ� ������
						{
							//�Ʒ��� ���� ���� �����
							//������ �Ʒ� �밢��
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
						&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ������
					{

						if ((player->posY) - (zombie[zombieNum].posY) < 0) //�÷��̾ ���ʿ� ������
						{
							//���� ���� ���� �����
							//������ �� �밢��
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

			else  //�����ʿ� ���� ������
			{
				if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // �Ʒ��ʿ� ���� ���ų� �÷��̾ ���� ��
				{

					if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �Ʒ��ʿ� ������
					{
						//�Ʒ��� ���� ���� �����
						//������ �Ʒ� �밢��
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
					&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ��
				{

					if ((player->posY) - (zombie[zombieNum].posY) < 0) //�÷��̾ ���ʿ� ������
					{
						//���� ���� ���� �����
						//������ �� �밢��
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
				&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
			{

				if ((player->posX) - (zombie[zombieNum].posX) < 0) //����
				{
					//�������� ���� ���� �����
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posX)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
						&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // �Ʒ��ʿ� ���� ���ų� �÷��̾ ���� ��
					{

						if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �Ʒ��ʿ� ������
						{
							//�Ʒ��� ���� ���� �����
							//���� �Ʒ� �밢��
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
						&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
					{

						if ((player->posY) - (zombie[zombieNum].posY) < 0) //�÷��̾ ���ʿ� ������
						{
							//���� ���� ���� �����
							//���� �� �밢��
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

			else //���ʿ� ���� ������
			{
				if (map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != '1'
					&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // �Ʒ��ʿ� ���� ���ų� �÷��̾ ���� ��
				{

					if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �Ʒ��ʿ� ������
					{
						//�Ʒ��� ���� ���� �����
						//���� �Ʒ� �밢��
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
					&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
				{

					if ((player->posY) - (zombie[zombieNum].posY) < 0) //�÷��̾ ���ʿ� ������
					{
						//���� ���� ���� �����
						//���� �� �밢��
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
				&& map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
			{
				if ((player->posY) - (zombie[zombieNum].posY) < 0) //����
				{
					//���� ���� ���� �����
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)--;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // �����ʿ� ���� ���ų� �÷��̾ ���� ��
					{
						if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �����ʿ� ������
						{
							//������ ���� ���� �����
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
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
					{

						if ((player->posX) - (zombie[zombieNum].posX) < 0) //����
						{
							//�������� ���� ���� �����
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

			else // ���ʿ� ���� ������
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // �����ʿ� ���� ���ų� �÷��̾ ���� ��
				{
					if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �����ʿ� ������
					{
						//������ ���� ���� �����
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
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
				{

					if ((player->posX) - (zombie[zombieNum].posX) < 0) //����
					{
						//�������� ���� ���� �����
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
				&& map[zombie[zombieNum].posY + 1][zombie[zombieNum].posX] != 'P') // �Ʒ��ʿ� ���� ���ų� �÷��̾ ��
			{

				if ((player->posY) - (zombie[zombieNum].posY) > 0) //�÷��̾ �Ʒ��ʿ� ������
				{
					//�Ʒ��� ���� ���� �����
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf(" ");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = '0';
					(zombie[zombieNum].posY)++;
					GotoXY(zombie[zombieNum].posX, zombie[zombieNum].posY);
					printf("Z");
					map[zombie[zombieNum].posY][zombie[zombieNum].posX] = 'Z';

					if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // �����ʿ� ���� ���ų� �÷��̾ ���� ��
					{
						if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �����ʿ� ������
						{
							//������ ���� ���� �����
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
						&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ��
					{

						if ((player->posX) - (zombie[zombieNum].posX) < 0) //����
						{
							//�������� ���� ���� �����
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

			else // �Ʒ��ʿ� ���� ������
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1'
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != 'P') // �����ʿ� ���� ���ų� �÷��̾ ���� ��
				{
					if ((player->posX) - (zombie[zombieNum].posX) > 0) //�÷��̾ �����ʿ� ������
					{
						//������ ���� ���� �����
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
					&& map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != 'P') // ���ʿ� ���� ���ų� �÷��̾ ���� ��
				{

					if ((player->posX) - (zombie[zombieNum].posX) < 0) //����
					{
						//�������� ���� ���� �����
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

		//�þ߿��� �����
		else
		{
			//�÷��̾� �߰����� �ʱ� => ���� �̵�
			int randomNum = rand() % 4;

			switch (randomNum)
			{
			case 0:
			{
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX + 1] != '1') //�����ʿ� ���� ���� ��
				{
					//������ ���� ���� �����
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
				if (map[zombie[zombieNum].posY][zombie[zombieNum].posX - 1] != '1') //���ʿ� ���� ���� ��
				{
					//�������� ���� ���� �����
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
				if (map[zombie[zombieNum].posY - 1][zombie[zombieNum].posX] != '1') //���ʿ� ���� ���� ��
				{
					//���� ���� ���� �����
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
				if (map[zombie[zombieNum].posY+1][zombie[zombieNum].posX] != '1') //�Ʒ��ʿ� ���� ���� ��
				{
					//�Ʒ��� ���� ���� �����
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
void ControlZombieHP(Player*player, Weapon* weapon, Zombie* zombie, int zombieNum, char(*map)[60], int* victory) //�÷��̾� �� �´� �͵� �ν�
{

	//���� ���� ��� Ȯ��
	int count=0;
	for (int i = 0; i < 50; i++)
	{
		if (zombie[i].zombieDead == 0) break;
		count++;
	}
	if (count == 50) *victory = 1;


	//�Ѿ��� 1�� ������ �� �÷��̾� ��� �ν�
	if(weapon->isShoot==1)
	{
		//��� ����
 		switch (weapon->way)
		{
		case 12:
		{
			int closetNum=-1;

			for (int i = 0; i < zombieNum; i++)
			{
				if (zombie[i].zombieDead == 1) continue; //���� ����� ����� �ʷ� ����.

				if ((zombie[i].posX == player->posX) && ((player->posY) - zombie[i].posY <= weapon->range) && ((player->posY) - zombie[i].posY > 0))
				{
					//��Ÿ� �ȿ� �ִµ� 2������ ���� ���ο� �ִ� ��� -> ���ؼ� �÷��̾�� ���� ����� ���� ������
					if (closetNum == -1) closetNum = i;
					closetNum = (player->posY - zombie[closetNum].posY <= player->posY - zombie[i].posY) ? closetNum : i;
				}
			}

			if (closetNum != -1)
			ZombieDamaged(player, weapon, zombie, closetNum, map);

		}
			break;

		case 3:
		{
			int closetNum = -1;

			for (int i = 0; i < zombieNum; i++)
			{
				if (zombie[i].zombieDead == 1) continue;

				if ((zombie[i].posY == player->posY) && (zombie[i].posX - (player->posX) <= weapon->range * 2) && (zombie[i].posX - (player->posX) >0))
				{
					if (closetNum == -1) closetNum = i;
					closetNum = (zombie[closetNum].posX - (player->posX) <= zombie[i].posX - (player->posX)) ? closetNum : i;
				}
			}

			if (closetNum != -1)
			ZombieDamaged(player, weapon, zombie, closetNum, map);
			

		}
			break;

		case 6:
		{
			int closetNum = -1;

			for (int i = 0; i < zombieNum; i++)
			{
				if (zombie[i].zombieDead == 1) continue;

				if ((zombie[i].posX == player->posX) && (zombie[i].posY - (player->posY) <= weapon->range) && (zombie[i].posY - (player->posY) > 0))
				{
					if (closetNum == -1) closetNum = i;
					closetNum = (zombie[closetNum].posY - (player->posY) <= zombie[i].posY - (player->posY)) ? closetNum : i;
				}
			}

			if (closetNum != -1)
			ZombieDamaged(player, weapon, zombie, closetNum, map);
			
		}
			break;

		case 9:
		{

			int closetNum = -1;

			for (int i = 0; i < zombieNum; i++)
			{
				if (zombie[i].zombieDead == 1) continue;

				if ((zombie[i].posY == player->posY) && ((player->posX) - zombie[i].posX <= weapon->range * 2) && (player->posX) - zombie[i].posX > 0)
				{
					if (closetNum == -1) closetNum = i;
					closetNum = ((player->posX) - zombie[closetNum].posX <= (player->posX) - zombie[i].posX) ? closetNum : i;
				}
			}

			if (closetNum != -1)
				ZombieDamaged(player, weapon, zombie, closetNum, map);
		}
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

	//�÷��̾� ����Ʈ ȹ��
	if (zombie[zombieNum].zombieDead == 0)
	{
		player->points += zombie[zombieNum].points;
	}

	zombie[zombieNum].zombieDead = 1;

}
