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
	int MaxMonsterNum;
	int TimeInterval;
	bool StageFinish = false;
	vector<POINT> SpawnArea;
	POINT LimitArea;

	vector<shared_ptr<Monster>> WaveMonsters;
	list<shared_ptr<Monster>> LiveMonsters; // ����ִ� ���͵�
	queue<shared_ptr<Monster>> DeadMonsters; // ���� ���͵�
};

struct PlayerData // �÷��̾���� ��ŷ ���� ����ü
{
	char name[4] = "";
	int score = 0;

	bool operator<(const PlayerData& other)
	{
		return (score > other.score);
	}
};

class DataManager : public SingletonTemplate<DataManager> // �ش� ���� �ʿ��� �����͸� �ε��Ѵ�.
{
private:
	friend SingletonTemplate;
	DataManager();
	~DataManager();
	int m_ChannelIndex = 1;

public:
	vector<shared_ptr<Animation>> m_Number_ani; // ���� �̹��� ������ ����
	vector<shared_ptr<Animation>> m_Alpha_ani;  // ���ĺ� �̹��� ������ ����

	//���� �ʿ��� ������ ����
	map<string, shared_ptr<Sprite>> m_Sprites;
	map<string, shared_ptr<Animation>> m_Animations;
	map<string, shared_ptr<Sound>> m_Sounds;

	//��ŷ ������ ����
	PlayerData m_PlayerData;			// ���� �÷��̾� ������
	vector<PlayerData> m_RankingDatas;	// ��ŷ �ؽ�Ʈ�� �ִ� �÷��̾� �����͵�

	void GetSentence(int& i, char* buff, char* sentence);			// �ؽ�Ʈ ���� �� ���� �б�
	void LoadSprites(const TCHAR dataFileName[100]);				// ��������Ʈ �ε�
	void LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>>& temp, bool isReference);			// �ִϸ��̼� �ε�
	void LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd, bool isReference);		// ���� �ε�

	void LoadPlayerDatas(HWND hWnd, shared_ptr<Player>& player);
	void LoadSceneDatas(int SceneNum, HWND hWnd);
	void LoadWaveDatas(HWND hWnd, RECT winRect, shared_ptr<Wave>& wave);
	void MakeRanking(const TCHAR rankFileName[100]);

};

