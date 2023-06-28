#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include"Player.h"

void GotoXY(int x, int y);
void StartScene();
void DrawMap(char(*map)[60]);
void SpawnXY(int* posX, int*posY, char(*map)[60]);
void SpawnAmmo(char(*map)[60]);
void GameResult(Player* player, int victory);

