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


    for (auto iter = m_StageMonsters.begin(); iter != m_StageMonsters.end();iter++) // �÷��̾� attack �ݶ��̴��� ������ body Collider�� ���� Ȯ��
    {
        CircleCollider temp = iter->get()->GetBodyCircleCollider();
        BoxCollider temp1 = player->GetBodyCollider();

        if (player->GetAttackCollider().OnTrigger(temp, 3)) //�÷��̾� ������ ���Ϳ� ����.
        {
            player->SetPoints(player->GetPoints()+ player->GetAttack());
            iter->get()->SetHP(iter->get()->GetHP() - player->GetAttack());
            //cout << "�÷��̾� ������ ���Ϳ� ����." << endl;
        }

        if (iter->get()->GetAttackCollider().OnTrigger(temp1, 3)) //������ ������ �÷��̾�� ��� ����.
        {
            player->SetHP(player->GetHP() - iter->get()->GetAttack());
            //cout << "������ ������ �÷��̾�� ��� ����." << endl;
        }
    }





    for (auto iter = m_StageMonsters.begin(); iter != m_StageMonsters.end();) //���� �� �÷��̾� �̵� ó��
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

