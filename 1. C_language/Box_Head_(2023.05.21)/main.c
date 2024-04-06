#include"Map.h"
#include"GameSystem.h"
#include"Weapon.h"
#include"Player.h"
#include"Zombie.h"

int main()
{
	StartScene();

	srand(time(NULL));
	int playerPosX, playerPosY;
	int zombiePosX, zombiePosY;

	SpawnXY(&playerPosX,&playerPosY,map_0);
	SpawnXY(&zombiePosX,&zombiePosY,map_0);

	Weapon weap[2] = { {"Pistol",1,5,25,9,0},
					   {"Grenade",5,3,5,9,0}
					 };
	Weapon* weapon = &weap[0];
	Player ply = {"player",100,playerPosX ,playerPosY,0,NULL};
	Player* player = &ply;
	player->weapon = weapon;
	Zombie zombie[40]; //좀비 최대 40마리 소환, 죽으면 일정 시간이 지난 후 부활
	int zombieNums = 4;

	// 맵 UI
	DrawMap(map_0);

	int TimePoint=1;
	int HpTimer = 1;
	int zombieMoveTimer = 0;
	int zombieSpawnTimer = 0;
	int AmmoTimer = 1;

	int zombieSpawnNum = 0;
	
	for (int i = 0; i < zombieNums; i++)
	{
		zombie[i].Hp = 4;
		zombie[i].damage = 5;
		zombie[i].points = 50;	
		zombie[i].sight = 5;	

		zombie[i].zombieDead = 0;
	}

	PlayerBeacon(playerPosX, playerPosY,map_0);

	while ((player->Hp)>0)
	{
		PlayerMove(player,player->weapon, map_0, &HpTimer);

		//플레이어 정보 UI
		ShowHP(61, 1, player);
		ShowAmmo(61, 3, weapon);
		WeaponName(61, 5, player->weapon);
		Score(61, 7, player);

		ControlZombieHP(player, weapon, zombie, zombieSpawnNum, map_0);
		if (zombieMoveTimer > 4000)
		{
			for (int i = 0; i < zombieSpawnNum; i++)
			{
				ZombieMove(player, zombie, i, map_0);
			}
			zombieMoveTimer = 0;
		}
		zombieMoveTimer++;

		if (TimePoint %15000 == 0)
		{
			player->points++;
			TimePoint = 0;
		}
		TimePoint++;

		if (AmmoTimer % 180000 == 0)
		{
			SpawnAmmo(map_0);
		}
		AmmoTimer++;

		if (zombieSpawnTimer % 22000 == 0 && zombieSpawnNum< zombieNums)
		{
			SpawnXY(&zombiePosX, &zombiePosY, map_0);

			zombie[zombieSpawnNum].posX = zombiePosX;
			zombie[zombieSpawnNum].posY = zombiePosY;

			ZombieBeacon(zombiePosX, zombiePosY, map_0,zombie,zombieSpawnNum);
			zombieSpawnNum++;
			zombieSpawnTimer = 0;
		}
		zombieSpawnTimer++;

	}

	GotoXY(61, 1);
	printf("HP : %3d", 0);
	GameOver(player);
	printf("\n\n\n\n\n\n");

	return 0;
}
