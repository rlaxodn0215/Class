#pragma once
#include<vector>
#include<string>
#include<map>
#include"Animation.h"
#include"Sound.h"
#include"Collider.h"
#include"Vector3.h"

using namespace std;

enum PlayerCharactor
{
	JOSE,
	RYNO,
	ROGER,
	STRAW
};

enum MonsterCharactor
{
	BASEBALL,
	BAT,
	CARD_RED,
	CARD_YELLW,
	CARD_GREEN,
	CARD_BLUE,
	WINDYPLANE
};

enum playerState
{

};

class Charactor
{
protected:
	Vector3 m_Position;
	int m_Hp;
	int m_MoveSpeed;
	int m_LookWay;
	bool m_isAlive;
	map<string, Animation*> CharactorAni;
	map<string, Sound> CharactorSound;

public:
	Charactor();
	virtual~Charactor();

	int GetHP() { return m_Hp; }
	void SetHP(int hp) { m_Hp = hp; }
	void Update();
	void ChangeAni(const string & beforeAniName, const string & afterAniName);
	void ShowCharactorStatus();
};

class Player : public Charactor // 상태 패턴
{
public:
	virtual ~Player() = default;
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

class Ryno :public Player
{
private:
	PlayerCharactor m_Charactor;
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
	int m_PlayerLife;
	int m_Points;

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

class Monster : public Charactor
{
public:
	~Monster();
	void Idle();
	void Damaged();
	void Dead();
	void NormalAttack();
};

class Baseball :public Monster
{
private:
	MonsterCharactor m_Charactor;
	CircleCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
};