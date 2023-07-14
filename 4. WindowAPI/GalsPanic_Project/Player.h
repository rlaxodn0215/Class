#pragma once
#include "framework.h"
#include<vector>

using namespace std;

class Player
{
private:
	POINT curPos; //플레이어 이동시 업데이트
	POINT beforePos; // 방향이 틀면 값이 현제 위치 값으로 바뀜
	bool up, down, left, right; //플레이어 이동 방향
	int life;

public:
	POINT GetCurPos()const { return curPos; }
	void SetCurPos(POINT p) { curPos = p; }
	POINT GetBeforePos()const { return beforePos; }
	void SetBeforePos(POINT p) { beforePos = p; }
	int GetLife()const { return life; }
	void SetLife(int L) { life = L; }
	int GetWay()const;
	void SetWay(int w);

	Player();
	virtual ~Player();
	void PlayerPosUpdate();
	void PlayerCharactorUpdate(HDC hdc);
};

