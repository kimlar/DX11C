#pragma once
#include "Core.h"

bool d3d11_pixel_shader_create(ID3D11Device1* d3d11Device, WCHAR* psFileName, ID3D11PixelShader** pixelShader, ID3DBlob** psBlob);
