#pragma once
#include "framework.h"
#include<list>
#include<queue>
#include"Charactor.h"
#include"DataManager.h"

class Wave //플레이 스테이지에 대한 정보저장(플레이 영역, 몬스터 수, 각 위치 등)
{
private:
	RECT m_PlayArea; // 한 스테이지에서 플레이 하는 영역
	vector<RECT> m_LimitAreas; // 접근 할 수 없는 영역들
	list<shared_ptr<Monster>> m_LiveMonsters; // 살아있는 몬스터들
	queue<shared_ptr<Monster>> m_DeadMonsters; // 죽은 몬스터들
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

