#pragma once
#include "framework.h"
#include<vector>

using namespace std;

class Player
{
private:
	POINT curPos; //�÷��̾� �̵��� ������Ʈ
	POINT beforePos; // ������ Ʋ�� ���� ���� ��ġ ������ �ٲ�
	bool up, down, left, right; //�÷��̾� �̵� ����
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

