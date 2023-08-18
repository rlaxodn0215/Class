#pragma once
#include<vector>
#include<string>
#include<map>
#include"Animation.h"
#include"Sound.h"
#include"Collider.h"
#include"Vector3.h"
#include<list>

using namespace std;

enum MonsterStatus
{
	NOTHING,
	MOVE,
	NORMAL_ATTACK,
	DAMAGED,
	DEAD
};

class Charactor
{
protected:
	Vector3 m_Position = {0,0,0};
	Vector3 m_Velocity = {0,0,0};
	int m_Hp;
	int m_MoveSpeed;
	bool m_isLookRight = true;// false == left
	bool m_isAlive = true;
	bool m_takeGravity = true;
	bool m_Jumping = false;
	bool m_StopMove = false;
	int m_CurAniFrameNum = 0;
	int m_tempTimer = 0;

	map<string, shared_ptr<Animation>> m_Animations;
	shared_ptr<Animation> m_CurAni;
	vector<POINT> m_CurAniShowOffset;
	int m_CurAniSpeed = 0;

	map<string, shared_ptr<Sound>> m_Sounds;
	shared_ptr<Sound> m_CurSound;

public:
	HBITMAP m_Bitmap;

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
	bool GetLookRight() { return m_isLookRight; }
	void SetLookRight(bool way) { m_isLookRight = way; }
	bool GetAlive() { return m_isAlive; }
	void SetAlive(bool live) { m_isAlive = live; }
	bool GetTakeGravity() { return m_takeGravity; }
	void SetTakeGravity(bool takeG) { m_takeGravity = takeG; }
	bool GetJumping() { return m_Jumping; }
	void SetJumping(bool j) { m_Jumping = j; }
	bool GetStopMove() { return m_StopMove; }
	void SetStopMove(bool s) { m_StopMove = s; }

	void Update(bool moveOK);
	void ShowCharactor(HDC hdc, int TimeDivRatio, int Timer, RECT winRect);
	virtual void ShowColliders(HDC hdc) = 0;
};

class Player : public Charactor // 상태 패턴
{
protected:
	int m_PlayingDynamite = 0;

public:
	Player() = default;
	Player(Vector3 pos, int hp, int moveSpeed, map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
		: Charactor(pos, hp, moveSpeed, anis, sounds) {};

	virtual ~Player() = default;
	int GetPlayDynamite() { return m_PlayingDynamite; }
	void SetPlayDynamite(int num) { m_PlayingDynamite=num; }

	//플레이어 위치, 콜라이더 위치, 데미지 등등...
	virtual BOOL Born() = 0;//
	virtual BOOL Idle()=0;//
	virtual BOOL Move() = 0;//
	virtual BOOL Run() = 0;//
	virtual BOOL Jump(bool& keydown, bool jumping)=0;//
	virtual BOOL Damaged()=0;
	virtual BOOL Dead()=0;
	virtual BOOL NormalAttack(bool isright)=0;//
	virtual BOOL HomeRun()=0;//
	virtual BOOL Catch()=0;
	virtual BOOL CatchAttack()=0;
	virtual BOOL CatchThrow()=0;
	virtual BOOL Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite)=0;

	//virtual void ShowColliders(HDC hdc) = 0;
	void ShowColliders(HDC hdc) override;

};

class Ryno :public Player
{
private:
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
	int m_PlayerLife = 3;
	int m_Points = 0;
	
public:
	Ryno() = default;
	Ryno(Vector3 pos, int hp, int moveSpeed, 
		map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds)
		: Player(pos, hp, moveSpeed, anis, sounds) { Born();};

	BoxCollider GetBodyCollider() { return m_BodyColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	BOOL Born() override;
	BOOL Idle() override;
	BOOL Move() override;
	BOOL Run() override;
	BOOL Jump(bool& keydown, bool jumping) override;
	BOOL Damaged() override;
	BOOL Dead() override;
	BOOL NormalAttack(bool isright) override;
	BOOL HomeRun() override;
	BOOL Catch() override;
	BOOL CatchAttack() override;
	BOOL CatchThrow() override;
	BOOL Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite) override;
};

class Monster : public Charactor
{
public:
	Monster() = default;
	Monster(Vector3 position, int Hp, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds) :Charactor(position, Hp, moveSpeed, anis, sounds) {
		m_isLookRight = false;
	};
	virtual ~Monster() = default;
	virtual void Move()=0;
	virtual void Damaged()=0;
	virtual void Dead()=0;
	virtual void NormalAttack()=0;
	virtual void ShowColliders(HDC hdc) = 0;
	virtual void MonsterAI(Player* player, int z_offest) = 0;
};

class Baseball :public Monster
{
private:
	MonsterStatus m_Status;
	CircleCollider m_BodyColliders;
	BoxCollider m_AttackColliders;

public:
	Baseball()=default;
	Baseball(Vector3 pos, int hp, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds) : Monster(pos, hp, moveSpeed, anis, sounds) {
		m_Status = NOTHING; Move();
	};
	~Baseball()=default;

	CircleCollider GetBodyCollider() { return m_BodyColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	void Move();
	void Damaged();
	void Dead();
	void NormalAttack();
	void MonsterAI(Player* player, int z_offest)override;

	void ShowColliders(HDC hdc)override;
};