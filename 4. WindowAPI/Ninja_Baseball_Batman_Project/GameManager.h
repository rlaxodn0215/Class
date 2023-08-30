#pragma once
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
#include"Charactor.h"
#include"DataManager.h"
#include"SingletonTemplate.h"
#include"Sound.h"
#include"Data_Names.h"

class GameManager : public SingletonTemplate<GameManager> // 씬, 키 입력, 플레이 영역, UI 관리
{
private:
	friend SingletonTemplate; //friend 키워드: SingletonTemplate이 GameManager class의 모든 멤버를 사용할 수 있다
	GameManager();
	~GameManager();

public:
	int m_SceneNum = 0; // 씬 번호 : 0. title / 1. select / 2. play / 3. ending
	bool m_Start = true; // 초기화 함수용 (void Start())

	void(GameManager::* m_Scene)(HWND, HDC, DataManager*);		// 해당 씬을 함수 포인터로 선언하여 화면에 출력
	shared_ptr<Wave>  m_Wave;									// 웨이브 관련 포인터
	shared_ptr<Player> m_Player;								// 플레이어 연결 포인터

	RECT m_WinRect;

	//Title Scene
	int totalFrame = 0;
	int curFrame = 0;

	//Select Scene
	POINT m_Cursor = { 50,150 };				// select에서 커서의 처음 위치
	int m_SelectPosX[4] = { 50,290,530,765 };	// 커서의 위치값 지정
	bool m_SelectFlag = false;					// 선택 유뮤 판단
	int m_SelectNum = 0;

	//Play Scene
	RECT m_PlayArea;				// 플레이 영역
	bool m_KeyFlag[6] = {};			// 0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_ComboFlag[6] = {};		//콤보용 플래그
	bool m_PlayerDynamite = false;	// 플레이어가 필살기를 쓰는지 확인
	int m_TimerFrame = 0;			// 타이머 값 저장
	int m_SelectTimer = 201;		// 선택 타이머
	int m_ComboTimerCount = 0;		// 콤보 사용시 이용하는 타이머

	//Ending Scene
	bool m_FirstPush = true;			// 첫 선택 확인 ('_' 체크용)
	bool m_ShowLetter[3];				// 글사 선택시 보여주는 영역 확인
	int m_NameCursor = 0;				// 이름 정할 때 정하는 위치
	int m_NameCount = 0;				// 알파벳 선택용 카운트		
	char m_Name[4] = { 'A','A','A','\0' };		// 저장할 이름

	void Gravity(int g);

	void TitleScene(HWND hWnd, HDC hdc, DataManager* dataManager);
	void SelectScene(HWND hWnd, HDC hdc, DataManager* dataManager);
	void PlayScene(HWND hWnd, HDC hdc, DataManager* dataManager);
	void EndingScene(HWND hWnd, HDC hdc, DataManager* dataManager);

	void ShowBackStage(HDC hdc, DataManager* dataManager);
	void ShowTimer(HDC hdc, vector<shared_ptr<Animation>>& timerAni);
	void ShowUI(HDC hdc, DataManager* dataManager);
	void ShowPlayerHP(HDC hdc, shared_ptr<Animation> hpBar, POINT offset_location, float imageRatioWidth, float imageRatioHeight, float hpRatio);
	void ShowPlayerPoints(HDC hdc, POINT offset_location, DataManager* dataManager, float imageRatioWidth, float imageRatioHeight, const int points, int distance);
	void MoveLetter(HDC hdc, int nameCursor, bool firstPush, DataManager* dataManager);
	void ShowLetter(HDC hdc, DataManager* dataManager);
	void ShowRanking(HDC hdc, DataManager* dataManager);

	void CharactorUpdate(HDC hdc, int Timer);
	void MonsterUpdate(HDC hdc);
	void TriggerCheck(HDC hdc);
	void MonsterInstantiate(int timeInterval, int timer);
	void RenderingCharactor(HDC hdc, int Timer);
	static bool RenderingOrder(const shared_ptr<Charactor>& a, const shared_ptr<Charactor>& b)
	{
		return (a->GetPos().m_Z < b->GetPos().m_Z);
	}

	void CheckKeyInput(HWND hWnd, HDC hdc, DataManager* dataManager);
	void CheckKeyRelease(HWND hWnd, WPARAM wParam, DataManager* dataManager);

	void MakeName(HDC hdc, DataManager* dataManager);
};

