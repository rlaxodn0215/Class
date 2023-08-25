#include "Charactor.h"

Charactor::Charactor(Vector3 pos, int maxhp,int curhp, int moveSpeed,
	map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
{
	m_Position = pos;
	m_MaxHp = maxhp;
	m_CurHp = curhp;
	m_MoveSpeed = moveSpeed;
	m_Animations = anis;
	m_Sounds = sounds;
	m_CurAni = NULL;
}

void Charactor::Update(bool moveOK)
{
	if (moveOK)
		m_Position = m_Position + m_Velocity;
}

void Charactor::ShowCharactor(HDC hdc,int TimeDivRatio, int Timer, RECT winRect)
{
	if (m_StopMove)
	{
		if (!(Timer % TimeDivRatio) && m_CurAniFrameNum < m_CurAni->GetFrameTotalCount() - 1)
		{
			m_CurAniFrameNum++;

		}

		if (m_CurAniFrameNum < m_CurAni->GetFrameTotalCount())
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[m_CurAniFrameNum], m_CurAniFrameNum, 3.0f, 3.0f, m_isLookRight, winRect);

		if (m_CurAniFrameNum == m_CurAni->GetFrameTotalCount() - 1)
		{
			m_DelayTimer++;
			if (m_DelayTimer > TimeDivRatio * 9.5f)
			{
				m_StopMove = false;
				m_DelayTimer = 0;
				m_CurAniFrameNum = 0;
			}
		}
	}

	else
	{

		if (!(Timer % TimeDivRatio))
		{
			if (m_CurAniFrameNum < m_CurAni->GetFrameTotalCount() - 1) m_CurAniFrameNum++;
			else m_CurAniFrameNum = 0;
		}

		if (m_CurAniFrameNum < m_CurAni->GetFrameTotalCount())
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[m_CurAniFrameNum], m_CurAniFrameNum, 3.0f, 3.0f, m_isLookRight, winRect);
	}

}

void Ryno::Idle()
{
	if (m_Status != IDLE)
	{
		m_Status = IDLE;
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_idle"];
		m_CurAniSpeed = 2;
		//m_CurAniFrameNum = 0;
		if(m_CurSound !=NULL)
			m_CurSound->ResetAudio();

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

		RECT collderPos = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z-80,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z +80 };
		m_BodyColliders.SetArea(collderPos);
		m_BodyColliders.SetPosZ(m_Position.m_Z);

	}

	m_AttackColliders.SetArea({-1,-1,-1,-1});

}

void Ryno::Move()
{
	if (m_Status !=MOVE)
	{
		m_Status = MOVE;
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_walk"];
		m_CurAniSpeed = 2;
		//m_CurAniFrameNum = 0;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

	}
}

void Ryno::Run()
{
	if (m_Status !=RUN)
	{
		m_Status = RUN;
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_run"];
		m_CurAniSpeed = 2;
		//m_CurAniFrameNum = 0;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}
	}

}
void Ryno::Jump(bool & keydown, bool jumping)
{

	if (m_Status != JUMP)
	{
		m_Status = JUMP;
		m_CurAni = m_Animations["Ryno_jump"];
		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
	}

	if (jumping && m_Position.m_Y >= m_Position.m_Z)
	{
		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z;
		keydown = false;
		m_Jumping = false;
	}

	if (!jumping && keydown)
	{
		m_Velocity.m_Y = -30; //점프 속도
		m_Jumping = true;
	}

	RECT collderPos = { Charactor::m_Position.m_X-10 , Charactor::m_Position.m_Y - 80,
	Charactor::m_Position.m_X + 40, Charactor::m_Position.m_Y + 80 };
	m_BodyColliders.SetArea(collderPos);
	m_BodyColliders.SetPosZ(m_Position.m_Z);

	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[i] });
	}

}

void Ryno::Damaged(HDC hdc, RECT winRect)
{
	if (m_Status != DAMAGED)
	{
		m_Status = DAMAGED;
		int n = rand() % 2;
		if (n) m_CurAni = m_Animations["Ryno_damaged"];
		else m_CurAni = m_Animations["Ryno_damaged1"];
		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
		m_StopMove = true;
		m_CurSound = m_Sounds["Ryno_hit"];
		m_Velocity = { 0 ,0,0 };

		RECT collderPos = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z - 80,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z + 80 };
		m_BodyColliders.SetArea(collderPos);
		m_BodyColliders.SetPosZ(m_Position.m_Z);
	}

	m_CurSound->PlayAudio();

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Ryno::Dead()
{
	if (m_Status != DEAD)
	{
		m_Status = DEAD;
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_dead"];
		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
		m_DeadTimer = 0;
		m_CurSound = m_Sounds["Ryno_dead"];

		for (int t = 0; t < 4; t++)
		{
			for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
			{
				m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
					m_Position.m_Z - m_CurAni->GetHeights()[i] + 20});
				m_CurAniShowOffset.push_back({ 0,0 });
			}
		}
		m_BodyColliders.SetArea({0,0,0,0});
	}

	
}

void Ryno::Attack(bool isright)
{

	if (m_Status != ATTACK)
	{
		m_Status = ATTACK;
		m_CurAni = m_Animations["Ryno_attack"];
		m_CurAniSpeed = 2;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 1;
		m_AttackTimer = 0;
		m_CurSound = m_Sounds["Ryno_attack"];
	}

	m_CurSound->PlayAudio();

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}


	if (isright)
	{
		RECT collderPos = { Charactor::m_Position.m_X + 30, Charactor::m_Position.m_Z - 100,
		Charactor::m_Position.m_X + 180, Charactor::m_Position.m_Z + 80 };
		m_AttackColliders.SetArea(collderPos);
		m_AttackColliders.SetPosZ(m_Position.m_Z);
	}

	else
	{
		RECT collderPos = { Charactor::m_Position.m_X - 70, Charactor::m_Position.m_Z - 100,
		Charactor::m_Position.m_X + 80 , Charactor::m_Position.m_Z + 90 };
		m_AttackColliders.SetArea(collderPos);
		m_AttackColliders.SetPosZ(m_Position.m_Z);
	}
	
}

void Ryno::HomeRun(HDC hdc, RECT winRect, bool& keydown)
{
	if (m_Status != HOME_RUN)
	{
		m_Status = HOME_RUN;
		m_CurAni = m_Animations["Ryno_homerun"];
		m_CurAniSpeed = 3;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 6;
		m_AttackTimer = 0;
		m_CurSound = m_Sounds["Ryno_homerun"];

		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z;
		keydown = false;
		m_Jumping = false;
	}

	m_Animations["Ryno_area_attack"]->AniPlay(hdc, { m_Position.m_X -150, m_Position.m_Y-80 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);

	m_Velocity.m_Y = 0;
	m_CurSound->PlayAudio();
		
	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	RECT collderPos = { Charactor::m_Position.m_X - 200, Charactor::m_Position.m_Z - 100,
		Charactor::m_Position.m_X + 230, Charactor::m_Position.m_Z + 80 };
	m_AttackColliders.SetArea(collderPos);
	m_AttackColliders.SetPosZ(m_Position.m_Z);

	RECT collderPos1 = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z - 80,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z + 80 };
	m_BodyColliders.SetArea(collderPos1);
	

}

void Ryno::Dynamite(HDC hdc,int timer, RECT winRect, bool & playerDynamite)
{
	RECT collderPos = { 0,0,0,0 };
	m_BodyColliders.SetArea(collderPos);

	if (m_PlayingDynamite == 0) //flying
	{

		m_DynamiteTimer[2] = timer;
		if (m_DynamiteTimer[1] < m_DynamiteTimer[2])
		{
			m_DynamiteTimer[1] = m_DynamiteTimer[2];
			m_DynamiteTimer[0]++;
		}

		if (m_Status != DYNAMITE)
		{
			m_Status = DYNAMITE;
			m_CurAni = m_Animations["Ryno_fly"];
			m_CurAniSpeed = 2;
			m_CurAniFrameNum = 0;
			m_CurSound = m_Sounds["Ryno_dynamite"];
		}

		m_CurSound->PlayAudio();

		m_CurAniShowOffset.clear();

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[0] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[0] });

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[1] / 2 + 12), // 42
			m_Position.m_Y - m_CurAni->GetHeights()[1] -2}); //14

		m_Velocity.m_X = 0;
		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z - 300;

		if (m_isLookRight)
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 70, m_Position.m_Y + 40 }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
		}

		else
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 70, m_Position.m_Y + 45 }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
		}
		

		if (m_DynamiteTimer[0] > 20)
		{
			m_PlayingDynamite = 1;
			for (int i = 0; i < 3; i++)
				m_DynamiteTimer[i] = 0;
			m_CurSound->ResetAudio();
		}
	}

	else if (m_PlayingDynamite == 1) //shooting balls
	{


		m_AttackTiming = 3;
		m_Attack = 1;

		m_DynamiteTimer[2] = timer;
		if (m_DynamiteTimer[1] < m_DynamiteTimer[2])
		{
			m_DynamiteTimer[1] = m_DynamiteTimer[2];
			m_DynamiteTimer[0]++;
			if (m_AttackTimer > 3)
				m_AttackTimer = 0;
			m_CurSound = m_Sounds["Ryno_dynamite_shooting"];
		}

		m_CurSound->PlayAudio();

		if (m_isLookRight)
		{
			for (int i = 0; i < 8; i++)
			{
				m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 55 + 20*i,
					m_Position.m_Y+ 65 + 35*i }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
			}

			collderPos = { Charactor::m_Position.m_X + 150, Charactor::m_Position.m_Z,
							Charactor::m_Position.m_X + 350, Charactor::m_Position.m_Z + 100 };
			m_AttackColliders.SetArea(collderPos);
			m_AttackColliders.SetPosZ(m_Position.m_Z);
		}

		else
		{
			for (int i = 0; i < 8; i++)
			{
				m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55 - 20*i,
					m_Position.m_Y + 65 + 35*i}, 0, 2.0f, 2.0f, m_isLookRight, winRect);
			}

			collderPos = { Charactor::m_Position.m_X - 50, Charactor::m_Position.m_Z,
							Charactor::m_Position.m_X - 250, Charactor::m_Position.m_Z + 100 };
			m_AttackColliders.SetArea(collderPos);
			m_AttackColliders.SetPosZ(m_Position.m_Z);
		}

		if (m_DynamiteTimer[0] > 50)
		{
			m_PlayingDynamite = 3;
			for (int i = 0; i < 3; i++)
				m_DynamiteTimer[i] = 0;
			m_AttackTimer = 0;
			m_CurSound->ResetAudio();
		}
	}

	else if (m_PlayingDynamite == 3) //squish...
	{


		m_AttackTiming = 3;
		m_Attack = 50;

		m_DynamiteTimer[2] = timer;
		if (m_DynamiteTimer[1] < m_DynamiteTimer[2])
		{
			m_DynamiteTimer[1] = m_DynamiteTimer[2];
			m_DynamiteTimer[0]++;
			m_Velocity = { 0 ,0,0 };
		}


		if (m_CurAni != m_Animations["Ryno_dynamite"])
		{
			m_CurAniShowOffset.clear();

			m_CurAni = m_Animations["Ryno_dynamite"];
			m_CurAniFrameNum = 0;
			m_CurAniSpeed = 4;
			m_Velocity = { 0,0,0 };
			m_CurSound = m_Sounds["Ryno_dynamite2"];
		}

		m_CurSound->PlayAudio();

		if (m_isLookRight)
		{
			m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left+40, m_AttackColliders.GetArea().top - 40 });
			m_Position.m_X = m_AttackColliders.GetArea().left + 40;
			m_Position.m_Y = m_AttackColliders.GetArea().top;

			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55, m_Position.m_Y - 30 }, 0, 4.0f, 4.0f, m_isLookRight, winRect);
			m_Animations["Ryno_area_attack"]->AniPlay(hdc, { m_Position.m_X - 150, m_Position.m_Y - 80 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X, m_Position.m_Y - 380 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X + 30, m_Position.m_Y - 420 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X - 20, m_Position.m_Y - 420 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		}

		else
		{
			m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left-170, m_AttackColliders.GetArea().top - 40 });
			m_Position.m_X = m_AttackColliders.GetArea().left-170;
			m_Position.m_Y = m_AttackColliders.GetArea().top;

			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 55, m_Position.m_Y - 30 }, 0, 4.0f, 4.0f, m_isLookRight, winRect);
			m_Animations["Ryno_area_attack"]->AniPlay(hdc, { m_Position.m_X - 150, m_Position.m_Y - 80 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X, m_Position.m_Y - 380 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X + 30, m_Position.m_Y - 420 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
			m_Animations["Ryno_thunder"]->AniPlay(hdc, { m_Position.m_X - 20, m_Position.m_Y - 420 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		}

		m_Position.m_Z = m_Position.m_Y;

		if (m_DynamiteTimer[0] > 20)
		{
			m_PlayingDynamite = 0;
			for (int i = 0; i < 3; i++)
				m_DynamiteTimer[i] = 0;
			m_CurSound->ResetAudio();
			playerDynamite = false;
			SetTakeGravity(true);
		}
	}

}

void Player::ShowColliders(HDC hdc)
{
	Ryno* temp = (Ryno*)this;
	temp->GetBodyCollider().ShowCollider(hdc);
	temp->GetAttackCollider().ShowCollider(hdc);
}

void Baseball::Move()
{
	if (m_Status != MOVE)
	{
		m_CurAni = m_Animations["Baseball_readyforfight"];
		m_CurAniSpeed = 10;
		m_CurAniFrameNum = 0;
		m_Status = MOVE;
		if (m_CurSound != NULL)
			m_CurSound->ResetAudio();
	}

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 100 });
	}
	
	if(m_isLookRight)
		m_BodyCircleColliders.SetCenter({ m_Position.m_X + 30, m_Position.m_Z - 110 });
	else
		m_BodyCircleColliders.SetCenter({ m_Position.m_X + 60, m_Position.m_Z -110 });

	m_BodyCircleColliders.SetRadius(70);
	m_BodyCircleColliders.SetPosZ(m_Position.m_Z);
	m_AttackColliders.SetArea({ -2,-2,-2,-2 });
}

void Baseball::Damaged(HDC hdc, RECT winRect)
{
	if (m_Status != DAMAGED)
	{
		if (rand() % 4 == 0)
			m_CurAni = m_Animations["Baseball_hit_1"];
		else if (rand() % 4 == 1)
			m_CurAni = m_Animations["Baseball_hit_2"];
		else if (rand() % 4 == 2)
			m_CurAni = m_Animations["Baseball_hit_3"];
		else
			m_CurAni = m_Animations["Baseball_hit_4"];

		m_CurAniSpeed = 10;
		m_CurAniFrameNum = 0;
		m_CurSound = m_Sounds["Baseball_hit"];

		m_Status = DAMAGED;
	}

	m_CurSound->PlayAudio();

	if(m_isLookRight)
		m_Animations["Hit_Image"]->AniPlay(hdc, { m_Position.m_X - 30, m_Position.m_Y  - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);
	else
		m_Animations["Hit_Image"]->AniPlay(hdc, { m_Position.m_X + 60, m_Position.m_Y - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] -100});
	}
}

void Baseball::Dead()
{
	if (m_Status != DEAD)
	{
		m_CurAni = m_Animations["Baseball_dead"];
		m_CurAniSpeed = 2;
		m_CurAniFrameNum = 0;
		m_Status = DEAD;
		m_DeadTimer = 0;
		m_CurAniShowOffset.clear();
		m_CurSound = m_Sounds["Baseball_dead"];
		for (int t = 0; t < 4; t++)
		{
			for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
			{
				m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
					m_Position.m_Z - m_CurAni->GetHeights()[i] - 100 });
				m_CurAniShowOffset.push_back({ -1000,0 });
			}
		}
	}

	m_CurSound->PlayAudio();
}

void Baseball::Attack(HDC hdc, RECT winRect)
{
	if (m_Status != ATTACK)
	{
		if (rand() % 2)
			m_CurAni = m_Animations["Baseball_kick"];
		else
			m_CurAni = m_Animations["Baseball_punch"];

		m_CurAniSpeed = 5;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 8;
		m_AttackTimer = 0;
		m_Attack = 5;

		m_Status = ATTACK;
	}

	if(m_CurAniFrameNum==0)
		m_AttackTimer = 0;

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 130 });
	}

	RECT collderPos;

	if (m_isLookRight)
	{
		collderPos = { Charactor::m_Position.m_X - 110, Charactor::m_Position.m_Z - 230,
						Charactor::m_Position.m_X + 20 , Charactor::m_Position.m_Z - 50 };
	}

	else
	{
		collderPos = { Charactor::m_Position.m_X + 80, Charactor::m_Position.m_Z - 230,
						Charactor::m_Position.m_X + 200, Charactor::m_Position.m_Z - 50 };
	}

	m_AttackColliders.SetArea(collderPos);
	m_AttackColliders.SetPosZ(m_Position.m_Z);
}

void Baseball::MonsterAI(HDC hdc, RECT winRect, shared_ptr<Player> player, int z_offest)
{

	if (m_CurHp > 0)
	{
		//시선 처리
		if (m_Position.m_X - player->GetPos().m_X > 0)m_isLookRight = true;
		else m_isLookRight = false;

		if (m_Status == DAMAGED) //공격을 받으면 잠시 일시 정지
		{
			m_Velocity = { 0,0,0 };
			m_DamagedTime++;
			Damaged(hdc,winRect);
			if (m_DamagedTime >= 20)
			{
				m_Status = NOTHING;
				m_DamagedTime = 0;
			}
		}

		else
		{
			if (m_Position.m_Z - 120 < player->GetPos().m_Z - z_offest) //같은 z축을 만든다
			{
				m_Velocity.m_Y = m_MoveSpeed;
				m_Velocity.m_Z = m_MoveSpeed;
				Move();
			}

			else if (m_Position.m_Z - 120 > player->GetPos().m_Z + z_offest)
			{
				m_Velocity.m_Y = -m_MoveSpeed;
				m_Velocity.m_Z = -m_MoveSpeed;
				Move();
			}

			else //z 축이 동일 하면
			{
				m_Velocity.m_Y = 0;
				m_Velocity.m_Z = 0;

				if (m_Position.m_X - player->GetPos().m_X > 140) //공격 사정거리보다 크면
				{
					m_Velocity.m_X = -2 * m_MoveSpeed;
					Move();
				}

				else if (m_Position.m_X - player->GetPos().m_X < -140)
				{
					m_Velocity.m_X = 2 * m_MoveSpeed;
					Move();
				}

				else //사정거리 안에 있다
				{
					m_Velocity.m_X = 0;
					//공격!
					Attack(hdc, winRect);

				}

			}
		}
	}

	else
	{
		m_Velocity = { 0,0,0 };
		Dead();
		m_DeadTimer++;
		if (m_DeadTimer == m_CurAniShowOffset.size() - 1)
		{
			m_isAlive = false;
		}
	}

}

void Baseball::ShowColliders(HDC hdc)
{
	GetBodyCircleCollider().ShowCollider(hdc);
	GetAttackCollider().ShowCollider(hdc);
}

