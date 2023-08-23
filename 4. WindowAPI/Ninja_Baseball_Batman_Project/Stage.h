#pragma once
#include "framework.h"
#include<list>
#include"Charactor.h"

class Stage //플레이 스테이지에 대한 정보저장(플레이 영역, 몬스터 수, 각 위치 등)
{
private:
	RECT m_PlayArea; // 한 스테이지에서 플레이 하는 영역
	vector<RECT> m_LimitAreas; // 접근 할 수 없는 영역들
	list<shared_ptr<Monster>> m_StageMonsters; // 스테이지에 존재하는 몬스터들
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

