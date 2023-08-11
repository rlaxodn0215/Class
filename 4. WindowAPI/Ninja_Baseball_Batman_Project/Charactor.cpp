#include "Charactor.h"

Charactor::Charactor(Vector3 pos, int hp, int moveSpeed, bool lookright, bool alive,
	map<string, shared_ptr<Animation>> charactorAni, map<string, shared_ptr<Sound>> charactorSound)
{
	m_Position = pos;
	m_Hp = hp;
	m_MoveSpeed = moveSpeed;
	m_isLookRight = lookright;
	m_isAlive = alive;
	m_CharactorAnis = charactorAni;
	m_CharactorSounds = charactorSound;
	m_CurAni = NULL;
	m_CurSound = NULL;
}


void Charactor::MoveUpdate()
{
	
}

void Charactor::ChangeAni(const string aniName)
{
	m_CurAni = m_CharactorAnis[aniName];
}

BOOL Ryno::Idle()
{
	return 0;
}

BOOL Ryno::Jump()
{
	return 0;
}

BOOL Ryno::Damaged()
{
	return 0;
}

BOOL Ryno::Dead()
{
	return 0;
}

BOOL Ryno::NormalAttack()
{
	return 0;
}

BOOL Ryno::JumpAttack()
{
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

BOOL Ryno::BearHandAttack()
{
	return 0;
}

BOOL Ryno::CatchDynamite()
{
	return 0;
}
