#include "Charactor.h"

Charactor::Charactor(Vector3 pos, int hp, int moveSpeed,
	map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
{
	m_Position = pos;
	m_Hp = hp;
	m_MoveSpeed = moveSpeed;
	m_Animations = anis;
	m_Sounds = sounds;
	m_CurAni = NULL;
	m_CurSound = NULL;
}

void Charactor::ShowCharactor(HDC hdc,int TimeDivRatio, int Timer, bool & aniWait)
{

	static int totalFrame = 0;
	static int curFrame = 0;
	totalFrame = m_CurAni->GetFrameTotalCount();

	if (aniWait)
	{
		static int tempTimer = 0;

		if (!(Timer % TimeDivRatio) && curFrame < totalFrame - 1)
		{
			curFrame++;
		}

		if (curFrame < totalFrame)
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[curFrame], curFrame, 3.0f);

		if (curFrame == totalFrame - 1)
		{
			tempTimer++;
			if (tempTimer> TimeDivRatio * 2.5f)
			{
				aniWait = false;
				tempTimer = 0;
			}
		}
	}

	else
	{
		if (!(Timer % TimeDivRatio))
		{
			if (curFrame < totalFrame - 1) curFrame++;
			else curFrame = 0;
		}

		if (curFrame < totalFrame)
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[curFrame], curFrame, 3.0f);
	}
	

	

}

BOOL Ryno::Born()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_born"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i]/2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Idle()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_idle"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	RECT collderPos = {Charactor::m_Position.m_X, Charactor::m_Position.m_Y, 
		Charactor::m_Position.m_X + 20, Charactor::m_Position.m_Y + 20};
	m_BodyColliders.SetArea(collderPos);
	return 0;
}

BOOL Ryno::Move()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_walk"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Run()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_run"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Jump(bool & keydown)
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_jump"];
	m_CurAniSpeed = 4;

	if(!keydown)
		m_Velocity.m_Y = -100;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[i] });
	}

	if (m_Velocity.m_Y == 100) keydown = false;

	return 0;
}

BOOL Ryno::Damaged()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	int n = rand() % 2;
	if(n) m_CurAni = m_Animations["Ryno_damaged"];
	else m_CurAni = m_Animations["Ryno_damaged1"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Dead()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_dead"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
	return 0;
}

BOOL Ryno::NormalAttack()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_attack"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
	return 0;
}

BOOL Ryno::JumpAttack()
{
	return 0;
}


BOOL Ryno::SlidingAttack()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_slide"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::HomeRun()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_homerun"];
	m_CurAniSpeed = 10;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Catch()
{
	return 0;
}

BOOL Ryno::CatchAttack()
{
	return 0;
}

BOOL Ryno::CatchThrow()
{
	return 0;
}

BOOL Ryno::LayDownAttack()
{
	return 0;
}

BOOL Ryno::SpecialCatchAttack()
{
	return 0;
}

BOOL Ryno::CatchDynamite()
{
	return 0;
}



void Monster::MoveUpdate()
{
}

void Baseball::Idle()
{
}

void Baseball::Damaged()
{
}

void Baseball::Dead()
{
}

void Baseball::NormalAttack()
{
}


