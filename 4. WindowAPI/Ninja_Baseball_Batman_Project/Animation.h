#pragma once
#include"Sprite.h"
#include"Camera.h"
#include<vector>

using namespace std;

class Animation
{
private:
	shared_ptr<Sprite> m_ResourceSprite;
	vector<POINT> m_Offset;
	vector<POINT> m_Pivot;
	vector<int> m_Width;
	vector<int> m_Height;
	int m_FrameTotalCount;

public:
	int GetFrameTotalCount() { return m_FrameTotalCount; }
	vector<int> GetWidths() { return m_Width; }
	vector<int> GetHeights() { return m_Height; }
	shared_ptr<Sprite> GetResourceSprite() { return m_ResourceSprite; }
	
	Animation();
	Animation(shared_ptr<Sprite> resource, const TCHAR textFileName[100]);
	~Animation();
	POINT SpriteToAni();
	void AniPlay(HDC hdc, POINT location, int spriteIndex, float imageRatio, bool lookRight, RECT winRect);
};

