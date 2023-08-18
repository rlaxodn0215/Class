#pragma once
#include "framework.h"
#include<list>
#include"Charactor.h"

class Stage //�÷��� ���������� ���� ��������(�÷��� ����, ���� ��, �� ��ġ ��)
{
private:
	RECT m_PlayArea; // �� ������������ �÷��� �ϴ� ����
	vector<RECT> m_LimitAreas; // ���� �� �� ���� ������
	list<shared_ptr<Monster>> m_StageMonsters; // ���������� �����ϴ� ���͵�
	bool m_StageFinish;

public:
	Stage() = default;
	Stage(RECT & playArea, vector<RECT> & limitAreas, list<shared_ptr<Monster>> & stageMonsters);
	~Stage() = default;

	void StageUpdate(RECT winRect, Player* player);
	void ShowStage(HDC hdc, int Timer, RECT winRect);
};

