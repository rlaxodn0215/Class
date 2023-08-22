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

enum Status
{
	NOTHING,
	IDLE,
	MOVE,
	RUN,
	JUMP,
	ATTACK,
	HOME_RUN,
	DYNAMITE,
	DAMAGED,
	DEAD
};

class Charactor
{
protected:
	Status m_Status;
	Vector3 m_Position = {0,0,0};
	Vector3 m_Velocity = {0,0,0};
	int m_CurHp;
	int m_MaxHp;
	int m_MoveSpeed;
	bool m_isLookRight = true;// false == left
	bool m_isAlive = true;
	bool m_takeGravity = true;
	bool m_Jumping = false;
	bool m_StopMove = false;
	int m_CurAniFrameNum = 0;
	int m_tempTimer = 0;
	int m_Attack = 0;
	int m_AttackTiming = 0;
	int m_AttackTimer = 0;

	map<string, shared_ptr<Animation>> m_Animations;
	shared_ptr<Animation> m_CurAni;
	vector<POINT> m_CurAniShowOffset;
	int m_CurAniSpeed = 0;

	map<string, shared_ptr<Sound>> m_Sounds;
	shared_ptr<Sound> m_CurSound;

public:
	HBITMAP m_Bitmap;

	Charactor() = default;
	Charactor(Vector3 pos, int maxhp,int curhp, int moveSpeed,
		map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds);
	~Charactor() = default;


	Status GetStatus() { return m_Status; }
	void SetStatus(Status st) { m_Status = st; }
	Vector3 GetPos() { return m_Position; }
	void SetPos(Vector3 vec) { m_Position = vec; }
	Vector3 GetVel() { return m_Velocity; }
	void SetVel(Vector3 vec) { m_Velocity = vec; }
	int GetMaxHP() { return m_MaxHp; }
	void SetMaxHP(int hp) { m_MaxHp = hp; }
	int GetCurHP() { return m_CurHp; }
	void SetCurHP(int hp) { m_CurHp = hp; }
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
	int GetAttack() { return m_Attack; }
	void SetAttack(int num) { m_Attack = num; }
	shared_ptr<Animation> GetCurAni() { return m_CurAni; }
	int GetAttackTimer() { return m_AttackTimer; }
	void SetAttackTimer(int num) { m_AttackTimer = num; }
	int GetAttackTiming() { return m_AttackTiming; }
	void SetAttackTiming(int num) { m_AttackTiming = num; }
	int GetTempTimer() { return m_tempTimer; }
	void SetTempTimer(int num) { m_tempTimer = num; }
	shared_ptr<Sound> GetSounds() { return m_CurSound; }

	void Dead() { if (m_CurHp <= 0)m_isAlive = false; }
	void Update(bool moveOK);
	void ShowCharactor(HDC hdc, int TimeDivRatio, int Timer, RECT winRect);
	virtual void ShowColliders(HDC hdc) = 0;
};

class Player : public Charactor // 상태 패턴
{
protected:
	int m_PlayingDynamite = 0;
	int m_PlayerLife = 3;
	int m_Points = 0;

public:
	Player() = default;
	Player(Vector3 pos, int maxhp, int curhp, int moveSpeed, map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
		: Charactor(pos, maxhp,curhp, moveSpeed, anis, sounds) {
		m_Status = NOTHING;
	};

	virtual ~Player() = default;
	int GetPlayDynamite() { return m_PlayingDynamite; }
	void SetPlayDynamite(int num) { m_PlayingDynamite=num; }

	int GetPlayerLife() { return m_PlayerLife; }
	void SetPlayerLife(int num) { m_PlayerLife = num; }
	int GetPoints() { return m_Points; }
	void SetPoints(int num) { m_Points = num; }

	virtual BoxCollider GetBodyCollider() = 0;
	virtual BoxCollider GetAttackCollider() = 0;

	//플레이어 위치, 콜라이더 위치, 데미지 등등...
	virtual BOOL Idle()=0;
	virtual BOOL Move() = 0;
	virtual BOOL Run() = 0;
	virtual BOOL Jump(bool& keydown, bool jumping)=0;
	virtual BOOL Damaged()=0;
	virtual BOOL Dead()=0;
	virtual BOOL Attack(bool isright)=0;
	virtual BOOL HomeRun()=0;
	virtual BOOL Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite)=0;

	void ShowColliders(HDC hdc) override;

};

class Ryno :public Player
{
private:
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;
	
public:
	Ryno() = default;
	Ryno(Vector3 pos, int maxhp, int curhp, int moveSpeed, 
		map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds)
		: Player(pos, maxhp,curhp, moveSpeed, anis, sounds) { Idle();};

	BoxCollider GetBodyCollider() { return m_BodyColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	BOOL Idle() override;
	BOOL Move() override;
	BOOL Run() override;
	BOOL Jump(bool& keydown, bool jumping) override;
	BOOL Damaged() override;
	BOOL Dead() override;
	BOOL Attack(bool isright) override;
	BOOL HomeRun() override;
	BOOL Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite) override;
};

class Monster : public Charactor
{
protected:
	int m_DamagedTime = 0;
	int m_DeadPoints;
public:
	Monster() = default;
	Monster(Vector3 position, int maxhp,int curhp, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds) :Charactor(position, maxhp,curhp, moveSpeed, anis, sounds) {
		m_isLookRight = false;
	};
	
	int GetDeadPoints() { return m_DeadPoints; }

	virtual CircleCollider GetBodyCircleCollider() = 0;
	virtual BoxCollider GetBodyCollider() = 0;
	virtual BoxCollider GetAttackCollider() = 0;

	virtual ~Monster() = default;
	virtual void Move()=0;
	virtual void Damaged()=0;
	virtual void Dead()=0;
	virtual void Attack()=0;
	virtual void ShowColliders(HDC hdc) = 0;
	virtual void MonsterAI(shared_ptr<Player> player, int z_offest) = 0;
};

class Baseball :public Monster
{
private:
	CircleCollider m_BodyCircleColliders;
	BoxCollider m_AttackColliders;

public:
	Baseball()=default;
	Baseball(Vector3 pos, int maxhp, int curhp, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds, int deadPoint) : Monster(pos, maxhp, curhp, moveSpeed, anis, sounds) {
		Move(); m_DeadPoints = deadPoint;
	};
	~Baseball()=default;

	CircleCollider GetBodyCircleCollider() { return m_BodyCircleColliders; }
	BoxCollider GetBodyCollider() { return m_AttackColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	void Move();
	void Damaged();
	void Dead();
	void Attack();
	void MonsterAI(shared_ptr<Player> player, int z_offest)override;

	void ShowColliders(HDC hdc)override;
};