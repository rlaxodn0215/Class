#include "Sprite.h"

Sprite::Sprite()
{
	m_AniImage = NULL;
	m_Offset = {0,0};
	m_Pivot = {0,0};
	m_Width = 0;
	m_Height = 0;
	m_TransparentColor = RGB(0, 0, 0);
}

Sprite::Sprite(const TCHAR imageName[100],const TCHAR textFileName[100], HANDLE hFile, int & readIndexNum, char chbuff[]) //파일 입출력으로 정보 자동으로 받아서 저장
{
	m_AniImage = (HBITMAP)LoadImage(NULL, imageName,
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (m_AniImage == NULL)
	{
		DWORD dwError = GetLastError();
		MessageBox(NULL, _T("이미지 로드 에러"), _T("에러"), MB_OK);
	}

	GetObject(m_AniImage, sizeof(BITMAP), &m_AniBit);

	if (hFile == NULL)
	{
		MessageBox(NULL, _T("데이터 파일 로드 에러"), _T("에러"), MB_OK);
	}

	int i = readIndexNum;
	int temp = 0;

	int tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Offset.x = tempNum;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Offset.y = tempNum;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Width = tempNum;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Height = tempNum;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Pivot.x = tempNum;

	tempNum = 0;
	while (chbuff[i] != '\n')
	{
		tempNum = 10 * tempNum + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_Pivot.y = tempNum;

	while (chbuff[i] != '\n')
	{
		temp = 10 * temp + (chbuff[i] - '0');
		i++;
	}
	i++;
	m_TransparentColor = temp;

	readIndexNum = i;

}

void Sprite::ShowSprite(HDC hdc, POINT location)
{
	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_AniImage);

	int bx = m_Width;
	int by = m_Height;
	int xStart = m_Offset.x;
	int yStart = m_Offset.y;
	int posX = location.x - m_Pivot.x;
	int posY = location.y - m_Pivot.y;

	TransparentBlt(hdc, posX, posY, bx, by, hMemDC, xStart, yStart, bx, by, m_TransparentColor);

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);
}

