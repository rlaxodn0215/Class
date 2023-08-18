#include "Stage.h"

Stage::Stage(RECT& playArea, vector<RECT>& limitAreas, list<shared_ptr<Monster>>& stageMonsters)
{
	m_PlayArea = playArea;
	m_LimitAreas = limitAreas;
	m_StageMonsters = stageMonsters;
	m_StageFinish = false;
}

void Stage::StageUpdate(HDC hdc, int Timer, RECT winRect, shared_ptr<Player> player, bool aniWait)
{
	if (m_StageMonsters.empty()) m_StageFinish = true;


    for (auto iter = m_StageMonsters.begin(); iter != m_StageMonsters.end();iter++) // 플레이어 attack 콜라이더와 몬스터의 body Collider이 접촉 확인
    {
        CircleCollider temp = iter->get()->GetBodyCircleCollider();
        BoxCollider temp1 = player->GetBodyCollider();

        if (player->GetAttackCollider().OnTrigger(temp, 3)) //플레이어 공격이 몬스터에 들어갔다.
        {
            player->SetPoints(player->GetPoints()+ player->GetAttack());
            iter->get()->SetHP(iter->get()->GetHP() - player->GetAttack());
            //cout << "플레이어 공격이 몬스터에 들어갔다." << endl;
        }

        if (iter->get()->GetAttackCollider().OnTrigger(temp1, 3)) //몬스터의 공격이 플레이어에게 들어 갔다.
        {
            player->SetHP(player->GetHP() - iter->get()->GetAttack());
            //cout << "몬스터의 공격이 플레이어에게 들어 갔다." << endl;
        }
    }





    for (auto iter = m_StageMonsters.begin(); iter != m_StageMonsters.end();) //몬스터 및 플래이어 이동 처리
    {
        iter->get()->ShowCharactor(hdc, iter->get()->GetAniSpeed(), Timer, winRect);
        iter->get()->ShowColliders(hdc);

        TCHAR temp[20];
        _stprintf_s(temp, L"[%d, %d, %d]", iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, iter->get()->GetPos().m_Z);
        TextOut(hdc, iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, temp, _tcslen(temp));

        iter->get()->MonsterAI(player, 3);
        iter->get()->Update(true);

        if (iter->get()->GetAlive() == false) iter = m_StageMonsters.erase(iter);
        else ++iter;
    }

	player->ShowCharactor(hdc, player->GetAniSpeed(), Timer, winRect);
	player->ShowColliders(hdc);
	player->Update(true);
}

