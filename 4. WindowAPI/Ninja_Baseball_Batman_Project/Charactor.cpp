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
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[m_CurAniFrameNum], m_CurAniFrameNum, 3.0f, m_isLookRight, winRect);

		if (m_CurAniFrameNum == m_CurAni->GetFrameTotalCount() - 1)
		{
			m_tempTimer++;
			if (m_tempTimer> TimeDivRatio * 2.5f)
			{
				m_StopMove = false;
				m_tempTimer = 0;
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
			m_CurAni->AniPlay(hdc, m_CurAniShowOffset[m_CurAniFrameNum], m_CurAniFrameNum, 3.0f, m_isLookRight, winRect);
	}

}

BOOL Ryno::Born() 
{
	if (m_CurAni != m_Animations["Ryno_born"]) //반복 할당 박기
	{
		m_CurAniShowOffset.clear();
		m_CurAni = m_Animations["Ryno_born"];

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

		m_CurAniSpeed = 4;

		//cout << "Ryno_Born" << endl;
	}

	return 0;
}

BOOL Ryno::Idle()
{
	if (m_CurAni != m_Animations["Ryno_idle"])
	{
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_idle"];
		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

		RECT collderPos = { Charactor::m_Position.m_X, Charactor::m_Position.m_Z-80,
			Charactor::m_Position.m_X + 60, Charactor::m_Position.m_Z +80 };
		m_BodyColliders.SetArea(collderPos);

	}

	m_AttackColliders.SetArea({-1,-1,-1,-1});

	return 0;
}

BOOL Ryno::Move()
{
	if (m_CurAni != m_Animations["Ryno_walk"])
	{
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_walk"];
		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

	}
	return 0;
}

BOOL Ryno::Run()
{
	if (m_CurAni != m_Animations["Ryno_run"])
	{
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_run"];
		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}
	}
	return 0;
}

BOOL Ryno::Jump(bool & keydown, bool jumping)
{

	if (m_CurAni != m_Animations["Ryno_jump"])
	{
		m_CurAni = m_Animations["Ryno_jump"];
		m_CurAniSpeed = 4;
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

	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[i] });
	}

	return 0;
}

BOOL Ryno::Damaged()
{
	if (m_CurAni != m_Animations["Ryno_damaged"] || m_CurAni != m_Animations["Ryno_damaged1"])
	{
		m_CurAniShowOffset.clear();

		int n = rand() % 2;
		if (n) m_CurAni = m_Animations["Ryno_damaged"];
		else m_CurAni = m_Animations["Ryno_damaged1"];
		m_CurAniSpeed = 4;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}
	}

	return 0;
}

BOOL Ryno::Dead()
{

	if (m_CurAni != m_Animations["Ryno_dead"])
	{
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_dead"];
		m_CurAniSpeed = 4;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}
	}
	return 0;
}

BOOL Ryno::NormalAttack(bool isright)
{
	if (m_CurAni != m_Animations["Ryno_attack"])
	{
		m_CurAniShowOffset.clear();

		m_CurAni = m_Animations["Ryno_attack"];
		m_CurAniSpeed = 2;

		for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
		{
			m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
				m_Position.m_Z - m_CurAni->GetHeights()[i] });
		}

	}

	if (isright)
	{
		RECT collderPos = { Charactor::m_Position.m_X + 30, Charactor::m_Position.m_Y - 100,
		Charactor::m_Position.m_X + 180, Charactor::m_Position.m_Y + 80 };
		m_AttackColliders.SetArea(collderPos);
	}

	else
	{
		RECT collderPos = { Charactor::m_Position.m_X - 70, Charactor::m_Position.m_Y - 100,
		Charactor::m_Position.m_X + 80 , Charactor::m_Position.m_Y + 90 };
		m_AttackColliders.SetArea(collderPos);
	}

	return 0;
}

BOOL Ryno::HomeRun()
{
	if (m_CurAni != m_Animations["Ryno_homerun"])
	{
		m_CurAni = m_Animations["Ryno_homerun"];
		m_CurAniSpeed = 3;
	}
		
	
	m_CurAniShowOffset.clear();
	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}

	m_Velocity.m_Y = 0;
	m_Position.m_Y = m_Position.m_Z;
	
	RECT collderPos = { Charactor::m_Position.m_X - 200, Charactor::m_Position.m_Z - 100,
		Charactor::m_Position.m_X + 230, Charactor::m_Position.m_Z + 80 };
	m_AttackColliders.SetArea(collderPos);
	
	m_BodyColliders.SetArea({0,0,0,0});
	
	//cout << "Ryno_Homerun" << endl;

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

		if (m_CurAni != m_Animations["Ryno_fly"])
		{
			m_CurAni = m_Animations["Ryno_fly"];
			m_CurAniSpeed = 2;
		}

		m_CurAniShowOffset.clear();

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[0] / 2),
			m_Position.m_Y - m_CurAni->GetHeights()[0] });

		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[1] / 2 + 12), // 42
			m_Position.m_Y - m_CurAni->GetHeights()[1] -2}); //14


		m_Velocity.m_Y = 0;
		m_Position.m_Y = m_Position.m_Z - 300;

		if (m_isLookRight)
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X + 70, m_Position.m_Y + 40 }, 0, 2.0f, m_isLookRight, winRect);
		}

		else
		{
			m_Animations["Ryno_dynamite_ball"]->AniPlay(hdc, { m_Position.m_X - 70, m_Position.m_Y + 45 }, 0, 2.0f, m_isLookRight, winRect);
		}
		

		if (time > 20)
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

		if (time > 50)
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

		if (m_CurAni != m_Animations["Ryno_dynamite"])
		{
			m_CurAniShowOffset.clear();

			m_CurAni = m_Animations["Ryno_dynamite"];
			m_CurAniSpeed = 4;
			m_Velocity = { 0,0,0 };
		}

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

		if (time > 20)
		{
			m_PlayingDynamite = 0;
			time = temp = temp1 = 0;
			playerDynamite = false;
			SetTakeGravity(true);
		}

	}

	return 0;
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
		m_Status = MOVE;
	}

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 100 });
	}
	
	if(m_isLookRight)
		m_BodyCircleColliders.SetCenter({ m_Position.m_X + 60, m_Position.m_Z -100 });
	else
		m_BodyCircleColliders.SetCenter({ m_Position.m_X + 90, m_Position.m_Z -100 });

	m_BodyCircleColliders.SetRadius(70);
	m_AttackColliders.SetArea({ 0,0,0,0 });

	//cout << "Baseball Idle" << endl;
}

void Baseball::Damaged()
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

		m_Status = DAMAGED;
	}
	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Baseball::Dead()
{
	if (m_Status != DEAD)
	{
		m_CurAni = m_Animations["Baseball_dead"];
		m_CurAniSpeed = 10;
		m_Status = DEAD;
	}

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] });
	}
}

void Baseball::NormalAttack()
{
	if (m_Status != NORMAL_ATTACK)
	{
		if (rand() % 2)
			m_CurAni = m_Animations["Baseball_kick"];
		else
			m_CurAni = m_Animations["Baseball_punch"];

		m_CurAniSpeed = 10;

		m_Status = NORMAL_ATTACK;
	}

	m_CurAniShowOffset.clear();

	for (int i = 0; i < m_CurAni->GetFrameTotalCount(); i++)
	{
		m_CurAniShowOffset.push_back({ m_Position.m_X - (m_CurAni->GetWidths()[i] / 2),
			m_Position.m_Z - m_CurAni->GetHeights()[i] - 130 });
	}

	RECT collderPos;

	if (m_isLookRight)
	{
		collderPos = { Charactor::m_Position.m_X - 80, Charactor::m_Position.m_Z - 200,
						Charactor::m_Position.m_X + 20 , Charactor::m_Position.m_Z - 100 };
	}

	else
	{
		collderPos = { Charactor::m_Position.m_X + 150, Charactor::m_Position.m_Z - 200,
						Charactor::m_Position.m_X + 230, Charactor::m_Position.m_Z - 100 };
	}

	m_AttackColliders.SetArea(collderPos);

	//cout << "Baseball Attack!!" << endl;
}

void Baseball::MonsterAI(shared_ptr<Player> player, int z_offest)
{
	//시선 처리
	if (m_Position.m_X - player->GetPos().m_X > 0)m_isLookRight = true;
	else m_isLookRight = false;

	if (m_Status != DAMAGED)
	{
		//Damaged();

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
				NormalAttack();
			}

		}

	}
}

void Baseball::ShowColliders(HDC hdc)
{
	GetBodyCircleCollider().ShowCollider(hdc);
	GetAttackCollider().ShowCollider(hdc);
}

