#pragma once
#include "framework.h"
#include<list>
#include"Charactor.h"
class Stage //�÷��� ���������� ���� ��������(�÷��� ����, ���� ��, �� ��ġ ��)
{
private:
	RECT m_PlayArea; // �� ������������ �÷��� �ϴ� Sprite ����
	vector<RECT> m_LimitAreas; // �÷��̾ ���� �� �� ���� Sprite ������
	list<Charactor> m_StageMonsters; // ���������� �����ϴ� ���͵�
	bool m_StageFinish;

public:
	Stage() = default;
	//Stage();
	~Stage() = default;
};

