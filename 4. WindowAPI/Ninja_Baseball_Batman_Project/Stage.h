#pragma once
#include"framework.h"
#include"Charactor.h"
#include"Animation.h"
#include"Sound.h"
#include<vector>
#include<memory>
#include<map>

using namespace std;

class Stage //�����ͷ� Stage �޸� �Ҵ��ϰ�, �ٲ� ������ ������ �ٲٱ� / �� ���������� �ʿ��� �����͸� ����
{
private:
	int m_StageNum;
	Animation * m_StageArea; //sprite ����
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

