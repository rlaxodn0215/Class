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

	//�� ��ü�� ComPtr GPU������ ��� ���� DX �۾� �����ϰ� ��, �ϳ��� �������̽�
	ComPtr<ID3D11Device> _device = nullptr;						// ���� ����
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;		// ���� ���
	ComPtr<IDXGISwapChain> _swapChain = nullptr;				// ���� ���۸��� ���

	// Render Target View
	ComPtr<ID3D11RenderTargetView> _renderTaegetView; // �ĸ� ���ۿ� �׷��޶�� ���� ��û

	// Misc
	D3D11_VIEWPORT _viewPort = { 0 };
	float _clearColor[4] = { 1.f,0.5f,0.5f, 0.5f }; //RGBA
};

