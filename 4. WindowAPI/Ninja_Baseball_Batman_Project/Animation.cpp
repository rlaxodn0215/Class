#include "Animation.h"

int FindNum(int& i, char chbuff[])
{
	int temp = 0;

	while (chbuff[i] != '\n' && chbuff[i] != '\0')
	{
		temp = 10 * temp + (chbuff[i] - '0');
		i++;
	}
	i++;

	return temp;
}

Animation::Animation()
{
	m_ResourceSprite = NULL;
}

Animation::Animation(shared_ptr<Sprite> resource, const TCHAR textFileName[100])//파일 입출력으로 정보 자동으로 받아서 저장
{
	m_ResourceSprite = resource;

	DWORD rbytes;

	HANDLE hFile = CreateFile(textFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);

	if (hFile == NULL)
	{
		MessageBox(NULL, _T("데이터 파일 로드 에러"), _T("에러"), MB_OK);
	}


	TCHAR buff[1000] = {};
	char chbuff[1000] = {};
	size_t convertedChars = 0;

	
	ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);

	//텍스트 직접 수정하면 안됨
	if (buff[0] == 65279)
	{
		SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
		ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);
	}

#ifdef UNICODE
		wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // 유니코드를 멀티바이트로 변환
#else
		strcpy_s(charStr, sizeof(charStr), tcharStr); // 이미 멀티바이트 문자열인 경우
#endif

	int i = 0;
	m_FrameTotalCount = FindNum(i,chbuff);

	for (int j = 0; j < m_FrameTotalCount; j++)
	{
		FindNum(i, chbuff);
		m_Offset.push_back({ FindNum(i, chbuff),FindNum(i, chbuff) });
		m_Width.push_back(FindNum(i, chbuff));
		m_Height.push_back(FindNum(i, chbuff));
		m_Pivot.push_back({ FindNum(i, chbuff) , FindNum(i, chbuff) });

		Vector3 temp = { -1, -1,-1 };
		if (resource->GetTransparentColor() == temp)
		{
			Vector3 vec;
			vec.m_X = FindNum(i, chbuff);
			vec.m_Y = FindNum(i, chbuff);
			vec.m_Z = FindNum(i, chbuff);
			resource->SetTransparentColor(vec);
		}
		else
		{
			FindNum(i, chbuff);
			FindNum(i, chbuff);
			FindNum(i, chbuff);
		}
	}

	CloseHandle(hFile);

}

Animation::~Animation()
{

}

void Animation::AniPlay(HDC hdc, POINT offset_location, int spriteIndex, float imageRatio)
{
	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_ResourceSprite->GetSpriteImage());

	int bx = m_Width[spriteIndex];
	int by = m_Height[spriteIndex];
	int xStart = m_Offset[spriteIndex].x;
	int yStart = m_Offset[spriteIndex].y;
	int posX = offset_location.x;
	int posY = offset_location.y;

	TransparentBlt(hdc, posX, posY, (int)(bx * imageRatio), (int)(by * imageRatio), hMemDC, xStart, yStart,
		bx, by, RGB(m_ResourceSprite->GetTransparentColor().m_X, m_ResourceSprite->GetTransparentColor().m_Y,
			m_ResourceSprite->GetTransparentColor().m_Z));//m_ResourceSprite->GetTransparentColor()

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);
}