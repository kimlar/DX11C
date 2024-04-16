#include "SwapChain.h"

// Create Swap Chain
bool d3d11_swap_chain_create(ID3D11Device1* d3d11Device, HWND hWnd, IDXGISwapChain1** d3d11SwapChain)
{
	// Get DXGI Factory (needed to create Swap Chain)
	IDXGIFactory2* dxgiFactory = NULL;
	{
		IDXGIDevice1* dxgiDevice = NULL;
		HRESULT hResult = ID3D11Device1_QueryInterface(d3d11Device, &IID_IDXGIDevice1, (void**)&dxgiDevice);
		assert(SUCCEEDED(hResult));

		IDXGIAdapter* dxgiAdapter = NULL;
		hResult = IDXGIDevice1_GetAdapter(dxgiDevice, &dxgiAdapter);
		assert(SUCCEEDED(hResult));
		IDXGIDevice1_Release(dxgiDevice);

		DXGI_ADAPTER_DESC adapterDesc;
		IDXGIAdapter_GetDesc(dxgiAdapter, &adapterDesc);

		OutputDebugStringA("Graphics Device: ");
		OutputDebugStringW(adapterDesc.Description);

		hResult = IDXGIAdapter_GetParent(dxgiAdapter, &IID_IDXGIFactory2, (void**)&dxgiFactory);
		assert(SUCCEEDED(hResult));
		IDXGIAdapter_Release(dxgiAdapter);
	}

	DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = { 0 };
	d3d11SwapChainDesc.Width = 0; // use window width
	d3d11SwapChainDesc.Height = 0; // use window height
	d3d11SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	d3d11SwapChainDesc.SampleDesc.Count = 1;
	d3d11SwapChainDesc.SampleDesc.Quality = 0;
	d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	d3d11SwapChainDesc.BufferCount = 2;
	d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	d3d11SwapChainDesc.Flags = 0;

	HRESULT hResult = IDXGIFactory2_CreateSwapChainForHwnd(dxgiFactory, (IUnknown*)d3d11Device, hWnd, &d3d11SwapChainDesc, 0, 0, d3d11SwapChain);
	assert(SUCCEEDED(hResult));
	IDXGIFactory2_Release(dxgiFactory);

	return true;
}
