#include "Animation.h"

Animation::Animation()
{
	m_FrameCurCount = 0;
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
	m_FrameCurCount = 0;

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
	m_FrameTotalCount = temp;
	
	for (int j = 0; j < frameCount; j++)
	{
		Sprite tempAni = Sprite::Sprite(imageName, textFileName,hFile, i, chbuff);
		m_Sprites.push_back(tempAni);
	}

	CloseHandle(hFile);

}

Animation::~Animation()
{
	
}

void Animation::AniPlay(HWND hWnd, HDC hdc, POINT location,int spriteIndex, float imageRatio, int timerDefine, int delayTime, TIMERPROC func)
{
	SetTimer(hWnd, timerDefine, delayTime, func);

	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_Sprites[spriteIndex].GetAniImage());

	int bx = m_Sprites[spriteIndex].GetWidth();
	int by = m_Sprites[spriteIndex].GetHeight();
	int xStart = m_Sprites[spriteIndex].GetOffset().x;
	int yStart = m_Sprites[spriteIndex].GetOffset().y;
	int posX = location.x - m_Sprites[spriteIndex].GetPivot().x * imageRatio;
	int posY = location.y - m_Sprites[spriteIndex].GetPivot().y * imageRatio;

	TransparentBlt(hdc, posX, posY, bx * imageRatio, by * imageRatio, hMemDC, xStart, yStart, bx, by, m_Sprites[spriteIndex].GetTransparentColor());

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);

}