#pragma once
#include<vector>
#include<string>
#include<map>
#include"Animation.h"
#include"Sound.h"
#include"Collider.h"
#include"Vector3.h"
#include<list>
#include"Data_Names.h"

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
	int m_CharactorID;

	Status m_Status;
	Vector3 m_Position = { 0,0,0 };
	Vector3 m_Velocity = { 0,0,0 };
	int m_CurHp;
	int m_MaxHp;
	int m_MoveSpeed;
	bool m_isLookRight = true;	// false == left
	bool m_isAlive = true;
	bool m_takeGravity = true;
	bool m_Jumping = false;
	bool m_StopMove = false;	// 특정 애니매이션에서 다른 동작을 멈추는 것
	int m_CurAniFrameNum = 0;	// 캐릭터 애니매이션의 현재 프레임
	int m_DeadTimer = 0;		// 죽을때 시간 측정용
	int m_DelayTimer = 0;		// 특정 애니메이션에서 멈추는 용 타이머
	int m_Attack = 0;			// 공격력
	int m_AttackTiming = 0;		// 공격 데미지가 들어가는 순간
	int m_AttackTimer = 0;		// 공격 데미지가 들어가는 순간을 측정하는 타이머

	map<string, shared_ptr<Animation>> m_Animations; // 캐릭터의 애니메이션 들
	shared_ptr<Animation> m_CurAni;					// 캐릭터가 현재 하고 있는 애니메이션
	vector<POINT> m_CurAniShowOffset;				// 현재 애니메이션이 위치해야하는 좌표들
	int m_CurAniSpeed = 0;							// 현재 애니메이션 속도

	map<string, shared_ptr<Sound>> m_Sounds;		// 캐릭터가 내는 모든 소리
	shared_ptr<Sound> m_CurSound;					// 현재 캐릭터가 내는 소리

public:
	HBITMAP m_Bitmap;

	Charactor() = default;
	Charactor(int ID, Vector3 pos, int maxhp, int curhp, int attack, int moveSpeed,
		map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds);
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
	int GetDeadTimer() { return m_DeadTimer; }
	void SetDeadTimer(int num) { m_DeadTimer = num; }
	int GetDelayTimer() { return m_DelayTimer; }
	void SetDelayTimer(int num) { m_DelayTimer = num; }
	map<string, shared_ptr<Sound>> GetSounds() { return m_Sounds; }
	void Dead() { if (m_CurHp <= 0) m_isAlive = false; }

	void Update(bool moveOK);
	void ShowCharactor(HDC hdc, int TimeDivRatio, int Timer, RECT winRect);
	virtual void ShowColliders(HDC hdc) = 0;
};

class Player : public Charactor // 상태 패턴
{
protected:
	int m_PlayingDynamite = 0; // 플레이어가 필살기를 쓸 때 순서 확인
	int m_DynamiteTimer = 0;
	int m_Points = 0;			// 플레이어 점수
	RECT m_DynamiteCollderPos = { 0,0,0,0 };
public:
	Player() = default;
	Player(int ID, Vector3 pos, int maxhp, int curhp, int attack, int moveSpeed, map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds)
		: Charactor(ID, pos, maxhp, curhp, attack, moveSpeed, anis, sounds) {
		m_Status = NOTHING;
	};

	virtual ~Player() = default;
	int GetPlayDynamite() { return m_PlayingDynamite; }
	void SetPlayDynamite(int num) { m_PlayingDynamite = num; }
	int GetPoints() { return m_Points; }
	void SetPoints(int num) { m_Points = num; }

	virtual BoxCollider GetBodyCollider() = 0;
	virtual BoxCollider GetAttackCollider() = 0;

	//플레이어 위치, 콜라이더 위치, 데미지 등등...
	virtual void Idle() = 0;
	virtual void Move() = 0;
	virtual void Run() = 0;
	virtual void Jump(bool& keydown, bool jumping) = 0;
	virtual void Damaged(HDC hdc, RECT winRect, bool& keydown) = 0;
	virtual void Dead() = 0;
	virtual void Attack(bool isright) = 0;
	virtual void HomeRun(HDC hdc, RECT winRect, bool& keydown) = 0;
	virtual void Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite) = 0;

	void ShowColliders(HDC hdc) override;

};

class Ryno :public Player
{
private:
	BoxCollider m_BodyColliders;
	BoxCollider m_AttackColliders;

public:
	Ryno() = default;
	Ryno(int ID, Vector3 pos, int maxhp, int curhp, int attack, int moveSpeed,
		map<string, shared_ptr<Animation>>& anis, map<string, shared_ptr<Sound>>& sounds)
		: Player(ID, pos, maxhp, curhp, attack, moveSpeed, anis, sounds) {
		Idle();
	};

	BoxCollider GetBodyCollider() { return m_BodyColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	void Idle() override;
	void Move() override;
	void Run() override;
	void Jump(bool& keydown, bool jumping) override;
	void Damaged(HDC hdc, RECT winRect, bool& keydown) override;
	void Dead() override;
	void Attack(bool isright) override;
	void HomeRun(HDC hdc, RECT winRect, bool& keydown) override;
	void Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite) override;

	void RynoDynamiteEffect(HDC hdc, RECT winRect, bool isRight);
};

class Monster : public Charactor
{
protected:
	int m_DamagedTime = 0;	//공격을 받으면 잠시 일시 정지 하는 시간
	int m_DeadPoints;		//죽을 때 얻는 점수

public:
	Monster() = default;
	Monster(int ID, Vector3 position, int maxhp, int curhp, int attack, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds) :Charactor(ID, position, maxhp, curhp, attack, moveSpeed, anis, sounds) {
		m_isLookRight = false; m_isAlive = false;
	};

	int GetDeadPoints() { return m_DeadPoints; }

	virtual CircleCollider GetBodyCircleCollider() = 0;
	virtual BoxCollider GetBodyCollider() = 0;
	virtual BoxCollider GetAttackCollider() = 0;

	virtual ~Monster() = default;
	virtual void Move() = 0;
	virtual void Damaged(HDC hdc, RECT winRect) = 0;
	virtual void Dead() = 0;
	virtual void Attack(HDC hdc, RECT winRect) = 0;
	virtual void ShowColliders(HDC hdc) = 0;
	virtual void MonsterAI(HDC hdc, RECT winRect, shared_ptr<Player> player, int z_offest) = 0;
};

class Baseball :public Monster
{
private:
	CircleCollider m_BodyCircleColliders;
	BoxCollider m_AttackColliders;

public:
	Baseball() = default;
	Baseball(int ID, Vector3 pos, int maxhp, int curhp, int attack, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds, int deadPoint) : Monster(ID, pos, maxhp, curhp, attack, moveSpeed, anis, sounds) {
		Move(); m_DeadPoints = deadPoint;
	};
	~Baseball() = default;

	CircleCollider GetBodyCircleCollider() { return m_BodyCircleColliders; }
	BoxCollider GetBodyCollider() { return m_AttackColliders; }
	BoxCollider GetAttackCollider() { return m_AttackColliders; }

	void Move();
	void Damaged(HDC hdc, RECT winRect);
	void Dead();
	void Attack(HDC hdc, RECT winRect);
	void MonsterAI(HDC hdc, RECT winRect, shared_ptr<Player> player, int z_offest)override;

	void ShowColliders(HDC hdc)override;
};