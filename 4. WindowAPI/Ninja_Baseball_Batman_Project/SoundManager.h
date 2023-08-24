#pragma once
#include"Sound.h"
#include<map>
#include<string>
#include<memory>
#include"SingletonTemplate.h"

using namespace std;

class SoundManager : public SingletonTemplate<SoundManager> // 사운드 채널 관리
{
private:
	friend SingletonTemplate;
	SoundManager();
	~SoundManager();

public:
	


	
};

