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

	vector<shared_ptr<Animation>> Number_ani; // 숫자 이미지 데이터 저장
	vector<shared_ptr<Animation>> Alpha_ani;  // 알파벳 이미지 데이터 저장

public:
};

