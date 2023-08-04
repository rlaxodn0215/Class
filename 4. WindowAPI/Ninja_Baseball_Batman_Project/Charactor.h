#pragma once
#include<vector>
#include<string>
#include"Animation.h"
#include"Sound.h"
#include"CircleCollider.h"
#include"BoxCollider.h"
#include"Vector3.h"

using namespace std;

enum player
{
	JOSE,
	RYNO,
	ROGER,
	STRAW
};

enum playerState
{

};

enum monster
{
	BASEBALL,
	BAT,
	CARD_RED,
	CARD_YELLW,
	CARD_GREEN,
	CARD_BLUE,
	WINDYPLANE
};

class Charactor
{
protected:
	Vector3 m_Position;
	int m_Hp;
	int m_MoveSpeed;
	int m_LookWay;
	bool m_isAlive;
	vector<Animation> CharAni;
	vector<Sound> CharSound;

public:
	Charactor();
	virtual~Charactor();

	int GetHP() { return m_Hp; }
	void SetHP(int hp) { m_Hp = hp; }
};

class Player : public Charactor
{
protected:
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;

public:
	virtual void Idle()=0;
	virtual void Jump()=0;
	virtual void Damaged()=0;
	virtual void LowHP()=0;
	virtual void Dead()=0;
	virtual void NormalAttack()=0;
	virtual void JumpAttack()=0;
	virtual void Sliding()=0;
	virtual void SlidingAttack()=0;
	virtual void WakeUpAttack()=0;
	virtual void HomeRun()=0;
	virtual void Catch()=0;
	virtual void CatchAttack()=0;
	virtual void CatchThrow()=0;
	virtual void LayDownAttack()=0;
	virtual void SpecialCatchAttack()=0;
	virtual void BearHandMode()=0;
	virtual void BearHandAttack()=0;
	virtual void CatchDynamite()=0;

};

class Monster : public Charactor
{
public:
	virtual void Idle() = 0;
	virtual void Damaged() = 0;
	virtual void Dead() = 0;
	virtual void NormalAttack() = 0;
};

class Ryno : public Player
{
public:
	void Idle();
	void Jump();
	void Damaged();
	void LowHP();
	void Dead();
	void NormalAttack();
	void JumpAttack();
	void Sliding();
	void SlidingAttack();
	void WakeUpAttack();
	void HomeRun();
	void Catch();
	void CatchAttack();
	void CatchThrow();
	void LayDownAttack();
	void SpecialCatchAttack();
	void BearHandMode();
	void BearHandAttack();
	void CatchDynamite();
};

class Baseball : public Monster
{
private:
	CircleCollider m_BodyCollider;
	BoxCollider m_AttackCollider;

public:

};

class Bat : public Monster
{

};

class Card : public Monster
{

};

class WindyPlane : public Monster
{

};










class Jose : public Player
{

};


class Roger : public Player
{

};

class Straw : public Player
{

};

