#pragma once
#include"Sound.h"
#include<map>
#include<string>
#include<memory>
#include"SingletonTemplate.h"

using namespace std;

class SoundManager : public SingletonTemplate<SoundManager> // ���� ä�� ����
{
private:
	friend SingletonTemplate;
	SoundManager();
	~SoundManager();

public:
	


	
};

