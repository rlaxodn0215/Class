#pragma once
#include<map>
#include<string>
#include<iostream>
#include"Camera.h"
#include"Charactor.h"
#include"Stage.h"
#include"SingletonTemplate.h"

class GameManager : public SingletonTemplate<GameManager> //싱글턴으로 만든다.
{
private:
	friend SingletonTemplate; //friend 키워드: SingletonTemplate이 GameManager class의 모든 멤버를 사용할 수 있다
	GameManager();
	~GameManager();

public:
	int m_SceneNum = 0;
	POINT m_Cursor = { 50,150 }; //(50,150), +220
	Stage* m_Stage;
	Player* m_Player;
	Camera* m_Cam;

	int m_SelectPosX[4] = {50,285,520,755};
	bool m_SelectFlag = false;
	bool m_KeyFlag[6] = {};
	bool m_ComboFlag[6] = {}; //
	int m_Timer = 500;
	int m_ComboTimerCount = 0;

	void ShowTimer(HDC hdc, vector<shared_ptr<Animation>>& timerAni);
	void CheckKeyInput(Player * player, int sceneNum);
	void CheckKeyRelease(WPARAM wParam);
	void ShowPlayerLife(const Charactor & player);
	void ShowPlayerHPbar(const Charactor& player);
	void ShowBossHPbar(const Charactor& Boss);
	void ShowPlayerStateUI(const Charactor& player);
	void ShowPlayerPoints(const Charactor& player);
	void MoveNextStage();
	void SlowMotion();
	void GameOver(); // Rank 포함
};

