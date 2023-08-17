#include "Stage.h"

Stage::Stage(RECT& playArea, vector<RECT>& limitAreas, list<Charactor>& stageMonsters)
{
	m_PlayArea = playArea;
	m_LimitAreas = limitAreas;
	m_StageMonsters = stageMonsters;
	m_StageFinish = false;
}

void Stage::ShowMonsters(HDC hdc,  int Timer, RECT winRect)
{
	bool temp = false;

	for (auto iter : m_StageMonsters)
	{
		if (iter.GetAlive())
		{
			iter.ShowCharactor(hdc, iter.GetAniSpeed(), Timer, temp , winRect);
		}
	}
}
