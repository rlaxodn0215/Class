#include "Stage.h"

Stage::Stage(RECT& playArea, vector<RECT>& limitAreas, queue<shared_ptr<Monster>>& DeadMonsters)
{
	m_PlayArea = playArea;
	m_LimitAreas = limitAreas;
	m_DeadMonsters = DeadMonsters;
	m_StageFinish = false;
}

void Stage::LoadStage(RECT winRect)
{

    RECT playArea = { 0,0,326,233 };
    vector<RECT> limitAreas;
    limitAreas.push_back({ 0,0,winRect.right,415 });

    queue<shared_ptr<Monster>> stageMonsters;
    
    map<string, shared_ptr<Animation>> temp;
    LoadAnimations(_T("AniData/Datas/PlayScene_Animations_Baseball.txt"), temp);

    map<string, shared_ptr<Sound>> temp1;
    temp1["Baseball_attack"] = Sounds["Baseball_attack"];
    temp1["Baseball_dead"] = Sounds["Baseball_dead"];
    temp1["Baseball_hit"] = Sounds["Baseball_hit"];

    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(1150, 700, 700), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(-150, 750, 750), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(1150, 750, 750), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(-150, 700, 700), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(1150, 700, 700), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(-150, 750, 750), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(1150, 750, 750), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(-150, 700, 700), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(1150, 700, 700), 50, 50, 1, temp, temp1, 100)));
    stageMonsters.push(shared_ptr<Baseball>(new Baseball(Vector3(-150, 750, 750), 50, 50, 1, temp, temp1, 100)));

    m_Stage = shared_ptr<Stage>(new Stage(playArea, limitAreas, stageMonsters));

}

void Stage::StageUpdate(HDC hdc, int Timer, RECT winRect, shared_ptr<Player> player, bool aniWait)
{
    MonsterInstantiate(200, Timer);

    for (auto iter = m_LiveMonsters.begin(); iter != m_LiveMonsters.end();iter++) // �÷��̾� attack �ݶ��̴��� ������ body Collider�� ���� Ȯ��
    {
        CircleCollider temp = iter->get()->GetBodyCircleCollider();
        BoxCollider temp1 = player->GetBodyCollider();

        if (player->GetAttackCollider().OnTrigger(temp, 10)) //�÷��̾� ����
        {   
            player->SetAttackTimer(player->GetAttackTimer() + 1);

            if (player->GetAttackTimer() == player->GetAttackTiming())
            {
                iter->get()->SetCurHP(iter->get()->GetCurHP() - player->GetAttack());

                iter->get()->Damaged(hdc,winRect);

            }
        }

        if (iter->get()->GetAttackCollider().OnTrigger(temp1, 500)) //���� ����
        {
            iter->get()->SetAttackTimer(iter->get()->GetAttackTimer() + 1);

            if (iter->get()->GetAttackTimer() == iter->get()->GetAttackTiming())
            {
                player->SetCurHP(player->GetCurHP() - iter->get()->GetAttack());

                if (player->GetAlive())
                {
                    player->Damaged(hdc,winRect);
                   
                }

                else
                {
                    m_StageFinish = true;
                }

            }
        }

        if (iter->get()->GetPos().m_Z <= 413) //�̵� ���� (����)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, 413, 413 });
        }

        else if (iter->get()->GetPos().m_Z >= winRect.bottom)
        {
            iter->get()->SetPos({ iter->get()->GetPos().m_X, winRect.bottom, winRect.bottom });
        }
    }

    for (auto iter = m_LiveMonsters.begin(); iter != m_LiveMonsters.end();) //���� �̵� ó��
    {
        iter->get()->ShowCharactor(hdc, iter->get()->GetAniSpeed(), Timer, winRect);
        iter->get()->ShowColliders(hdc);

        TCHAR temp[20];
        _stprintf_s(temp, L"[%d, %d, %d]", iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, iter->get()->GetPos().m_Z);
        TextOut(hdc, iter->get()->GetPos().m_X, iter->get()->GetPos().m_Y, temp, _tcslen(temp));

        iter->get()->MonsterAI(hdc, winRect, player, 3);
        iter->get()->Update(true);

        if (iter->get()->GetAlive() == false)
        {
            player->SetPoints(player->GetPoints() + iter->get()->GetDeadPoints());
            m_DeadMonsters.push(*iter);
            iter = m_LiveMonsters.erase(iter);
        }
        else ++iter;
    }

    if (player->GetPos().m_X < 25) //�̵� ���� (�÷��̾�)
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

void Stage::MonsterInstantiate(int timeInterval, int timer)
{
    if (!(timer % timeInterval) && !m_DeadMonsters.empty()) //�ð��� �� �ǰ�, ���� ���� ����Ʈ�� ������� �ʴٸ� 
    {
        m_DeadMonsters.front()->SetAlive(true);
        m_DeadMonsters.front()->SetCurHP(m_DeadMonsters.front()->GetMaxHP());
        m_LiveMonsters.push_back(m_DeadMonsters.front());
        m_DeadMonsters.pop();
    }
}

