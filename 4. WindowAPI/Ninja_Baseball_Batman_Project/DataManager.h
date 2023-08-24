#pragma once
#include<map>
#include"Sound.h"
#include"Sprite.h"
#include"Animation.h"

class DataManager
{
private:
	map<string, shared_ptr<Sprite>> Sprites;
	map<string, shared_ptr<Animation>> Animations;
	map<string, shared_ptr<Sound>> Sounds;

	vector<shared_ptr<Animation>> Number_ani; // ���� �̹��� ������ ����
	vector<shared_ptr<Animation>> Alpha_ani;  // ���ĺ� �̹��� ������ ����

public:
};

