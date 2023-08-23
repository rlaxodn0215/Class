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

	RECT GetPlayArea() { return m_PlayArea; }
	vector<RECT> GetLimitAreas(){ return m_LimitAreas; }
	list<shared_ptr<Monster>> GetStageMonsters() { return m_StageMonsters; }
	bool GetStageFinish() { return m_StageFinish; }

	void StageUpdate(HDC hdc, int Timer, RECT winRect, shared_ptr<Player> player, bool aniWait);
	//void RenderingCharactor();
};

