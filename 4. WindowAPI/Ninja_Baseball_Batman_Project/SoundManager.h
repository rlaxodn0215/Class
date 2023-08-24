#pragma once
#include"Sound.h"
#include"SingletonTemplate.h"
class SoundManager : public SingletonTemplate<SoundManager>
{
private:
	friend SingletonTemplate;
	SoundManager();
	~SoundManager();
public:
};

