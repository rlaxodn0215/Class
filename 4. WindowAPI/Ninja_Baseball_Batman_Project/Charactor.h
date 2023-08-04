#pragma once
#include<vector>
#include<string>
#include<map>
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
	map<string, Animation> CharactorAni;
	map<string, Sound> CharactorSound;

public:
	Charactor();
	virtual~Charactor();

	int GetHP() { return m_Hp; }
	void SetHP(int hp) { m_Hp = hp; }
	void ChangeAni(const string & beforeAniName, const string & afterAniName);
	void ShowCharactorStatus();
};

class Player : public Charactor
{
protected:
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
	int m_Points;

public:
	virtual void Idle()=0;
	virtual void Jump()=0;
	virtual void Damaged()=0;
	virtual void LowHP()=0;
	virtual void Dead()=0;
	virtual void NormalAttack()=0;
	virtual void Sliding()=0;
	virtual void HomeRun()=0;
	virtual void Catch()=0;
	virtual void LayDownAttack()=0;
	virtual void SpecialCatchAttack()=0;
	virtual void BearHandMode()=0;
	virtual void BearHandAttack()=0;

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

