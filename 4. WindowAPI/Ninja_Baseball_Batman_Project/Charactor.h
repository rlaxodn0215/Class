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
	Vector3 m_Velocity = {0,0,0};
	int m_Hp;
	int m_MoveSpeed;
	bool m_isLookRight = true;// false == left
	bool m_isAlive = true;

	map<string, shared_ptr<Animation>> m_Animations;
	shared_ptr<Animation> m_CurAni;
	vector<POINT> m_CurAniShowOffset;
	int m_CurAniSpeed = 0;

	map<string, shared_ptr<Sound>> m_Sounds;
	shared_ptr<Sound> m_CurSound;

public:
	Charactor() = default;
	Charactor(Vector3 pos, int hp, int moveSpeed,
		map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds);
	~Charactor() = default;

	Vector3 GetPos() { return m_Position; }
	void SetPos(Vector3 vec) { m_Position = vec; }
	Vector3 GetVel() { return m_Velocity; }
	void SetVel(Vector3 vec) { m_Velocity = vec; }
	int GetHP() { return m_Hp; }
	void SetHP(int hp) { m_Hp = hp; }
	int GetMoveSpeed() { return m_MoveSpeed; }
	int GetAniSpeed() { return m_CurAniSpeed; }

	void ShowCharactor(HDC hdc, int frameTime, int Timer);
};

class Player : public Charactor // 상태 패턴
{
protected:
	PlayerStatus m_PlayerStatus = BORN;

public:
	Player() = default;
	Player(Vector3 pos, int hp, int moveSpeed, map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
		: Charactor(pos, hp, moveSpeed, anis, sounds) {};

	virtual ~Player() = default;
	PlayerStatus GetPlayerStatus() { return m_PlayerStatus; }
	void SetPlayerStatus(int i) { m_PlayerStatus = (PlayerStatus)i; }

	//BOOL (Player::* PlayerPlaying)();

	//플레이어 위치, 콜라이더 위치, 데미지 등등...
	virtual BOOL Born() = 0;
	virtual BOOL Idle()=0;
	virtual BOOL Move() = 0;
	virtual BOOL Run() = 0;
	virtual BOOL Jump()=0;
	virtual BOOL Damaged()=0;
	virtual BOOL Dead()=0;
	virtual BOOL NormalAttack()=0;
	virtual BOOL JumpAttack()=0;
	virtual BOOL SlidingAttack()=0;
	virtual BOOL HomeRun()=0;
	virtual BOOL Catch()=0;
	virtual BOOL CatchAttack()=0;
	virtual BOOL CatchThrow()=0;
	virtual BOOL LayDownAttack()=0;
	virtual BOOL SpecialCatchAttack()=0;
	virtual BOOL BearHandMode()=0;
	virtual BOOL BearHandMove()=0;
	virtual BOOL BearHandAttack()=0;
	virtual BOOL CatchDynamite()=0;

};

class Ryno :public Player
{
private:
	PlayerCharactor m_Charactor = RYNO;
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
	int m_PlayerLife = 3;
	int m_Points = 0;

public:
	Ryno() = default;
	Ryno(Vector3 pos, int hp, int moveSpeed, 
		map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds)
		: Player(pos, hp, moveSpeed, anis, sounds) { Born();};

	BOOL Born() override;
	BOOL Idle() override;
	BOOL Move() override;
	BOOL Run() override;
	BOOL Jump() override;
	BOOL Damaged() override;
	BOOL Dead() override;
	BOOL NormalAttack() override;
	BOOL JumpAttack() override;
	BOOL SlidingAttack() override;
	BOOL HomeRun() override;
	BOOL Catch() override;
	BOOL CatchAttack() override;
	BOOL CatchThrow() override;
	BOOL LayDownAttack() override;
	BOOL SpecialCatchAttack() override;
	BOOL BearHandMode() override;
	BOOL BearHandMove() override;
	BOOL BearHandAttack() override;
	BOOL CatchDynamite() override;
};

class Monster : public Charactor
{
public:
	Monster() = default;
	virtual ~Monster() = default;
	void MoveUpdate();
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