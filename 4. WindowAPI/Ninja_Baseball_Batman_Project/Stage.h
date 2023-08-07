#pragma once
#include"framework.h"
#include"Charactor.h"
#include"Animation.h"
#include"Sound.h"
#include<vector>
#include<map>
#include<memory>

using namespace std;

class Stage:public Sprite //�����ͷ� Stage �޸� �Ҵ��ϰ�, �ٲ� ������ ������ �ٲٱ� 
{
private:
	int m_StageNum;
	Sprite * m_StageArea; //sprite ����
	vector<RECT> m_LimitArea;
	vector<shared_ptr<Charactor>> m_Monsters;
	map<string, shared_ptr<Sound>> m_BGMs;
	map<string, shared_ptr<Animation>> m_MonstersAni;
	map<string, shared_ptr<Animation>> m_UIAni;
	bool m_isFinish;

public:
	Stage() {};
	Stage(int stageNum, Sprite * stageArea, vector<RECT> & limitArea, vector<shared_ptr<Charactor>>& monsters,
		map<string, shared_ptr<Sound>> & BGM, map<string, shared_ptr<Animation>> & monstersAni,
		map<string, shared_ptr<Animation>> & uiAni, bool isFinish);
	~Stage();
	int GetStageNum() { return m_StageNum; }
	Sprite *GetStageArea() { return m_StageArea; }
	void SetFinish(bool f) { m_isFinish = f; }
	void ShowUIStage(HWND hWnd, HDC hdc, int timerDefine, int delayTime, TIMERPROC func);
};

