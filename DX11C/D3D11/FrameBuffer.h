#pragma once
#include "Core.h"

bool d3d11_frame_buffer_create(ID3D11Device1* d3d11Device, IDXGISwapChain1* d3d11SwapChain, ID3D11RenderTargetView** d3d11FrameBufferView);
