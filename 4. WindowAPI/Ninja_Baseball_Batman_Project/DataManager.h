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
	list<shared_ptr<Monster>> m_LiveMonsters; // 살아있는 몬스터들
	queue<shared_ptr<Monster>> m_DeadMonsters; // 죽은 몬스터들
	bool m_StageFinish = false;
};

class DataManager : public SingletonTemplate<DataManager> // 해당 씬에 필요한 데이터를 로드한다.
{
private:
	friend SingletonTemplate;
	DataManager();
	~DataManager();

public:
	vector<shared_ptr<Animation>> m_Number_ani; // 숫자 이미지 데이터 저장
	vector<shared_ptr<Animation>> m_Alpha_ani;  // 알파벳 이미지 데이터 저장

	//씬에 필요한 데이터 저장
	map<string, shared_ptr<Sprite>> m_Sprites;
	map<string, shared_ptr<Animation>> m_Animations;
	map<string, shared_ptr<Sound>> m_Sounds;

	shared_ptr<Wave> m_Wave; // 한 Wave에 필요한 데이터들

	void GetSentence(int& i, char* buff, char* sentence);			// 텍스트 파일 한 영역 읽기
	void LoadSprites(const TCHAR dataFileName[100]);				// 스프라이트 로드
	void LoadAnimations(const TCHAR dataFileName[100]);				// 애니메이션 로드
	void LoadSounds(const TCHAR dataFileName[100],HWND hWnd);		// 사운드 로드

	void LoadSceneDatas(int SceneNum, HWND hWnd);
	void LoadWaveDatas(int WaveNum, HWND hWnd);
};

