#include "Stage.h"

Stage::Stage(RECT& playArea, vector<RECT>& limitAreas, list<shared_ptr<Monster>>& stageMonsters)
{
	m_PlayArea = playArea;
	m_LimitAreas = limitAreas;
	m_StageMonsters = stageMonsters;
	m_StageFinish = false;
}

void Stage::StageUpdate(HDC hdc, int Timer, RECT winRect, Player * player, bool aniWait)
{
	for (auto iter : m_StageMonsters)
	{
		if (iter->GetAlive())
		{
			iter->ShowCharactor(hdc, iter->GetAniSpeed(), Timer,  winRect);
			iter->ShowColliders(hdc);

			TCHAR temp[20];
			_stprintf_s(temp, L"[%d, %d, %d]", iter->GetPos().m_X, iter->GetPos().m_Y, iter->GetPos().m_Z);
			TextOut(hdc, iter->GetPos().m_X, iter->GetPos().m_Y, temp, _tcslen(temp));

			iter->MonsterAI(player,3);
			iter->Update(true);
		}
	}

	player->ShowCharactor(hdc, player->GetAniSpeed(), Timer, winRect);
	player->ShowColliders(hdc);
	player->Update(true);
}

