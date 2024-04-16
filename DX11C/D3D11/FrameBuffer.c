#include "FrameBuffer.h"

// Create Framebuffer Render Target
bool d3d11_frame_buffer_create(ID3D11Device1* d3d11Device, IDXGISwapChain1* d3d11SwapChain, ID3D11RenderTargetView** d3d11FrameBufferView)
{
	ID3D11Texture2D* d3d11FrameBuffer = NULL;
	HRESULT hResult = IDXGISwapChain1_GetBuffer(d3d11SwapChain, 0, &IID_ID3D11Texture2D, (void**)&d3d11FrameBuffer);
	assert(SUCCEEDED(hResult));

	hResult = ID3D11Device1_CreateRenderTargetView(d3d11Device, (ID3D11Resource*)d3d11FrameBuffer, NULL, d3d11FrameBufferView);
	assert(SUCCEEDED(hResult));
	ID3D11Texture2D_Release(d3d11FrameBuffer);

	return true; // Success
}
