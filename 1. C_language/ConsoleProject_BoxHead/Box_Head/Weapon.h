#pragma once

typedef struct
{
	char name[20];
	int damage;
	int range;
	int ammo;
	int way; //사격 방향 :12시, 3시, 6시, 9시
	int isShoot;

}Weapon;

void WeaponName(int posX, int posY, Weapon* weapon);