#pragma once
#include"framework.h"
#include"Charactor.h"
#include"Animation.h"
#include"Sound.h"
#include<vector>
#include<map>

using namespace std;

class Stage //�����ͷ� Stage �޸� �Ҵ��ϰ�, �ٲ� ������ ������ �ٲٱ� / �� ���������� �ʿ��� �����͸� ����
{
private:
	int m_StageNum;
	Animation m_StageArea; //sprite ����
	vector<RECT> m_LimitArea;
	map<string, Sound*> m_BGM;
	map<string, Animation*> m_UI;
	map<string, Animation*> m_Background;
	vector<Charactor> m_StageMonsters;
	bool m_isFinish;

public:
	Stage() {};
	Stage(int stageNum, Animation stageArea, vector<RECT> & limitArea, map<string, Sound*> & bgm,
		map<string, Animation*> & ui, map<string, Animation*> & background, vector<Charactor> & stageMonsters);
	~Stage();
	int GetStageNum() { return m_StageNum; }
	Animation GetStageArea() { return m_StageArea; }
	void SetFinish(bool f) { m_isFinish = f; }
};

