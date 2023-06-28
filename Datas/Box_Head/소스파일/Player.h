#pragma once
#include"Weapon.h"

typedef struct 
{
	char name[25];
	int Hp;
	int posX;
	int posY;
	int points;
	struct Weapon *weapon;
}Player;

void PlayerBeacon(int posX, int posY, char(*map)[60]);
void ShowHP(int posX, int posY, Player* player);
void ShowAmmo(int posX, int posY, Weapon* weapon);
void Score(int posX, int posY, Player* player);
void PlayerMove(Player* player,Weapon *weapon, char(*map)[60], int* HpTimer);
void PlayerAttack(Player* player, Weapon* weapon, char(*map)[60]);

