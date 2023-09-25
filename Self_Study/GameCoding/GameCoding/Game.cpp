#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

	//TODO
	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

void Game::Update()
{
}

void Game::Render()
{
	RenderBegin();

	// TODO
	//IA - VS - RS - PS - OM
	{

	}


	RenderEnd();
}

void Game::RenderBegin()
{
	// 도화지 넘기기
	_deviceContext->OMSetRenderTargets(1,_renderTaegetView.GetAddressOf(),nullptr);
	// 도화지 색을 초기화
	_deviceContext->ClearRenderTargetView(_renderTaegetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewPort);
}

void Game::RenderEnd()
{
	HRESULT hr =  _swapChain->Present(1, 0); //화면에 출력
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;			
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//최종 결과물을 그리는 용도
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr =  ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);
	
	CHECK(hr);
}

void Game::CreateRenderTargetView()
{
	HRESULT hr;
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	_device->CreateRenderTargetView(backBuffer.Get(),nullptr, _renderTaegetView.GetAddressOf());
	CHECK(hr);
}

void Game::SetViewport()
{
	_viewPort.TopLeftX = 0.f; // 0 ~ 1
	_viewPort.TopLeftY = 0.f;
	_viewPort.Width = static_cast<float>(_width);
	_viewPort.Height = static_cast<float>(_height);
	_viewPort.MinDepth = 0.f;
	_viewPort.MaxDepth = 1.f;
}
