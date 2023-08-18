#include "Stage.h"

Stage::Stage(RECT& playArea, vector<RECT>& limitAreas, list<shared_ptr<Monster>>& stageMonsters)
{
	m_PlayArea = playArea;
	m_LimitAreas = limitAreas;
	m_StageMonsters = stageMonsters;
	m_StageFinish = false;
}

void Stage::StageUpdate(RECT winRect, Player * player)
{

	for (auto iter : m_StageMonsters)
	{
		if (iter->GetAlive())
		{
			iter->MonsterAI(player,3);
			iter->Update();
		}
	}
}

void Stage::ShowStage(HDC hdc, int Timer, RECT winRect)
{
	bool temp = false;

	for (auto iter : m_StageMonsters)
	{
		if (iter->GetAlive())
		{
			iter->ShowCharactor(hdc, iter->GetAniSpeed(), Timer, temp, winRect);
			iter->ShowColliders(hdc);

			TCHAR temp[20];
			_stprintf_s(temp, L"[%d, %d, %d]", iter->GetPos().m_X, iter->GetPos().m_Y, iter->GetPos().m_Z);
			TextOut(hdc, iter->GetPos().m_X, iter->GetPos().m_Y, temp, _tcslen(temp));
		}
	}
}
