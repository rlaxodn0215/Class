#pragma once
#include "framework.h"
#include<list>
#include"Charactor.h"

class Stage //플레이 스테이지에 대한 정보저장(플레이 영역, 몬스터 수, 각 위치 등)
{
private:
	RECT m_PlayArea; // 한 스테이지에서 플레이 하는 영역
	vector<RECT> m_LimitAreas; // 접근 할 수 없는 영역들
	list<Charactor> m_StageMonsters; // 스테이지에 존재하는 몬스터들
	bool m_StageFinish;

public:
	Stage() = default;
	Stage(RECT & playArea, vector<RECT> & limitAreas, list<Charactor> & stageMonsters);
	~Stage() = default;

	void ShowMonsters(HDC hdc, int Timer, RECT winRect);
};

