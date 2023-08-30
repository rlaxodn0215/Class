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

Animation::Animation(shared_ptr<Sprite> resource, const TCHAR textFileName[100])//���� ��������� ���� �ڵ����� �޾Ƽ� ����
{
	m_ResourceSprite = resource;

	DWORD rbytes;

	HANDLE hFile = CreateFile(textFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);

	if (hFile == NULL)
	{
		MessageBox(NULL, _T("Animation ������ ���� �ε� ����"), _T("����"), MB_OK);
	}

	TCHAR buff[1000] = {};
	char chbuff[1000] = {};
	size_t convertedChars = 0;

	if (ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL))
	{
		if (buff[0] == 0xFEFF)
		{
			_LARGE_INTEGER temp;
			temp.QuadPart = 2;
			if (SetFilePointerEx(hFile, temp, NULL, FILE_BEGIN))
				ReadFile(hFile, buff, sizeof(buff), &rbytes, NULL);
			else
			{
				MessageBox(NULL, _T("Animation ������ ���� Ŀ�� �̵� ����"), _T("����"), MB_OK);
				CloseHandle(hFile);
				return;
			}
		}
	}

	else
	{
		MessageBox(NULL, _T("Animation ������ ���� �б� ����"), _T("����"), MB_OK);
		CloseHandle(hFile);
		return;
	}

#ifdef UNICODE
	wcstombs_s(&convertedChars, chbuff, sizeof(chbuff), buff, _TRUNCATE); // �����ڵ带 ��Ƽ����Ʈ�� ��ȯ
#else
	strcpy_s(charStr, sizeof(charStr), tcharStr); // �̹� ��Ƽ����Ʈ ���ڿ��� ���
#endif

	int i = 0;
	m_FrameTotalCount = FindNum(i, chbuff);

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

void Animation::AniPlay(HDC hdc, POINT offset_location, int spriteIndex, float imageRatioWidth, float imageRatioHeight, bool lookRight, RECT winRect)
{
	int bx = m_Width[spriteIndex];
	int by = m_Height[spriteIndex];
	int xStart = m_Offset[spriteIndex].x;
	int yStart = m_Offset[spriteIndex].y;
	int posX = offset_location.x - m_Pivot[spriteIndex].x;
	int posY = offset_location.y - m_Pivot[spriteIndex].y;

	HDC hMemDC;
	HBITMAP holdBitmap;

	hMemDC = CreateCompatibleDC(hdc);
	holdBitmap = (HBITMAP)SelectObject(hMemDC, m_ResourceSprite->GetSpriteImage());

	TransparentBlt(hdc, posX, posY, (int)(bx * imageRatioWidth), (int)(by * imageRatioHeight), hMemDC, xStart, yStart,
		bx, by, RGB(m_ResourceSprite->GetTransparentColor().m_X, m_ResourceSprite->GetTransparentColor().m_Y,
			m_ResourceSprite->GetTransparentColor().m_Z));

	SelectObject(hMemDC, holdBitmap);
	DeleteDC(hMemDC);

}