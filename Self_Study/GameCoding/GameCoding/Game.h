#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();
private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32  _height = 0;

private:
	// DX

	//컴 객체는 ComPtr GPU종류와 상관 없이 DX 작업 가능하게 함, 하나의 인터페이스
	ComPtr<ID3D11Device> _device = nullptr;						// 유닛 생성
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;		// 유닛 명령
	ComPtr<IDXGISwapChain> _swapChain = nullptr;				// 더블 버퍼링과 비슷

	// Render Target View
	ComPtr<ID3D11RenderTargetView> _renderTaegetView; // 후면 버퍼에 그려달라는 것을 요청

	// Misc
	D3D11_VIEWPORT _viewPort = { 0 };
	float _clearColor[4] = { 1.f,0.5f,0.5f, 0.5f }; //RGBA
};

