#include"Weapon.h"

void WeaponName(int posX, int posY, Weapon* weapon)
{
	GotoXY(posX, posY);

	 printf("Weapon : %s", weapon->name); 
}