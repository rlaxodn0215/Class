#pragma once

typedef struct
{
	char name[20];
	int damage;
	int range;
	int ammo;
	int way; //��� ���� :12��, 3��, 6��, 9��
	int isShoot;

}Weapon;

void WeaponName(int posX, int posY, Weapon* weapon);