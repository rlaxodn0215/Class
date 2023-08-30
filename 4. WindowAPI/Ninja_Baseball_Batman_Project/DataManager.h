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
	list<shared_ptr<Monster>> LiveMonsters; // 살아있는 몬스터들
	queue<shared_ptr<Monster>> DeadMonsters; // 죽은 몬스터들
};

struct PlayerData // 플레이어들의 랭킹 저장 구조체
{
	char name[4] = "";
	int score = 0;

	bool operator<(const PlayerData& other)
	{
		return (score > other.score);
	}
};

class DataManager : public SingletonTemplate<DataManager> // 해당 씬에 필요한 데이터를 로드한다.
{
private:
	friend SingletonTemplate;
	DataManager();
	~DataManager();
	int m_ChannelIndex = 1;

public:
	vector<shared_ptr<Animation>> m_Number_ani; // 숫자 이미지 데이터 저장
	vector<shared_ptr<Animation>> m_Alpha_ani;  // 알파벳 이미지 데이터 저장

	//씬에 필요한 데이터 저장
	map<string, shared_ptr<Sprite>> m_Sprites;
	map<string, shared_ptr<Animation>> m_Animations;
	map<string, shared_ptr<Sound>> m_Sounds;

	//랭킹 데이터 저장
	PlayerData m_PlayerData;			// 현재 플레이어 데이터
	vector<PlayerData> m_RankingDatas;	// 랭킹 텍스트에 있는 플레이어 데이터들

	void GetSentence(int& i, char* buff, char* sentence);			// 텍스트 파일 한 영역 읽기
	void LoadSprites(const TCHAR dataFileName[100]);				// 스프라이트 로드
	void LoadAnimations(const TCHAR dataFileName[100], map<string, shared_ptr<Animation>>& temp, bool isReference);			// 애니메이션 로드
	void LoadSounds(const TCHAR dataFileName[100], map<string, shared_ptr<Sound>>& temp, HWND hWnd, bool isReference);		// 사운드 로드

	void LoadPlayerDatas(HWND hWnd, shared_ptr<Player>& player);
	void LoadSceneDatas(int SceneNum, HWND hWnd);
	void LoadWaveDatas(HWND hWnd, RECT winRect, shared_ptr<Wave>& wave);
	void MakeRanking(const TCHAR rankFileName[100]);

};

