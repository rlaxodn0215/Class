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

void Charactor::Update()
{
	m_Position = m_Position + m_Velocity;
}

void Charactor::ShowCharactor(HDC hdc,int TimeDivRatio, int Timer, bool & aniWait, RECT winRect)
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
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[curFrame], curFrame, 3.0f, m_isLookRight, winRect);

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
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[curFrame], curFrame, 3.0f, m_isLookRight, winRect);
	}
	

	

}

BOOL Ryno::Born()
{
	cout << "Ryno_Born" << endl;

	if (!m_CurAniShowOffset.empty())
	{
		m_CurAniShowOffset.clear();

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}
	}

	m_CurAni = m_Animations["Ryno_born"];
	m_CurAniSpeed = 4;

	return 0;
}

BOOL Ryno::Idle()
{
	cout << "Ryno_Idle" << endl;

	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_idle"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	RECT collderPos = {Charactor::m_Position.m_X+25, Charactor::m_Position.m_Z, 
		Charactor::m_Position.m_X + 100, Charactor::m_Position.m_Z + 125};
	m_BodyColliders.SetArea(collderPos);

	m_AttackColliders.SetArea({0,0,0,0});

	return 0;
}

BOOL Ryno::Move()
{
	cout << "Ryno_Move" << endl;

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

BOOL Ryno::Jump(bool & keydown, bool & jumping)
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_jump"];
	m_CurAniSpeed = 4;

	if (jumping && m_Position.m_Y >= m_Position.m_Z)
	{
		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z;
		keydown = false;
		jumping = false;
	}

	if (!jumping && keydown)
	{
		m_Velocity.m_Y = -30;
		jumping = true;
	}

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[i] });
	}

	RECT collderPos = { Charactor::m_Position.m_X , Charactor::m_Position.m_Y,
		Charactor::m_Position.m_X + 80, Charactor::m_Position.m_Y + 100 };
	m_BodyColliders.SetArea(collderPos);

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

BOOL Ryno::NormalAttack(bool isright)
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Ryno_attack"];
	m_CurAniSpeed = 4;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}


	if (isright)
	{
		RECT collderPos = { Charactor::m_Position.m_X + 50, Charactor::m_Position.m_Y,
		Charactor::m_Position.m_X + 200, Charactor::m_Position.m_Y + 100 };
		m_AttackColliders.SetArea(collderPos);
	}

	else
	{
		RECT collderPos = { Charactor::m_Position.m_X - 40, Charactor::m_Position.m_Y,
		Charactor::m_Position.m_X + 90 , Charactor::m_Position.m_Y + 100 };
		m_AttackColliders.SetArea(collderPos);
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

	RECT collderPos = { Charactor::m_Position.m_X - 100, Charactor::m_Position.m_Z,
		Charactor::m_Position.m_X + 300, Charactor::m_Position.m_Z + 100 };
	m_AttackColliders.SetArea(collderPos);

	RECT collderPos1 = { Charactor::m_Position.m_X + 25, Charactor::m_Position.m_Z,
		Charactor::m_Position.m_X + 100, Charactor::m_Position.m_Z + 100 };
	m_BodyColliders.SetArea(collderPos1);

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

BOOL Ryno::Dynamite(HDC hdc,int timer, RECT winRect, bool & playerDynamite)
{
	RECT collderPos = { 0,0,0,0 };
	m_BodyColliders.SetArea(collderPos);

	if (m_PlayingDynamite == 0) //flying
	{
		static int time = 0;
		static int temp = 0;
		static int temp1 = 0;

		temp1 = timer;
		if (temp<temp1)
		{
			temp = temp1;
			time++;
		}

		if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_fly"];
		m_CurAniSpeed = 4;

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[0] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[0] });

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[1] / 2) - 44, // 42
			m_Position.m_Y - m_CurAni->GetHeights()[1] - 16 }); //14
		

		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z - 300;

		if (time > 50)
		{
			m_PlayingDynamite = 1;
			time = temp = temp1 = 0;
		}
	}

	else if (m_PlayingDynamite == 1) //shooting balls
	{
		static int time = 0;
		static int temp = 0;
		static int temp1 = 0;

		temp1 = timer;
		if (temp < temp1)
		{
			temp = temp1;
			time++;
		}

		if (m_isLookRight)
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55, m_Position.m_Y+30 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55+20, m_Position.m_Y+30+35 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 40,m_Position.m_Y + 30 + 70}, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 60,m_Position.m_Y + 30 + 105}, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 80,m_Position.m_Y + 30 + 140 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 100,m_Position.m_Y + 30 + 175 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 120, m_Position.m_Y + 30 +210}, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 140,m_Position.m_Y + 30 + 245 }, 0, 2.0f, m_isLookRight, winRect);

			collderPos = { Charactor::m_Position.m_X + 150, Charactor::m_Position.m_Z,
							Charactor::m_Position.m_X + 350, Charactor::m_Position.m_Z + 100 };
			m_AttackColliders.SetArea(collderPos);
		}

		else
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55, m_Position.m_Y + 30}, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 20, m_Position.m_Y + 30 + 35 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 40,m_Position.m_Y + 30 + 70 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 60,m_Position.m_Y + 30 + 105 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 80,m_Position.m_Y + 30 + 140 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 100,m_Position.m_Y + 30 + 175 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 120, m_Position.m_Y + 30 + 210 }, 0, 2.0f, m_isLookRight, winRect);
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 140,m_Position.m_Y + 30 + 245 }, 0, 2.0f, m_isLookRight, winRect);

			collderPos = { Charactor::m_Position.m_X - 50, Charactor::m_Position.m_Z,
							Charactor::m_Position.m_X - 250, Charactor::m_Position.m_Z + 100 };
			m_AttackColliders.SetArea(collderPos);
		}

		if (time > 100)
		{
			m_PlayingDynamite = 3;
			time = temp = temp1 = 0;
		}
	}

	else if (m_PlayingDynamite == 3) //squish...
	{

		static int time = 0;
		static int temp = 0;
		static int temp1 = 0;

		temp1 = timer;
		if (temp < temp1)
		{
			temp = temp1;
			time++;
		}

		if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_dynamite"];
		m_CurAniSpeed = 4;
		m_Velocity = { 0,0,0 };

		if (m_isLookRight)
		{
			m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left+40, m_AttackColliders.GetArea().top - 40 });
			m_Position.m_X = m_AttackColliders.GetArea().left + 40;
			m_Position.m_Y = m_AttackColliders.GetArea().top;
		}

		else
		{
			m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left-170, m_AttackColliders.GetArea().top - 40 });
			m_Position.m_X = m_AttackColliders.GetArea().left-170;
			m_Position.m_Y = m_AttackColliders.GetArea().top;
		}

		m_Position.m_Z = m_Position.m_Y;

		if (time > 50)
		{
			m_PlayingDynamite = 0;
			time = temp = temp1 = 0;
			playerDynamite = false;
			SetTakeGravity(true);
		}

	}

	return 0;
}

void Baseball::Idle()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	if(rand()%2)
		m_CurAni = m_Animations["Baseball_readyforfight"];
	else
		m_CurAni = m_Animations["Baseball_walk"];

	m_CurAniSpeed = 10;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	m_BodyColliders.SetCenter({ m_Position.m_X, m_Position.m_Z });
	m_BodyColliders.SetRadius(50);
	m_AttackColliders.SetArea({ 0,0,0,0 });
}

void Baseball::Damaged()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	if (rand() % 4 == 0)
		m_CurAni = m_Animations["Baseball_hit1"];
	else if(rand() % 4 == 1)
		m_CurAni = m_Animations["Baseball_hit2"];
	else if (rand() % 4 == 2)
		m_CurAni = m_Animations["Baseball_hit3"];
	else 
		m_CurAni = m_Animations["Baseball_hit4"];

	m_CurAniSpeed = 10;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Baseball::Dead()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	m_CurAni = m_Animations["Baseball_dead"];

	m_CurAniSpeed = 10;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Baseball::NormalAttack()
{
	if (!m_CurAniShowOffset.empty()) m_CurAniShowOffset.clear();

	if (rand() % 2)
		m_CurAni = m_Animations["Baseball_kick"];
	else
		m_CurAni = m_Animations["Baseball_punch"];

	m_CurAniSpeed = 10;

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Baseball::FollowPlayer()
{


}


