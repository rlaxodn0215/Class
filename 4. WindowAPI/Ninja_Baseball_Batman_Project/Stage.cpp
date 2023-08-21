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

        if (player->GetAttackCollider().OnTrigger(temp, 10)) //플레이어 공격
        {   
            player->SetAttackTimer(player->GetAttackTimer() + 1);
            //cout << player->GetAttackTimer() << endl;
            if (player->GetAttackTimer() == player->GetAttackTiming())
            {
                player->SetPoints(player->GetPoints() + player->GetAttack());
                iter->get()->SetHP(iter->get()->GetHP() - player->GetAttack());
                iter->get()->Damaged();
                //cout << "Player Attack" << endl;
            }
        }

        if (iter->get()->GetAttackCollider().OnTrigger(temp1, 500)) //몬스터 공격
        {
            iter->get()->SetAttackTimer(iter->get()->GetAttackTimer() + 1);
            if (iter->get()->GetAttackTimer() == iter->get()->GetAttackTiming())
            {
                player->SetHP(player->GetHP() - iter->get()->GetAttack());
                player->Damaged();
                cout << "Monster Attack" << endl;
            }
        }


        if (iter->get()->GetPos().m_Z <= 413) //이동 영역 (몬스터)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, 413, 413 });
        }

        else if (iter->get()->GetPos().m_Z >= winRect.bottom)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, winRect.bottom, winRect.bottom });
        }
    }

    for (auto iter = m_StageMonsters.begin(); iter != m_StageMonsters.end();) //몬스터 이동 처리
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

    if (player->GetPos().m_X < 25) //이동 영역 (플레이어)
    {
        player->SetPos({ 25,player->GetPos().m_Y, player->GetPos().m_Z });
    }

    else if (player->GetPos().m_X > winRect.right-110)
    {
        player->SetPos({ winRect.right-110,player->GetPos().m_Y, player->GetPos().m_Z });
    }

    if (player->GetPos().m_Z < 415 - 80)
    {
        player->SetPos({ player->GetPos().m_X, 415 - 80, 415 - 80 });
    }

    else if (player->GetPos().m_Z > winRect.bottom - 100)
    {
        player->SetPos({ player->GetPos().m_X, winRect.bottom - 100, winRect.bottom - 100});
    }

	player->ShowCharactor(hdc, player->GetAniSpeed(), Timer, winRect);
	player->ShowColliders(hdc);
	player->Update(true);
}

