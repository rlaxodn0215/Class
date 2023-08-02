#include"framework.h"
#include "cMainGame.h"

cMainGame::cMainGame() 
	: m_hBitmap(NULL)
	,m_vEye(0,0,-5)
	,m_vLookAt(0,0,0)
	,m_vUp(0,1,0)
	,m_vPosition(0,0,0)
	,m_fBoxRotY(0.0f)
{
}

cMainGame::~cMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::SetUp()
{
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);

	//RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	ReleaseDC(g_hWnd, hdc);

	// vertex
	//near
	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

	//rear
	m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
	m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));


	//index -> 법선 벡터 고려
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);
	
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);


	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}

void cMainGame::Update()
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY += -0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}

	//RECT rc;
	//GetClientRect(g_hWnd, &rc);

	m_vLookAt = cVector3(0.0f, 0.0f, 0.0f);
	m_vEye = cVector3(0.0f, 5.0f, -5.0f);

	cMatrix matR = cMatrix::RotationY(m_fBoxRotY);

	m_matWorld =  cMatrix::Translation(m_vPosition)* matR;
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f, (float)rc.right / rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom,0,1);
}

void cMainGame::Render(HDC hdc)
{
	//RECT rc;
	//GetClientRect(g_hWnd, &rc);
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom,WHITENESS);

	cMatrix matWVP = m_matWorld * m_matView * m_matProj;

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		// to do something

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		//래스터라이징
		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v3.x, v3.y);
		LineTo(m_MemDC, v1.x, v1.y);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);

}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		break;
	}
}
