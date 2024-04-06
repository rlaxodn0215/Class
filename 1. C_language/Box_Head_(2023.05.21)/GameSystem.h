#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include"Player.h"

//#define PLAYER_BORN_X (55) //플레이서 생성 X좌표 // 55
//#define PLAYER_BORN_Y (17) //플레이서 생성 Y좌표 // 15
//
//#define ZOMBIE_BORN_X (12) //좀비 생성 X좌표
//#define ZOMBIE_BORN_Y (7) //좀비 생성 Y좌표

void GotoXY(int x, int y);
void StartScene();
void DrawMap(char(*map)[60]);
void SpawnXY(int* posX, int*posY, char(*map)[60]);
void SpawnAmmo(char(*map)[60]);
void GameOver(Player* player);

