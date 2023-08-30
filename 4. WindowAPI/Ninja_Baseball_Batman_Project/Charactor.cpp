#include "Charactor.h"

Charactor::Charactor(int ID, Vector3 pos, int maxhp,int curhp, int attack, int moveSpeed,
	map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
	: m_CharactorID(ID),
	m_Position(pos),
	m_MaxHp(maxhp),
	m_CurHp(curhp),
	m_Attack(attack),
	m_MoveSpeed(moveSpeed),
	m_Animations(anis),
	m_Sounds(sounds),
	m_CurAni(NULL)
{
}

void Charactor::Update(bool moveOK)
{
	if (moveOK)
		m_Position = m_Position + m_Velocity;
}

void Charactor::ShowCharactor(HDC hdc,int TimeDivRatio, int Timer, RECT winRect)
{
	if (!m_CurAni)
	{
		MessageBox(NULL, _T("m_CurAni -> NULL"), _T("에러"), MB_OK);
		return;
	}

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

			if (m_Status == DAMAGED)
			{
				if (m_isLookRight)
					m_Animations[HIT_IMAGE]->AniPlay(hdc, { m_Position.m_X - 20, m_Position.m_Z - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);
				else
					m_Animations[HIT_IMAGE]->AniPlay(hdc, { m_Position.m_X + 60, m_Position.m_Z - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);
			}

			if (m_DelayTimer > TimeDivRatio * 8.5f)
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

		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_IDLE];
		else
			m_CurAni = m_Animations[RYNO_IDLE_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Idle m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 2;

		m_Position = { m_Position.m_X, m_Position.m_Z, m_Position.m_Z };

		if(m_CurSound !=NULL)
			m_CurSound->ResetAudio();

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
		}

		RECT collderPos = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z-195,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z -35 };
		m_BodyColliders.SetArea(collderPos);
		m_BodyColliders.SetPosZ(m_Position.m_Z);

		m_AttackColliders.SetArea({ -1,-1,-1,-1 });

	}


}

void Ryno::Move()
{
	if (m_Status !=MOVE)
	{
		m_Status = MOVE;
		m_CurAniShowOffset.clear();

		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_WALK];
		else
			m_CurAni = m_Animations[RYNO_WALK_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Move m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
		}

	}
}

void Ryno::Run()
{
	if (m_Status !=RUN)
	{
		m_Status = RUN;
		m_CurAniShowOffset.clear();

		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_RUN];
		else
			m_CurAni = m_Animations[RYNO_RUN_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Run m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
		}
	}

}

void Ryno::Jump(bool & keydown, bool jumping)
{
	if (m_Status != JUMP)
	{
		m_Status = JUMP;
		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
	}

	if (m_isLookRight)
		m_CurAni = m_Animations[RYNO_JUMP];
	else
		m_CurAni = m_Animations[RYNO_JUMP_REV];

	if (!m_CurAni)
	{
		MessageBox(NULL, _T("Ryno Jump m_CurAni -> NULL"), _T("에러"), MB_OK);
		return;
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
		m_Velocity.m_Z = 0;
		m_Jumping = true;
	}

	RECT collderPos = { Charactor::m_Position.m_X-10 , Charactor::m_Position.m_Y - 195,
	Charactor::m_Position.m_X + 40, Charactor::m_Position.m_Y -35 };
	m_BodyColliders.SetArea(collderPos);
	m_BodyColliders.SetPosZ(m_Position.m_Z);

	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[i] - 115 });
	}

}

void Ryno::Damaged(HDC hdc, RECT winRect, bool& keydown)
{
	if (m_Status != DAMAGED)
	{
		m_Status = DAMAGED;
		int n = rand() % 2;

		if (m_isLookRight)
		{
			if (n) m_CurAni = m_Animations[RYNO_DAMAGED];
			else m_CurAni = m_Animations[RYNO_DAMAGED1];
		}

		else
		{
			if (n) 
				m_CurAni = m_Animations[RYNO_DAMAGED_REV];
			else
				m_CurAni = m_Animations[RYNO_DAMAGED1_REV];
		}

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Damaged m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
		m_StopMove = true;
		keydown = false;
		m_Jumping = false;
		m_CurSound = m_Sounds[RYNO_HIT_SOUND];

		if (!m_CurSound)
		{
			MessageBox(NULL, _T("m_CurSound -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurSound->ResetAudio();
		m_CurSound->PlayAudio();
		m_Velocity = { 0 ,0,0 };
		m_Position = { m_Position.m_X, m_Position.m_Z, m_Position.m_Z };
		
		m_BodyColliders.SetArea({-8, -8, -8, -8});
		m_BodyColliders.SetPosZ(m_Position.m_Z);
	}

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
	}
}

void Ryno::Dead()
{
	if (m_Status != DEAD)
	{
		m_Status = DEAD;
		m_CurAniShowOffset.clear();

		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_DEAD];
		else
			m_CurAni = m_Animations[RYNO_DEAD_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Dead m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 4;
		m_CurAniFrameNum = 0;
		m_DeadTimer = 0;
		m_CurSound = m_Sounds[RYNO_DEAD_SOUND];
		if (!m_CurSound)
		{
			MessageBox(NULL, _T("Ryno Dead m_CurSound -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurSound->PlayAudio();

		for (int t = 0; t < 4; t++)
		{
			for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
			{
				m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
					m_Position.m_Z - m_CurAni->GetHeights()[i] - 95});
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
		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_ATTACK];
		else
			m_CurAni = m_Animations[RYNO_ATTACK_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Attack m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 2;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 1;
		m_AttackTimer = 0;
		m_CurSound = m_Sounds[RYNO_ATTACK_SOUND];
		if (!m_CurSound)
		{
			MessageBox(NULL, _T("Ryno Attack m_CurSound -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurSound->ResetAudio();
	}

	m_CurSound->PlayAudio();

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
	}


	if (isright)
	{
		RECT collderPos = { Charactor::m_Position.m_X + 30, Charactor::m_Position.m_Z - 215,
		Charactor::m_Position.m_X + 180, Charactor::m_Position.m_Z - 35 };
		m_AttackColliders.SetArea(collderPos);
		m_AttackColliders.SetPosZ(m_Position.m_Z);
	}

	else
	{
		RECT collderPos = { Charactor::m_Position.m_X - 100, Charactor::m_Position.m_Z - 215,
		Charactor::m_Position.m_X + 80 , Charactor::m_Position.m_Z - 25 };
		m_AttackColliders.SetArea(collderPos);
		m_AttackColliders.SetPosZ(m_Position.m_Z);
	}
	
}

void Ryno::HomeRun(HDC hdc, RECT winRect, bool& keydown)
{
	if (m_Status != HOME_RUN)
	{
		m_Status = HOME_RUN;

		if(m_isLookRight)
			m_CurAni = m_Animations[RYNO_HOMERUN];
		else
			m_CurAni = m_Animations[RYNO_HOMERUN_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Homerun m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 3;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 6;
		m_AttackTimer = 0;
		m_CurSound->ResetAudio();
		m_CurSound = m_Sounds[RYNO_HOMERUN_SOUND];
		if (!m_CurSound)
		{
			MessageBox(NULL, _T("Ryno Homerun m_CurSound -> NULL"), _T("에러"), MB_OK);
			return;
		}
		m_CurSound->PlayAudio();
		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z;
		keydown = false;
		m_Jumping = false;
	}

	m_Animations[RYNO_AREA_ATTACK]->AniPlay(hdc, { m_Position.m_X -150, m_Position.m_Y-195 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);

	m_Velocity.m_Y = 0;
		
	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 115 });
	}

	RECT collderPos = { Charactor::m_Position.m_X - 180, Charactor::m_Position.m_Z-165,
		Charactor::m_Position.m_X + 230, Charactor::m_Position.m_Z - 35 };
	m_AttackColliders.SetArea(collderPos);
	m_AttackColliders.SetPosZ(m_Position.m_Z);

	RECT collderPos1 = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z - 135,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z - 35 };
	m_BodyColliders.SetArea(collderPos1);
	

}

void Ryno::Dynamite(HDC hdc,int timer, RECT winRect, bool & playerDynamite) // 깔끔하게 정리
{
	m_BodyColliders.SetArea({0,0,0,0});

	if (m_PlayingDynamite == 0) //flying
	{
		m_DynamiteTimer++;

		if (m_Status != DYNAMITE)
		{
			m_Status = DYNAMITE;
			m_CurAniSpeed = 2;
			m_CurAniFrameNum = 0;
			m_CurSound = m_Sounds[RYNO_DYNAMITE_SOUND];
			if (!m_CurSound)
			{
				MessageBox(NULL, _T("Ryno Dynamite0 m_CurSound -> NULL"), _T("에러"), MB_OK);
				return;
			}
			m_CurSound->PlayAudio();
		}

		if (m_isLookRight)
			m_CurAni = m_Animations[RYNO_FLY];
		else
			m_CurAni = m_Animations[RYNO_FLY_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Dynamite0m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniShowOffset.clear();

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[0] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[0] - 115 });

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[1] / 2 + 12), // 42
			m_Position.m_Y - m_CurAni->GetHeights()[1] -117}); //14

		m_Velocity.m_X = 0;
		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z - 300;

		if (m_isLookRight)
		{
			m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X + 70, m_Position.m_Y - 75 }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
		}

		else
		{
			m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X - 70, m_Position.m_Y - 75 }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
		}
		
		if (m_DynamiteTimer > 20)
		{
			m_PlayingDynamite = 1;
			m_DynamiteTimer = 0;
			m_CurSound->ResetAudio();
			m_CurSound = m_Sounds[RYNO_DYNAMITE_SHOOTING_SOUND];
			if (!m_CurSound)
			{
				MessageBox(NULL, _T("Ryno Dynamite1 m_CurSound -> NULL"), _T("에러"), MB_OK);
				return;
			}
			m_CurSound->PlayAudio();
		}
	}

	else if (m_PlayingDynamite == 1) //shooting balls
	{
		m_AttackTiming = 3;
		m_Attack = 1;

		m_DynamiteTimer++;

		if (m_AttackTimer > 3)
			m_AttackTimer = 0;

		if (m_isLookRight)
			m_CurAni = m_Animations[RYNO_FLY];
		else
			m_CurAni = m_Animations[RYNO_FLY_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Ryno Dynamite1 m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		if (m_isLookRight)
		{
			for (int i = 0; i < 8; i++)
			{
					m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X + 75 + 20*i,
						m_Position.m_Y - 50 + 35*i }, 0, 2.0f, 2.0f, m_isLookRight, winRect);
			}

			m_DynamiteCollderPos = { Charactor::m_Position.m_X + 150, Charactor::m_Position.m_Z - 115,
							Charactor::m_Position.m_X + 350, Charactor::m_Position.m_Z - 15 };
			m_AttackColliders.SetArea(m_DynamiteCollderPos);
		}

		else
		{
			for (int i = 0; i < 8; i++)
			{
					m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X - 55 - 20*i,
						m_Position.m_Y - 60 + 35*i}, 0, 2.0f, 2.0f, m_isLookRight, winRect);
			}

			m_DynamiteCollderPos = { Charactor::m_Position.m_X - 270, Charactor::m_Position.m_Z - 115,
							Charactor::m_Position.m_X - 70, Charactor::m_Position.m_Z - 15 };
			m_AttackColliders.SetArea(m_DynamiteCollderPos);
		}

		m_AttackColliders.SetPosZ(m_Position.m_Z);

		if (m_DynamiteTimer > 45)
		{
			m_PlayingDynamite = 3;
			m_DynamiteTimer = 0;
			m_AttackTimer = 0;
			m_CurSound->ResetAudio();
		}
	}

	else if (m_PlayingDynamite == 3) //squish...
	{
		m_AttackTiming = 1;
		m_Attack = 50;

		m_DynamiteTimer++;
		m_Velocity = { 0 ,0,0 };

		if (m_CurAni != m_Animations[RYNO_DYNAMITE]) // define으로 정리 한다
		{
			m_CurAniShowOffset.clear();

			if(m_isLookRight)
				m_CurAni = m_Animations[RYNO_DYNAMITE];
			else
				m_CurAni = m_Animations[RYNO_DYNAMITE_REV];

			if (!m_CurAni)
			{
				MessageBox(NULL, _T("Ryno Dynamite3 m_CurAni -> NULL"), _T("에러"), MB_OK);
				return;
			}

			m_CurAniFrameNum = 0;
			m_CurAniSpeed = 4;
			m_Velocity = { 0,0,0 };
			m_CurSound = m_Sounds[RYNO_DYNAMITE2_SOUND];
			if (!m_CurSound)
			{
				MessageBox(NULL, _T("Ryno Dynamite3 m_CurSound -> NULL"), _T("에러"), MB_OK);
				return;
			}

			SetStopMove(true);
		}

		m_CurSound->PlayAudio();

		m_Sounds[RYNO_DYNAMITE_CRUSH_SOUND]->PlayAudio();

		RynoDynamiteEffect(hdc, winRect, m_isLookRight);

		if (m_DynamiteTimer > 20)
		{
			m_Position.m_Y = m_Position.m_Z;
			m_PlayingDynamite = 0;
			m_DynamiteTimer = 0;
			m_AttackTimer = 0;
			m_CurSound->ResetAudio();
			m_Sounds[RYNO_DYNAMITE_CRUSH_SOUND]->ResetAudio();
			playerDynamite = false;
			SetTakeGravity(true);
			SetStopMove(false);
			m_DynamiteCollderPos = { 0,0,0,0 };
		}
	}

}

void Ryno::RynoDynamiteEffect(HDC hdc,RECT winRect, bool isRight)
{
	if (!(m_Animations[RYNO_THUNDER] && m_Animations[RYNO_DYNAMITE_BALL] && m_Animations[RYNO_AREA_ATTACK]))
	{
		MessageBox(NULL, _T("RynoDynamiteEffect Animation Load 에러"), _T("에러"), MB_OK);
		return;
	}

	if (m_isLookRight)
	{
		m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left + 40, m_AttackColliders.GetArea().top - 40 });
		m_Position.m_X = m_AttackColliders.GetArea().left + 170;
		m_Position.m_Y = m_AttackColliders.GetArea().top;

		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X - 35, m_Position.m_Y - 285 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X - 5, m_Position.m_Y - 325 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X - 55, m_Position.m_Y - 325 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X - 70, m_Position.m_Y - 50 }, 0, 4.0f, 4.0f, m_isLookRight, winRect);
		m_Animations[RYNO_AREA_ATTACK]->AniPlay(hdc, { m_Position.m_X - 170, m_Position.m_Y - 110 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);

		m_AttackColliders.SetArea({ m_DynamiteCollderPos.left - 80, m_DynamiteCollderPos.top, m_DynamiteCollderPos.right + 110, m_DynamiteCollderPos.bottom });
		m_AttackColliders.SetPosZ(m_Position.m_Z);
	}

	else
	{
		m_CurAniShowOffset.push_back({ m_AttackColliders.GetArea().left + 170, m_AttackColliders.GetArea().top - 40 });
		m_Position.m_X = m_AttackColliders.GetArea().left + 200;
		m_Position.m_Y = m_AttackColliders.GetArea().top;

		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X + 10, m_Position.m_Y - 285 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X + 20, m_Position.m_Y - 315 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_THUNDER]->AniPlay(hdc, { m_Position.m_X - 30, m_Position.m_Y - 315 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);
		m_Animations[RYNO_DYNAMITE_BALL]->AniPlay(hdc, { m_Position.m_X - 65, m_Position.m_Y - 40 }, 0, 4.0f, 4.0f, m_isLookRight, winRect);
		m_Animations[RYNO_AREA_ATTACK]->AniPlay(hdc, { m_Position.m_X - 140, m_Position.m_Y - 90 }, 0, 3.0f, 3.0f, m_isLookRight, winRect);

		m_AttackColliders.SetArea({ m_DynamiteCollderPos.left - 130,m_DynamiteCollderPos.top, m_DynamiteCollderPos.right + 70, m_DynamiteCollderPos.bottom });
		m_AttackColliders.SetPosZ(m_Position.m_Z);
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
		m_CurAniSpeed = 10;
		m_CurAniFrameNum = 0;
		m_Status = MOVE;
		if (m_CurSound != NULL)
			m_CurSound->ResetAudio();
	}

	if (m_isLookRight)
		m_CurAni = m_Animations[BASEBALL_READYFORFIGHT];
	else
		m_CurAni = m_Animations[BASEBALL_READYFORFIGHT_REV];

	if (!m_CurAni)
	{
		MessageBox(NULL, _T("Baseball Move m_CurAni -> NULL"), _T("에러"), MB_OK);
		return;
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
		if (m_isLookRight)
		{
			if (rand() % 4 == 0)
				m_CurAni = m_Animations[BASEBALL_HIT_1];
			else if (rand() % 4 == 1)
				m_CurAni = m_Animations[BASEBALL_HIT_2];
			else if (rand() % 4 == 2)
				m_CurAni = m_Animations[BASEBALL_HIT_3];
			else
				m_CurAni = m_Animations[BASEBALL_HIT_4];
		}

		else
		{
			if (rand() % 4 == 0)
				m_CurAni = m_Animations[BASEBALL_HIT_1_REV];
			else if (rand() % 4 == 1)
				m_CurAni = m_Animations[BASEBALL_HIT_2_REV];
			else if (rand() % 4 == 2)
				m_CurAni = m_Animations[BASEBALL_HIT_3_REV];
			else
				m_CurAni = m_Animations[BASEBALL_HIT_4_REV];
		}

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Baseball Damaged m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 10;
		m_CurAniFrameNum = 0;

		if(m_CurHp<=0 && m_CurSound != m_Sounds[BASEBALL_DEAD_SOUND])
			m_CurSound = m_Sounds[BASEBALL_DEAD_SOUND];
		else
			m_CurSound = m_Sounds[BASEBALL_HIT_SOUND];

		m_CurSound->ResetAudio();
		m_CurSound->PlayAudio();
		m_Status = DAMAGED;
		m_CurAniShowOffset.clear();

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] - 100 });
		}
	}


	if (m_isLookRight)
		m_Animations[HIT_IMAGE]->AniPlay(hdc, { m_Position.m_X - 30, m_Position.m_Y - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);
	else
		m_Animations[HIT_IMAGE]->AniPlay(hdc, { m_Position.m_X + 60, m_Position.m_Y - 140 }, 0, 1.0f, 1.0f, m_isLookRight, winRect);
	
}

void Baseball::Dead()
{
	if (m_Status != DEAD)
	{
		if(m_isLookRight)
			m_CurAni = m_Animations[BASEBALL_DEAD];
		else
			m_CurAni = m_Animations[BASEBALL_DEAD_REV];

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Baseball Dead m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

		m_CurAniSpeed = 2;
		m_CurAniFrameNum = 0;
		m_Status = DEAD;
		m_DeadTimer = 0;
		m_CurAniShowOffset.clear();

		if(m_CurSound != NULL)
			m_CurSound->ResetAudio();
		m_CurSound = m_Sounds[BASEBALL_DEAD_SOUND];

		m_CurSound->ResetAudio();
		m_CurSound->PlayAudio();
		for (int t = 0; t < 4; t++)
		{
			for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
			{
				m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
					m_Position.m_Z - m_CurAni->GetHeights()[i] - 100 });
				m_CurAniShowOffset.push_back({ -1000,0 });
			}
		}
		m_BodyCircleColliders.SetCenter({ -100,-100});
		m_BodyCircleColliders.SetRadius(1);
		m_AttackColliders.SetArea({-10,-10,-1,-2});
	}
}

void Baseball::Attack(HDC hdc, RECT winRect)
{
	if (m_Status != ATTACK)
	{

		m_CurAniSpeed = 5;
		m_CurAniFrameNum = 0;
		m_AttackTiming = 8;
		m_AttackTimer = 0;

		if (m_isLookRight)
		{
			if (rand() % 2)
				m_CurAni = m_Animations[BASEBALL_KICK];
			else
				m_CurAni = m_Animations[BASEBALL_PUNCH];
		}

		else
		{
			if (rand() % 2)
				m_CurAni = m_Animations[BASEBALL_KICK_REV];
			else
				m_CurAni = m_Animations[BASEBALL_PUNCH_REV];
		}

		if (!m_CurAni)
		{
			MessageBox(NULL, _T("Baseball Attack m_CurAni -> NULL"), _T("에러"), MB_OK);
			return;
		}

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
			if (m_DamagedTime >= 25)
			{
				m_Status = NOTHING;
				m_DamagedTime = 0;
			}
		}

		else
		{
			if (m_Position.m_Z < player->GetPos().m_Z - z_offest) //같은 z축을 만든다
			{
				if (m_Position.m_Z < 450)
				{
					m_Position = { m_Position.m_X,450,450 };
				}

				m_Velocity.m_Y = m_MoveSpeed;
				m_Velocity.m_Z = m_MoveSpeed;
				Move();
			}

			else if (m_Position.m_Z > player->GetPos().m_Z + z_offest)
			{

				if (m_Position.m_Z > winRect.bottom)
				{
					m_Position = { m_Position.m_X,winRect. bottom, winRect.bottom };
				}

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

