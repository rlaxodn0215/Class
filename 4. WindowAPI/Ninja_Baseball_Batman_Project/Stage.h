#pragma once
#include "framework.h"
#include<list>
#include"Charactor.h"

class Stage //�÷��� ���������� ���� ��������(�÷��� ����, ���� ��, �� ��ġ ��)
{
private:
	RECT m_PlayArea; // �� ������������ �÷��� �ϴ� ����
	vector<RECT> m_LimitAreas; // ���� �� �� ���� ������
	list<Charactor> m_StageMonsters; // ���������� �����ϴ� ���͵�
	bool m_StageFinish;

public:
	Stage() = default;
	Stage(RECT & playArea, vector<RECT> & limitAreas, list<Charactor> & stageMonsters);
	~Stage() = default;

	void ShowMonsters(HDC hdc, int Timer, RECT winRect);
};

