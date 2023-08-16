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
	map<string, shared_ptr<Sprite>> Sprites;
	map<string, shared_ptr<Animation>> Animations;
	map<string, shared_ptr<Sound>> Sounds;

	vector<shared_ptr<Animation>> Timer_ani;
	int m_SceneNum = 0;

	void(GameManager:: * m_Scene)(HDC,HBITMAP&);
	Stage* m_Stage;
	Player* m_Player;
	Camera* m_Cam;

	POINT m_Cursor = { 50,150 }; //(50,150), +220
	int m_SelectPosX[4] = {50,290,530,765};
	bool m_SelectFlag = false;

	bool m_KeyFlag[6] = {}; //0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_Jumping;
	bool m_ComboFlag[6] = {}; 
	bool m_AniWait;

	int m_TimerFrame = 0;
	int m_SelectTimer = 20*10;
	int m_ComboTimerCount = 0;

	void GetSentence(int& i, char* buff, char* sentence);
	void LoadSprites(const TCHAR dataFileName[100], map<string, shared_ptr<Sprite>>& temp);
	void LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>>& temp);
	void LoadSounds(const TCHAR dataFileName[100]);
	
	void TitleScene(HDC hdc, HBITMAP & screen);
	void SelectScene(HDC hdc, HBITMAP & screen);
	void PlayScene(HDC hdc, HBITMAP & screen);
	void EndingScene(HDC hdc, HBITMAP & screen);

	void Gravity(int g);
	void ShowTimer(HDC hdc, vector<shared_ptr<Animation>>& timerAni);
	void CheckKeyInput();
	void CheckKeyRelease(WPARAM wParam);
	void ShowPlayerLife(const Charactor & player);
	void ShowPlayerHPbar(const Charactor & player);
	void ShowBossHPbar(const Charactor & Boss);
	void ShowPlayerStateUI(const Charactor & player);
	void ShowPlayerPoints(const Charactor & player);
	void MoveNextStage();
	void SlowMotion();
	void GameOver(); // Rank 포함
};

