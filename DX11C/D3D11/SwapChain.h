#pragma once
#include "Core.h"

bool d3d11_swap_chain_create(ID3D11Device1* d3d11Device, HWND hWnd, IDXGISwapChain1** d3d11SwapChain);
