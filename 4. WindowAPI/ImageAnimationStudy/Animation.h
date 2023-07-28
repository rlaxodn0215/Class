#pragma once
#include "framework.h"
#include<string>

#pragma comment(lib, "msimg32.lib")

using namespace std;

class Animation
{
private:
	HBITMAP _aniSprite;
	BITMAP _aniBit;
	int _bitWidth, _bitHeight;
	int _startPoint, _endPoint;
	int _frameCount;

public:
	Animation(const TCHAR * name)
	{
		_aniSprite = (HBITMAP)LoadImage(NULL, name,
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (_aniSprite == NULL)
		{
			DWORD dwError = GetLastError();
			MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
		}

		GetObject(_aniSprite, sizeof(BITMAP), &_aniBit);
	}


};

