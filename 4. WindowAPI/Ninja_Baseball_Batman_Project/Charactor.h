#pragma once
#include<vector>
#include<string>
#include<map>
#include"Animation.h"
#include"Sound.h"
#include"Collider.h"
#include"Vector3.h"

using namespace std;

//enum MonsterCharactor
//{
//	BASEBALL,
//	BAT,
//	CARD_RED,
//	CARD_YELLW,
//	CARD_GREEN,
//	CARD_BLUE,
//	WINDYPLANE
//};

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
	bool m_takeGravity = true;

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

	void Update();
	void ShowCharactor(HDC hdc, int TimeDivRatio, int Timer, bool& aniWait,RECT winRect);
};

class Player : public Charactor // 상태 패턴
{
protected:
	PlayerStatus m_PlayerStatus = BORN;
	int m_PlayingDynamite = 0;

public:
	Player() = default;
	Player(Vector3 pos, int hp, int moveSpeed, map<string, shared_ptr<Animation>> & anis, map<string, shared_ptr<Sound>> & sounds)
		: Charactor(pos, hp, moveSpeed, anis, sounds) {};

	virtual ~Player() = default;
	PlayerStatus GetPlayerStatus() { return m_PlayerStatus; }
	void SetPlayerStatus(int i) { m_PlayerStatus = (PlayerStatus)i; }
	int GetPlayDynamite() { return m_PlayingDynamite; }
	void SetPlayDynamite(int num) { m_PlayingDynamite=num; }

	//BOOL (Player::* PlayerPlaying)();

	//플레이어 위치, 콜라이더 위치, 데미지 등등...
	virtual BOOL Born() = 0;//
	virtual BOOL Idle()=0;//
	virtual BOOL Move() = 0;//
	virtual BOOL Run() = 0;//
	virtual BOOL Jump(bool& keydown, bool& jumping)=0;//
	virtual BOOL Damaged()=0;
	virtual BOOL Dead()=0;
	virtual BOOL NormalAttack(bool isright)=0;//
	virtual BOOL HomeRun()=0;//
	virtual BOOL Catch()=0;
	virtual BOOL CatchAttack()=0;
	virtual BOOL CatchThrow()=0;
	virtual BOOL Dynamite(HDC hdc, int timer, RECT winRect, bool& playerDynamite)=0;

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
	BOOL Jump(bool& keydown, bool& jumping) override;
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
		map<string, shared_ptr<Sound>>& sounds) :Charactor(position,Hp,moveSpeed,anis,sounds) {};
	virtual ~Monster() = default;
	virtual void Idle()=0;
	virtual void Damaged()=0;
	virtual void Dead()=0;
	virtual void NormalAttack()=0;
	virtual void FollowPlayer() = 0;
};

class Baseball :public Monster
{
private:
	CircleCollider m_BodyColliders;
	BoxCollider m_AttackColliders;

public:
	Baseball()=default;
	Baseball(Vector3 pos, int hp, int moveSpeed, map<string, shared_ptr<Animation>>& anis,
		map<string, shared_ptr<Sound>>& sounds) : Monster(pos, hp, moveSpeed, anis, sounds) {
		Idle();
	};
	~Baseball()=default;
	void Idle();
	void Damaged();
	void Dead();
	void NormalAttack();
	void FollowPlayer();
};