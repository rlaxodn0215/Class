#pragma once
#include "Player.h"
#include"Weapon.h"

typedef struct
{
	int Hp;
	int posX;
	int posY;
	int damage;
	int points;
	int zombieDead;
	int sight;

}Zombie;

void ZombieBeacon(int posX,int posY, char(*map)[60], Zombie*zombie);
void ZombieMove(Player *player, Zombie* zombie, int zombieNum, char(*map)[60]);
void ZombieAttack(Player* player, Zombie* zombie, int zombieNum);
void ControlZombieHP(Player* player, Weapon* weapon, Zombie* zombie, int zombies, char(*map)[60], int* victory);
void ZombieDamaged(Player* player, Weapon* weapon, Zombie* zombie, int zombieNum, char(*map)[60]);
void ZombieDead(Zombie* zombie, int zombieNum, Player* player, char(*map)[60]);
