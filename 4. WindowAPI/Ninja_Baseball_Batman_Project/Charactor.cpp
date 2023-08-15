#include "Charactor.h"

Charactor::Charactor(Vector3 pos, int hp, int moveSpeed)
{
	m_Position = pos;
	m_Hp = hp;
	m_MoveSpeed = moveSpeed;
	m_CurAni = NULL;
	m_CurSound = NULL;
}

Player::Player(Vector3 pos, int hp, int moveSpeed) : Charactor(pos,hp,moveSpeed) {}

Ryno::Ryno(Vector3 pos, int hp, int moveSpeed) : Player(pos, hp, moveSpeed) {}


BOOL Ryno::Born()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_born"];
	return 0;
}

BOOL Ryno::Idle()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_idle"];
	RECT collderPos = {Charactor::m_Position.m_Pos_X, Charactor::m_Position.m_Pos_Y, 
		Charactor::m_Position.m_Pos_X + 20, Charactor::m_Position.m_Pos_Y + 20};
	m_BodyColliders.SetArea(collderPos);
	return 0;
}

BOOL Ryno::Move()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_walk"];
	return 0;
}

BOOL Ryno::Jump()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_jump"];
	return 0;
}

BOOL Ryno::Damaged()
{
	int n = rand() % 2;
	if(n) m_CurAni = GameManager::GetInstance()->Animations["Ryno_damaged"];
	else m_CurAni = GameManager::GetInstance()->Animations["Ryno_damaged1"];

	return 0;
}

BOOL Ryno::Dead()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_dead"];
	return 0;
}

BOOL Ryno::NormalAttack()
{
	m_CurAni = GameManager::GetInstance()->Animations["Ryno_attack"];
	return 0;
}

BOOL Ryno::JumpAttack()
{
	//m_CurAni = GameManager::GetInstance()->Animations["Ryno_dead"];
	return 0;
}

BOOL Ryno::Sliding()
{
	return 0;
}

BOOL Ryno::SlidingAttack()
{
	return 0;
}

BOOL Ryno::HomeRun()
{
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

BOOL Ryno::BearHandMode()
{
	return 0;
}

BOOL Ryno::BearHandMove()
{
	return 0;
}

BOOL Ryno::BearHandAttack()
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
