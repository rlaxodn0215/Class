#pragma once
#include"framework.h"
#include"Charactor.h"
#include"UI.h"
#include"Sound.h"
#include<vector>
#include<map>

using namespace std;

class Stage //�����ͷ� Stage �޸� �Ҵ��ϰ�, �ٲ� ������ ������ �ٲٱ� 
{
private:
	int m_StageNum;
	RECT m_StageArea; //sprite ����
	vector<RECT> m_LimitArea;
	vector<Charactor> m_Monsters;
	map<string, Sound> m_BGMs;

	map<string, UI> m_UIs;//���� stage, ���� stage (�������� data ���� UI)
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

