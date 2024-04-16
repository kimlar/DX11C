#include "DepthStencilView.h"
#include "../Window/Window.h"

//bool d3d11_depth_stencil_view_create(ID3D11Device1* d3d11Device, ID3D11Texture2D** d3d11DepthStencilBuffer, ID3D11DepthStencilView** d3d11DepthStencilView)
bool d3d11_depth_stencil_view_create(ID3D11Device1* d3d11Device, ID3D11DepthStencilView** d3d11DepthStencilView)
{
	D3D11_TEXTURE2D_DESC d3d11DepthStencilBufferDesc = { 0 };
	d3d11DepthStencilBufferDesc.Width = windowWidth;
	d3d11DepthStencilBufferDesc.Height = windowHeight;
	d3d11DepthStencilBufferDesc.MipLevels = 1;
	d3d11DepthStencilBufferDesc.ArraySize = 1;
	d3d11DepthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3d11DepthStencilBufferDesc.SampleDesc.Count = 1;
	d3d11DepthStencilBufferDesc.SampleDesc.Quality = 0;
	d3d11DepthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	d3d11DepthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	d3d11DepthStencilBufferDesc.CPUAccessFlags = 0;
	d3d11DepthStencilBufferDesc.MiscFlags = 0;

	ID3D11Texture2D* d3d11DepthStencilBuffer = NULL;
	HRESULT hResult = ID3D11Device1_CreateTexture2D(d3d11Device, &d3d11DepthStencilBufferDesc, NULL, &d3d11DepthStencilBuffer);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC d3d11DepthStencilViewDesc = { 0 };
	d3d11DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3d11DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	d3d11DepthStencilViewDesc.Texture2D.MipSlice = 0;

	hResult = ID3D11Device1_CreateDepthStencilView(d3d11Device, (ID3D11Resource*)d3d11DepthStencilBuffer, &d3d11DepthStencilViewDesc, d3d11DepthStencilView);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}
	ID3D11Texture2D_Release(d3d11DepthStencilBuffer);

	return true; // Success
}
