#pragma once
#include<map>
#include<string>
#include<iostream>
#include<algorithm>
#include"Charactor.h"
#include"SingletonTemplate.h"
#include"Sound.h"

struct PlayerData // �÷��̾���� ��ŷ ���� ����ü
{
	string name = "";
	int score = 0;

	bool operator<(const PlayerData & other)
	{
		return (score > other.score);
	}
};

class GameManager : public SingletonTemplate<GameManager> // ��, Ű �Է�, �÷��� ����, UI, Ranking ����
{
private:
	friend SingletonTemplate; //friend Ű����: SingletonTemplate�� GameManager class�� ��� ����� ����� �� �ִ�
	GameManager();
	~GameManager();

public:
	int m_SceneNum = 0; // �� ��ȣ : 0. title / 1. select / 2. play / 3. ending

	void(GameManager:: * m_Scene)(HWND,HDC,HBITMAP&,RECT);		// �ش� ���� �Լ� �����ͷ� �����Ͽ� ȭ�鿡 ���
	shared_ptr<Stage>  m_Stage;									// �������� ���� ������
	shared_ptr< Player> m_Player;								// �÷��̾� ���� ������

	//SelectScene
	POINT m_Cursor = { 50,150 };			// select���� Ŀ���� ó�� ��ġ
	int m_SelectPosX[4] = { 50,290,530,765 }; // Ŀ���� ��ġ�� ����
	bool m_SelectFlag = false;				// ���� ���� �Ǵ�

	//PlayScene
	bool m_KeyFlag[6] = {};			//0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_ComboFlag[6] = {};		//�޺��� �÷���
	bool m_PlayerDynamite = false;	// �÷��̾ �ʻ�⸦ ������ Ȯ��
	int m_TimerFrame = 0;			// Ÿ�̸� �� ����
	int m_SelectTimer = 20*10;		//���� Ÿ�̸�
	int m_ComboTimerCount = 0;		// �޺� ���� �̿��ϴ� Ÿ�̸�

	//Ending Scene
	bool m_FirstPush = true;			// ù ���� Ȯ�� ('_' üũ��)
	bool m_ShowLetter[3];				// �ۻ� ���ý� �����ִ� ���� Ȯ��
	int m_NameCursor = 0;				// �̸� ���� �� ���ϴ� ��ġ
	int m_NameCount = 0;				// ���ĺ� ���ÿ� ī��Ʈ		
	char m_Name[3] = {'A','A','A'};		// ������ �̸�

	PlayerData m_PlayerData;			// ���� �÷��̾� ������
	vector<PlayerData> m_RankingDatas;	// ��ŷ �ؽ�Ʈ�� �ִ� �÷��̾� �����͵�
	
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

