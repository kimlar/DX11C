#pragma once
#include "Core.h"
#include "../Math/gpu_math.h"

// Create Constant Buffer
typedef struct Constants
{
	float4x4 modelViewProj;
} Constants;

bool d3d11_constant_buffer_create(ID3D11Device1* d3d11Device, ID3D11Buffer** constantBuffer);
