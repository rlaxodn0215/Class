#pragma once
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
#include"Charactor.h"
#include"SingletonTemplate.h"
#include"Sound.h"

struct PlayerData // 플레이어들의 랭킹 저장 구조체
{
	string name = "";
	int score = 0;

	bool operator<(const PlayerData & other)
	{
		return (score > other.score);
	}
};

class GameManager : public SingletonTemplate<GameManager> // 씬, 키 입력, 플레이 영역, UI, Ranking 관리
{
private:
	friend SingletonTemplate; //friend 키워드: SingletonTemplate이 GameManager class의 모든 멤버를 사용할 수 있다
	GameManager();
	~GameManager();

public:
	int m_SceneNum = 0; // 씬 번호 : 0. title / 1. select / 2. play / 3. ending

	void(GameManager:: * m_Scene)(HWND,HDC,HBITMAP&,RECT);		// 해당 씬을 함수 포인터로 선언하여 화면에 출력
	shared_ptr<Stage>  m_Stage;									// 스테이지 관련 포인터
	shared_ptr< Player> m_Player;								// 플레이어 연결 포인터

	//SelectScene
	POINT m_Cursor = { 50,150 };			// select에서 커서의 처음 위치
	int m_SelectPosX[4] = { 50,290,530,765 }; // 커서의 위치값 지정
	bool m_SelectFlag = false;				// 선택 유뮤 판단

	//PlayScene
	bool m_KeyFlag[6] = {};			//0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_ComboFlag[6] = {};		//콤보용 플래그
	bool m_PlayerDynamite = false;	// 플레이어가 필살기를 쓰는지 확인
	int m_TimerFrame = 0;			// 타이머 값 저장
	int m_SelectTimer = 20*10;		//선택 타이머
	int m_ComboTimerCount = 0;		// 콤보 사용시 이용하는 타이머

	//Ending Scene
	bool m_FirstPush = true;			// 첫 선택 확인 ('_' 체크용)
	bool m_ShowLetter[3];				// 글사 선택시 보여주는 영역 확인
	int m_NameCursor = 0;				// 이름 정할 때 정하는 위치
	int m_NameCount = 0;				// 알파벳 선택용 카운트		
	char m_Name[3] = {'A','A','A'};		// 저장할 이름

	PlayerData m_PlayerData;			// 현재 플레이어 데이터
	vector<PlayerData> m_RankingDatas;	// 랭킹 텍스트에 있는 플레이어 데이터들
	
	void TitleScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void SelectScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void PlayScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);
	void EndingScene(HWND hWnd, HDC hdc, HBITMAP & screen, RECT winRect);

	void Gravity(int g);
	void ShowBackStage(HDC hdc, RECT winRect);
	void ShowTimer(HDC hdc, vector<shared_ptr<Animation>>& timerAni, RECT winRect);

	void CheckKeyInput(HDC hdc, RECT winRect);
	void CheckKeyRelease(WPARAM wParam);

	void ShowUI(HDC hdc, RECT winRect);
	void ShowPlayerHP(HDC hdc, shared_ptr<Animation> hpBar, POINT offset_location, float imageRatioWidth, float imageRatioHeight, float hpRatio);
	void ShowPlayerPoints(HDC hdc, POINT offset_location, float imageRatioWidth, float imageRatioHeight,const int points, int distance);
	void MakeName(HDC hdc,RECT winRect);
	void MakeRanking(const TCHAR rankFileName[100]);
	void ShowRanking(HDC hdc, RECT winRect);
};

