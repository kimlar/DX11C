#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>

#include <assert.h>
#include <stdbool.h>

#define COBJMACROS
#include <d3d11_1.h>
#pragma comment(lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

// -------------------------------------------------------------------------------------------------------

#ifdef _DEBUG
#include "DebugLayer.h"
#endif

#include "Device.h"
#include "SwapChain.h"
#include "FrameBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "VertexBuffer.h"
#include "SamplerState.h"
#include "ShaderResourceView.h"
#include "ConstantBuffer.h"
#include "RasterizerState.h"
#include "DepthStencilView.h"

// -------------------------------------------------------------------------------------------------------
