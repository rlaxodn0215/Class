#pragma once
#include"framework.h"
#include"Charactor.h"
#include"Animation.h"
#include"Sound.h"
#include<vector>
#include<memory>
#include<map>

using namespace std;

class Stage //포인터로 Stage 메모리 할당하고, 바뀔 때마다 포인터 바꾸기 / 각 스테이지에 필요한 데이터만 저장
{
private:
	int m_StageNum;
	Animation * m_StageArea; //sprite 기준
	vector<RECT> m_LimitArea;
	map<string, shared_ptr<Sound>> m_BGM;
	map<string, shared_ptr<Animation>> m_UI;
	map<string, shared_ptr<Animation>> m_Background;
	vector<Charactor> m_StageCharactors;

public:
	Stage() {};
	Stage(int stageNum, Animation * stageArea, vector<RECT> limitArea, map<string, shared_ptr<Sound>> bgm,
		map<string, shared_ptr<Animation>> ui, map<string, shared_ptr<Animation>> background, vector<Charactor> stageCharactors);
	~Stage();
	int GetStageNum() { return m_StageNum; }
	Animation *GetStageArea() { return m_StageArea; }
	vector<RECT> GetLimitArea() { return m_LimitArea; }
	map<string, shared_ptr<Sound>> GetBGM() { return m_BGM; }
	map<string, shared_ptr<Animation>> GetUI() { return m_UI; }
	map<string, shared_ptr<Animation>> GetBackground() { return m_Background; }
	vector<Charactor> GetStageCharactor() { return m_StageCharactors; }

};

