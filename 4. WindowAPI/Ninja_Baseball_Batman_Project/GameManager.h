#pragma once
#include<map>
#include<string>
#include"UI.h"
#include"Camera.h"
#include"Charactor.h"
#include"Stage.h"
#include"Sound.h"

class GameManager //�̱������� �����.
{
private:
	int m_CurStageNum;
	int m_PlayerLife;
	int m_PlayerHP;
	int m_BossMonsterHP;
	map<string, UI> m_UIs; // �������� data ���� UI

public:
	GameManager();
	GameManager(int playerLife,int playerHP, int curStageNum, int bossMosterHP, map<string, UI>  & UI);
	~GameManager() {};

	void ShowPlayerLife(const Charactor & player);
	void ShowPlayerHPbar(const Charactor& player);
	void ShowPlayerStateUI(const Charactor& player);
	void ShowBossHPbar(const Charactor& Boss);
	void SlowMotion();
	void GameOver();
};

