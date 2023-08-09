#include "Sprite.h"

Sprite::Sprite()
{
	m_SpriteImage = NULL;
	m_SpriteBit;
	m_TransparentColor = RGB(0, 0, 0);
}

Sprite::Sprite(const TCHAR imageName[100])
{
	m_SpriteImage = (HBITMAP)LoadImage(NULL, imageName,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_SpriteImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
	}

	GetObject(m_SpriteImage, sizeof(BITMAP), &m_SpriteBit);
}



