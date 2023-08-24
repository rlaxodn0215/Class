#pragma once
#include<list>
#include<queue>
#include<map>
#include"Charactor.h"
#include"Sound.h"
#include"Sprite.h"
#include"Animation.h"
#include"SingletonTemplate.h"

struct Wave
{
	int Timer;
	int MaxMonsterNum;
	bool StageFinish = false;
	vector<RECT> SpawnArea;
	POINT LimitArea;
	list<shared_ptr<Monster>> LiveMonsters; // ����ִ� ���͵�
	queue<shared_ptr<Monster>> DeadMonsters; // ���� ���͵�
};

class DataManager : public SingletonTemplate<DataManager> // �ش� ���� �ʿ��� �����͸� �ε��Ѵ�.
{
private:
	friend SingletonTemplate;
	DataManager();
	~DataManager();

public:
	vector<shared_ptr<Animation>> m_Number_ani; // ���� �̹��� ������ ����
	vector<shared_ptr<Animation>> m_Alpha_ani;  // ���ĺ� �̹��� ������ ����

	//���� �ʿ��� ������ ����
	map<string, shared_ptr<Sprite>> m_Sprites;
	map<string, shared_ptr<Animation>> m_Animations;
	map<string, shared_ptr<Sound>> m_Sounds;

	void GetSentence(int& i, char* buff, char* sentence);			// �ؽ�Ʈ ���� �� ���� �б�
	void LoadSprites(const TCHAR dataFileName[100]);				// ��������Ʈ �ε�
	void LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>>& temp);			// �ִϸ��̼� �ε�
	void LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd);		// ���� �ε�

	void LoadPlayerDatas(HWND hWnd, shared_ptr<Player> player);
	void LoadSceneDatas(int SceneNum, HWND hWnd);
	void LoadWaveDatas(HWND hWnd, RECT winRect, shared_ptr<Wave> wave);
	
};

