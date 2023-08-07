#pragma once
#include<map>
#include<string>
#include"Camera.h"
#include"Charactor.h"
#include"Stage.h"
#include"Sound.h"

class GameManager //싱글턴으로 만든다.
{
private:
	int m_CurStageNum;
	int m_PlayerLife;
	int m_PlayerHP;
	int m_BossMonsterHP;

public:
	GameManager();
	GameManager(int playerLife,int playerHP, int curStageNum, int bossMosterHP);
	~GameManager() {};

	void ShowPlayerLife(const Charactor & player);
	void ShowPlayerHPbar(const Charactor& player);
	void ShowPlayerStateUI(const Charactor& player);
	void ShowBossHPbar(const Charactor& Boss);
	void SlowMotion();
	void GameOver();
};

