#pragma once
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
#include"Charactor.h"
#include"Stage.h"
#include"SingletonTemplate.h"
#include"Sound.h"

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

	vector<shared_ptr<Animation>> Number_ani;
	int m_SceneNum = 0;

	void(GameManager:: * m_Scene)(HWND,HDC,HBITMAP&,RECT);
	shared_ptr<Stage>  m_Stage;
	shared_ptr< Player> m_Player;

	POINT m_Cursor = { 50,150 }; //(50,150), +220
	int m_SelectPosX[4] = {50,290,530,765};
	bool m_SelectFlag = false;

	bool m_KeyFlag[6] = {}; //0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_ComboFlag[6] = {}; 
	bool m_PlayerDynamite = false;

	int m_TimerFrame = 0;
	int m_SelectTimer = 20*10;
	int m_ComboTimerCount = 0;

	void GetSentence(int& i, char* buff, char* sentence);
	void LoadSprites(const TCHAR dataFileName[100], map<string, shared_ptr<Sprite>>& temp);
	void LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>>& temp);
	void LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd);
	
	void TitleScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void SelectScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void PlayScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void LoadStage(HWND hWnd, int stageNum, RECT winRect);
	void EndingScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);

	void Gravity(int g);
	void ShowBackStage(HDC hdc, RECT winRect);
	void ShowTimer(HDC hdc, vector<shared_ptr<Animation>>& timerAni, RECT winRect);
	void CheckKeyInput(HDC hdc, RECT winRect);
	void CheckKeyRelease(WPARAM wParam);
	void ShowUI(HDC hdc, RECT winRect);
	void ShowPlayerHP(HDC hdc, shared_ptr<Animation> hpBar, POINT offset_location, float imageRatioWidth, float imageRatioHeight, float hpRatio);
	void ShowPlayerPoints(HDC hdc, POINT offset_location, float imageRatioWidth, float imageRatioHeight,const int points);
	void GameOver();
};

