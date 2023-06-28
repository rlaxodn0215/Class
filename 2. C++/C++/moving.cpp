#include"Move.h"
#include<iostream>

int main()
{
	Move mov(3.5, 6.7);
	mov.showmove();
	Move mov1(1.7, -5.6);
	mov1.showmove();
	Move mov2=mov.add(mov1);
	mov2.showmove();
	mov2.reset(1, 1);
	mov2.showmove();
	return 0;
}