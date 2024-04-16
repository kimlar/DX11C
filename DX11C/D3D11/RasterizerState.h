#pragma once
#include "Core.h"

bool d3d11_rasterizer_state_create(ID3D11Device1* d3d11Device, ID3D11RasterizerState** rasterizerState, bool culling);
bool d3d11_rasterizer_state_wireframe_create(ID3D11Device1* d3d11Device, ID3D11RasterizerState** rasterizerState, bool culling);
