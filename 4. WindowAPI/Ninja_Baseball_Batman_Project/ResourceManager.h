#pragma once
#include"framework.h"
#include<map>
#include"Sprite.h"
#include"Animation.h"
#include"Sound.h"
#include"SingletonTemplate.h"

class ResourceManager:public SingletonTemplate<ResourceManager>
{
private:
	friend SingletonTemplate; 
	ResourceManager();
	~ResourceManager();

public:
	map<string, shared_ptr<Sprite>> Sprites;
	map<string, shared_ptr<Animation>> Animations;
	map<string, shared_ptr<Sound>> Sounds;

	vector<shared_ptr<Animation>> Timer_ani;

};

