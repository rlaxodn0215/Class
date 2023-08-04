#pragma once
#include"framework.h"
#include"Charactor.h"
#include"UI.h"
#include"Sound.h"
#include<vector>
#include<map>

using namespace std;

class Stage //포인터로 Stage 메모리 할당하고, 바뀔 때마다 포인터 바꾸기 
{
private:
	int m_StageNum;
	RECT m_StageArea; //sprite 기준
	vector<RECT> m_LimitArea;
	vector<Charactor> m_Monsters;
	map<string, Sound> m_BGMs;

	map<string, UI> m_UIs;//시작 stage, 선택 stage (고정적인 data 관련 UI)
	bool m_isFinish;

public:
	Stage();
	Stage(int stageNum, RECT stageArea, RECT limitArea, vector<Charactor>& monsters, vector<UI> & m_UIs, bool isFinish);
	~Stage() {};
	int GetStageNum() { return m_StageNum; }
	RECT GetStageArea() { return m_StageArea; }
	void SetFinish(bool f) { m_isFinish = f; }
	void PlayBGM();
	BOOL StageStart();
	BOOL StageEnd();
};

