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
	list<shared_ptr<Monster>> m_LiveMonsters; // ����ִ� ���͵�
	queue<shared_ptr<Monster>> m_DeadMonsters; // ���� ���͵�
	bool m_StageFinish = false;
};

class DataManager : public SingletonTemplate<DataManager> // �ش� ���� �ʿ��� �����͸� �ε��Ѵ�.
{
private:
	friend SingletonTemplate;
	DataManager();
	~DataManager();

public:
	vector<shared_ptr<Animation>> m_Number_ani; // ���� �̹��� ������ ����
	vector<shared_ptr<Animation>> m_Alpha_ani;  // ���ĺ� �̹��� ������ ����

	//���� �ʿ��� ������ ����
	map<string, shared_ptr<Sprite>> m_Sprites;
	map<string, shared_ptr<Animation>> m_Animations;
	map<string, shared_ptr<Sound>> m_Sounds;

	shared_ptr<Wave> m_Wave; // �� Wave�� �ʿ��� �����͵�

	void GetSentence(int& i, char* buff, char* sentence);			// �ؽ�Ʈ ���� �� ���� �б�
	void LoadSprites(const TCHAR dataFileName[100]);				// ��������Ʈ �ε�
	void LoadAnimations(const TCHAR dataFileName[100]);				// �ִϸ��̼� �ε�
	void LoadSounds(const TCHAR dataFileName[100],HWND hWnd);		// ���� �ε�

	void LoadSceneDatas(int SceneNum, HWND hWnd);
	void LoadWaveDatas(int WaveNum, HWND hWnd);
};

