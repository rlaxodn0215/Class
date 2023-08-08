#pragma once
#include<map>
#include<string>
#include"Camera.h"
#include"Charactor.h"
#include"Stage.h"
#include"SingletonTemplate.h"

class GameManager : public SingletonTemplate<GameManager> //싱글턴으로 만든다.
{
private:
	friend SingletonTemplate; //friend 키워드: SingletonTemplate이 GameManager class의 모든 멤버를 사용할 수 있다
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
	void GameOver(); // Rank 포함
};

