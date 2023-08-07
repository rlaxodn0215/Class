#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(const TCHAR imageName[100], const TCHAR textFileName[100])//파일 입출력으로 정보 자동으로 받아서 저장
{
	DWORD rbytes;

	HANDLE hFile = CreateFile(textFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);

	if (hFile == NULL)
	{
		MessageBox(NULL, _T("데이터 파일 로드 에러"), _T("에러"), MB_OK);
	}

	int frameCount;
	int transparentColor;

	TCHAR buff[100] = {};
	char chbuff[100] = {};
	size_t convertedChars = 0;

	SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
	ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);

#ifdef UNICODE
		wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // 유니코드를 멀티바이트로 변환
#else
		strcpy_s(charStr, sizeof(charStr), tcharStr); // 이미 멀티바이트 문자열인 경우
#endif

	int i = 0;
	int temp = 0;
	while (chbuff[i] != '\n')
	{
		temp = 10 * temp + (chbuff[i] - '0');
		i++;
	}
	i++;
	frameCount = temp;
	temp = 0;
	CloseHandle(hFile);
	
	for (int j = 0; j < frameCount; j++)
	{
		Sprite tempAni = Sprite::Sprite(imageName, textFileName,i);
		m_Sprites.push_back(tempAni);
	}

	
}

Animation::~Animation()
{
	
}

void Animation::AniPlay(HWND hWnd, HDC hdc, POINT location, int spriteIndex)
{

	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_Sprites[spriteIndex].GetAniImage());

	int bx = m_Sprites[spriteIndex].GetWidth();
	int by = m_Sprites[spriteIndex].GetHeight();
	int xStart = m_Sprites[spriteIndex].GetOffset().x;
	int yStart = m_Sprites[spriteIndex].GetOffset().y;
	int posX = location.x - m_Sprites[spriteIndex].GetPivot().x;
	int posY = location.y - m_Sprites[spriteIndex].GetPivot().y;

	TransparentBlt(hdc, posX, posY, bx, by, hMemDC, xStart, yStart, bx, by, m_Sprites[spriteIndex].GetTransparentColor());

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);

}