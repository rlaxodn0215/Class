#include "Animation.h"

int FindNum(int& i, char chbuff[])
{
	int temp = 0;

	while (chbuff[i] != '\n')
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

Animation::Animation(shared_ptr<Sprite> resource, const TCHAR textFileName[100])//���� ��������� ���� �ڵ����� �޾Ƽ� ����
{
	m_ResourceSprite = resource;

	DWORD rbytes;

	HANDLE hFile = CreateFile(textFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);

	if (hFile == NULL)
	{
		MessageBox(NULL, _T("������ ���� �ε� ����"), _T("����"), MB_OK);
	}

	int transparentColor;

	TCHAR buff[1000] = {};
	char chbuff[1000] = {};
	size_t convertedChars = 0;

	
	ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);

	//�ؽ�Ʈ ���� �����ϸ� �ȵ�
	if (buff[0] == 65279)
	{
		SetFilePointer(hFile, 2, NULL, FILE_BEGIN);
		ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);
	}

#ifdef UNICODE
		wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
#else
		strcpy_s(charStr, sizeof(charStr), tcharStr); // �̹� ��Ƽ����Ʈ ���ڿ��� ���
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
		if (resource->GetTransparentColor() == NULL)
			resource->SetTransparentColor((COLORREF)FindNum(i, chbuff));
		else
			FindNum(i, chbuff);
	}

	CloseHandle(hFile);

}

Animation::~Animation()
{

}

void Animation::AniPlay(HDC hdc, POINT location, int spriteIndex, float imageRatio)
{
	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_ResourceSprite->GetSpriteImage());

	int bx = m_Width[spriteIndex];
	int by = m_Height[spriteIndex];
	int xStart = m_Offset[spriteIndex].x;
	int yStart = m_Offset[spriteIndex].y;
	int posX = location.x - (int)(m_Pivot[spriteIndex].x * imageRatio);
	int posY = location.y - (int)(m_Pivot[spriteIndex].y * imageRatio);

	TransparentBlt(hdc, posX, posY, (int)(bx * imageRatio), (int)(by * imageRatio), hMemDC, xStart, yStart, bx, by, m_ResourceSprite->GetTransparentColor());//m_ResourceSprite->GetTransparentColor()

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);
}