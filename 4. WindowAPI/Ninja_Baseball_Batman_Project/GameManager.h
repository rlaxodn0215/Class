#pragma once
#include<map>
#include<string>
#include"Camera.h"
#include"Charactor.h"
#include"Stage.h"
#include"SingletonTemplate.h"

class GameManager : public SingletonTemplate<GameManager> //�̱������� �����.
{
private:
	friend SingletonTemplate; //friend Ű����: SingletonTemplate�� GameManager class�� ��� ����� ����� �� �ִ�
	GameManager();
	~GameManager();

public:
	Stage* m_CurStage;
	Player* m_Player;
	Camera* m_Cam;

	void SetInstance(Stage* curStage, Player* player, Camera* cam);
	void ShowPlayerLife(const Charactor & player);
	void ShowPlayerHPbar(const Charactor& player);
	void ShowBossHPbar(const Charactor& Boss);
	void ShowPlayerStateUI(const Charactor& player);
	void ShowPlayerPoints(const Charactor& player);
	void MoveNextStage();
	void SlowMotion();
	void GameOver(); // Rank ����
};

