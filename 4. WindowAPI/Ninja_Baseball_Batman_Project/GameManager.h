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

class GameManager : public SingletonTemplate<GameManager> // ��, Ű �Է�, �÷��� ����, UI ����
{
private:
	friend SingletonTemplate; //friend Ű����: SingletonTemplate�� GameManager class�� ��� ����� ����� �� �ִ�
	GameManager();
	~GameManager();

public:
	int m_SceneNum = 0; // �� ��ȣ : 0. title / 1. select / 2. play / 3. ending
	bool m_Start = true; // �ʱ�ȭ �Լ��� (void Start())

	void(GameManager::* m_Scene)(HWND, HDC, DataManager*);		// �ش� ���� �Լ� �����ͷ� �����Ͽ� ȭ�鿡 ���
	shared_ptr<Wave>  m_Wave;									// ���̺� ���� ������
	shared_ptr<Player> m_Player;								// �÷��̾� ���� ������

	RECT m_WinRect;

	//Title Scene
	int totalFrame = 0;
	int curFrame = 0;

	//Select Scene
	POINT m_Cursor = { 50,150 };				// select���� Ŀ���� ó�� ��ġ
	int m_SelectPosX[4] = { 50,290,530,765 };	// Ŀ���� ��ġ�� ����
	bool m_SelectFlag = false;					// ���� ���� �Ǵ�
	int m_SelectNum = 0;

	//Play Scene
	RECT m_PlayArea;				// �÷��� ����
	bool m_KeyFlag[6] = {};			// 0: UP, 1: DOWN, 2: LEFT, 3: RIGHT, 4: ATTACK, 5: JUMP
	bool m_ComboFlag[6] = {};		//�޺��� �÷���
	bool m_PlayerDynamite = false;	// �÷��̾ �ʻ�⸦ ������ Ȯ��
	int m_TimerFrame = 0;			// Ÿ�̸� �� ����
	int m_SelectTimer = 201;		// ���� Ÿ�̸�
	int m_ComboTimerCount = 0;		// �޺� ���� �̿��ϴ� Ÿ�̸�

	//Ending Scene
	bool m_FirstPush = true;			// ù ���� Ȯ�� ('_' üũ��)
	bool m_ShowLetter[3];				// �ۻ� ���ý� �����ִ� ���� Ȯ��
	int m_NameCursor = 0;				// �̸� ���� �� ���ϴ� ��ġ
	int m_NameCount = 0;				// ���ĺ� ���ÿ� ī��Ʈ		
	char m_Name[4] = { 'A','A','A','\0' };		// ������ �̸�

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

