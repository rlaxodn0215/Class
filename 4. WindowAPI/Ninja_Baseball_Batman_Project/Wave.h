#pragma once
#include "framework.h"
#include<list>
#include<queue>
#include"Charactor.h"
#include"DataManager.h"

class Wave //�÷��� ���������� ���� ��������(�÷��� ����, ���� ��, �� ��ġ ��)
{
private:
	RECT m_PlayArea; // �� ������������ �÷��� �ϴ� ����
	vector<RECT> m_LimitAreas; // ���� �� �� ���� ������
	list<shared_ptr<Monster>> m_LiveMonsters; // ����ִ� ���͵�
	queue<shared_ptr<Monster>> m_DeadMonsters; // ���� ���͵�
	bool m_StageFinish;

public:
	Wave() = default;
	Wave(RECT & playArea, vector<RECT> & limitAreas, queue<shared_ptr<Monster>> & DeadMonsters);
	~Wave() = default;

	RECT GetPlayArea() { return m_PlayArea; }
	vector<RECT> GetLimitAreas(){ return m_LimitAreas; }
	bool GetStageFinish() { return m_StageFinish; }

	void LoadStage(RECT winRect);
	void StageUpdate(HDC hdc, int Timer, RECT winRect, shared_ptr<Player> player, bool aniWait);
	void MonsterInstantiate(int timeInterval, int timer);
};

