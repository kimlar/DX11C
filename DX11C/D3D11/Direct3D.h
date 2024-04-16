#pragma once
#include "Core.h"
#include "../Window/Window.h"
#include "../Camera/Camera.h"

static ID3D11Device1* d3d11Device = NULL;
static ID3D11DeviceContext1* d3d11DeviceContext = NULL;
static IDXGISwapChain1* d3d11SwapChain = NULL;
static ID3D11RenderTargetView* d3d11FrameBufferView = NULL;
static ID3D11DepthStencilView* d3d11DepthStencilView = NULL;
//static ID3D11Texture2D* d3d11DepthStencilBuffer = NULL;


//static bool direct3d_create(ID3D11Device1** d3d11Device, ID3D11DeviceContext1** d3d11DeviceContext, IDXGISwapChain1** d3d11SwapChain, ID3D11RenderTargetView** d3d11FrameBufferView)
static bool direct3d_create()
{
	// Create D3D11 Device and Device Context
	if (!d3d11_device_create(&d3d11Device, &d3d11DeviceContext))
	{
		return false; // Failure
	}
	assert(d3d11Device != NULL);
	assert(d3d11DeviceContext != NULL);



#ifdef _DEBUG
	// Set up debug layer to break on D3D11 errors
	if (!d3d11_debug_layer_init(d3d11Device))
	{
		return false; // Failure
	}
#endif



	// Create Swap Chain
	if (!d3d11_swap_chain_create(d3d11Device, hwnd, &d3d11SwapChain))
	{
		return false; // Failure
	}
	assert(d3d11SwapChain != NULL);




	// Create Framebuffer Render Target
	if (!d3d11_frame_buffer_create(d3d11Device, d3d11SwapChain, &d3d11FrameBufferView))
	{
		return false; // Failure
	}
	assert(d3d11FrameBufferView != NULL);




	// Create Depth Stencil Buffer
	//if (!d3d11_depth_stencil_view_create(d3d11Device, &d3d11DepthStencilBuffer, &d3d11DepthStencilView))
	if (!d3d11_depth_stencil_view_create(d3d11Device, &d3d11DepthStencilView))
	{
		return false; // Failure
	}
	//assert(d3d11DepthStencilBuffer != NULL);
	assert(d3d11DepthStencilView != NULL);


	return true; // Success
}



static void direct3d_did_resize()
{
	if (global_windowDidResize)
	{
		if (d3d11SwapChain)
		{
			ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext,0, 0, 0);

			// Release all outstanding references to the swap chain's buffers.
			ID3D11RenderTargetView_Release(d3d11FrameBufferView);
			ID3D11DepthStencilView_Release(d3d11DepthStencilView);

			HRESULT hr;
			// Preserve the existing buffer count and format.
			// Automatically choose the width and height to match the client rect for HWNDs.
			hr = IDXGISwapChain1_ResizeBuffers(d3d11SwapChain, 0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
			assert(SUCCEEDED(hr));
			if (FAILED(hr))
			{
				exit(1);
			}

			if (!d3d11_frame_buffer_create(d3d11Device, d3d11SwapChain, &d3d11FrameBufferView))
			{
				exit(1);
			}

			if (!d3d11_depth_stencil_view_create(d3d11Device, &d3d11DepthStencilView))
			{
				exit(1);
			}

			ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

			// Set up the viewport.
			D3D11_VIEWPORT vp;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;
			vp.Width = (float)windowWidth; //width;
			vp.Height = (float)windowHeight; //height;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			ID3D11DeviceContext1_RSSetViewports(d3d11DeviceContext, 1, &vp);

			perspectiveMat = makePerspectiveMat(windowAspectRatio, degreesToRadians(60), 0.1f, 1000.f);
		}

		global_windowDidResize = false;
	}
}

static void direct3d_pre_render()
{
	FLOAT backgroundColor[4] = { 0.39f, 0.58f, 0.93f, 1.0f };
	ID3D11DeviceContext1_ClearRenderTargetView(d3d11DeviceContext, d3d11FrameBufferView, backgroundColor);
	ID3D11DeviceContext1_ClearDepthStencilView(d3d11DeviceContext, d3d11DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)windowWidth, (FLOAT)windowHeight, 0.0f, 1.0f };
	ID3D11DeviceContext1_RSSetViewports(d3d11DeviceContext, 1, &viewport);
}

static void direct3d_post_render()
{
	IDXGISwapChain1_Present(d3d11SwapChain, 1, 0);
}
