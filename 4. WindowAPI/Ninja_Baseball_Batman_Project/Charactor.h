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

enum PlayerStatus
{
	BORN,
	IDLE,
	MOVE,
	NORMAL_ATTACK,
	JUMP,
	JUMP_ATTACK,
	DAMAGED,
	LAY_DOWN,
	DEAD,
	SLIDE,
	SLIDE_ATTACK,
	HOME_RUN,
	CATCH,
	CATCH_ATTACK,
	SPECIAL_CATCH_ATTACK,
	CATCH_THROW,
	LAYDOWN_ATTACK,
	BEARHAND_MODE,
	BEARHAND_ATTACK,
	CATCH_DYNAMITE
};

class Charactor
{
protected:
	Vector3 m_Position;
	int m_Hp;
	int m_MoveSpeed;
	bool m_isLookRight;// false == left
	bool m_isAlive;
	map<string, shared_ptr<Animation>> m_CharactorAnis;
	map<string, shared_ptr<Sound>> m_CharactorSounds;
	shared_ptr<Animation> m_CurAni;
	shared_ptr<Sound> m_CurSound;

public:
	Charactor() = default;
	Charactor(Vector3 pos, int hp, int moveSpeed, bool lookright, bool alive, 
		map<string, shared_ptr<Animation>> charactorAni, map<string, shared_ptr<Sound>> charactorSound);
	virtual~Charactor() = default;

	int GetHP() { return m_Hp; }
	void SetHP(int hp) { m_Hp = hp; }
	void MoveUpdate();
	void ChangeAni(const string aniName);
};

class Player : public Charactor // 상태 패턴
{
protected:
	PlayerStatus m_PlayerStatus;

public:
	Player() = default;
	virtual ~Player() = default;
	PlayerStatus GetPlayerStatus() { return m_PlayerStatus; }
	void SetPlayerStatus(int i) { m_PlayerStatus = (PlayerStatus)i; }

	virtual BOOL Idle()=0;
	virtual BOOL Jump()=0;
	virtual BOOL Damaged()=0;
	virtual BOOL Dead()=0;
	virtual BOOL NormalAttack()=0;
	virtual BOOL JumpAttack()=0;
	virtual BOOL Sliding()=0;
	virtual BOOL SlidingAttack()=0;
	virtual BOOL HomeRun()=0;
	virtual BOOL Catch()=0;
	virtual BOOL CatchAttack()=0;
	virtual BOOL CatchThrow()=0;
	virtual BOOL LayDownAttack()=0;
	virtual BOOL SpecialCatchAttack()=0;
	virtual BOOL BearHandMode()=0;
	virtual BOOL BearHandAttack()=0;
	virtual BOOL CatchDynamite()=0;

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
	BOOL Idle() override;
	BOOL Jump() override;
	BOOL Damaged() override;
	BOOL Dead() override;
	BOOL NormalAttack() override;
	BOOL JumpAttack() override;
	BOOL Sliding() override;
	BOOL SlidingAttack() override;
	BOOL HomeRun() override;
	BOOL Catch() override;
	BOOL CatchAttack() override;
	BOOL CatchThrow() override;
	BOOL LayDownAttack() override;
	BOOL SpecialCatchAttack() override;
	BOOL BearHandMode() override;
	BOOL BearHandAttack() override;
	BOOL CatchDynamite() override;
};

class Monster : public Charactor
{
public:
	Monster() = default;
	virtual ~Monster() = default;
	virtual void Idle()=0;
	virtual void Damaged()=0;
	virtual void Dead()=0;
	virtual void NormalAttack()=0;
};

class Baseball :public Monster
{
private:
	MonsterCharactor m_Charactor;
	CircleCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
public:
	void Idle();
	void Damaged();
	void Dead();
	void NormalAttack();
};