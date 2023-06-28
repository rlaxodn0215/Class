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
	int TimePoint=0;
	int HpTimer = 0;
	int zombieMoveTimer = 0;
	int zombieSpawnTimer = 0;
	int AmmoTimer = 0;
	int zombieSpawnNum = 0;
	int victory = 0;

	SpawnXY(&playerPosX,&playerPosY,map_0);
	SpawnXY(&zombiePosX,&zombiePosY,map_0);

	Weapon weap = { "Pistol",1,5,35,9,0 };				
	Weapon* weapon = &weap;
	Player ply = {"player",100,playerPosX ,playerPosY,0,NULL};
	Player* player = &ply;
	player->weapon = weapon;

	Zombie zombie[50]; //좀비 최대 50마리 소환
	int zombieNums = 50;
	for (int i = 0; i < zombieNums; i++)
	{
		zombie[i].Hp = 4;
		zombie[i].damage = 5;
		zombie[i].points = 50;	
		zombie[i].sight = 6;	

		zombie[i].zombieDead = 0;
	}

	DrawMap(map_0);
	PlayerBeacon(playerPosX, playerPosY,map_0);

	while ((player->Hp)>0 && victory==0)
	{
		PlayerMove(player,player->weapon, map_0, &HpTimer);
		ControlZombieHP(player, weapon, zombie, zombieSpawnNum, map_0,&victory);


		//플레이어 정보 UI
		ShowHP(61, 1, player);
		ShowAmmo(61, 3, weapon);
		WeaponName(61, 5, player->weapon);
		Score(61, 7, player);

		if (zombieMoveTimer > 4000)
		{
			for (int i = 0; i < zombieSpawnNum; i++)
			{
				ZombieMove(player, zombie, i, map_0);
			}
			zombieMoveTimer = 0;
		}
		zombieMoveTimer++;

		if (TimePoint >20000)
		{
			player->points++;
			TimePoint = 0;
		}
		TimePoint++;

		if (AmmoTimer > 200000)
		{
			SpawnAmmo(map_0);
			AmmoTimer = 0;
		}
		AmmoTimer++;

		if (zombieSpawnTimer > 20000 && zombieSpawnNum< zombieNums)
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

	GameResult(player,victory);
	printf("\n\n\n\n\n\n");

	return 0;
}
