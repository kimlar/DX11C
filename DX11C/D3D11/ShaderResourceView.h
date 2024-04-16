#pragma once
#include "Core.h"

bool d3d11_shader_resource_view_create(ID3D11Device1* d3d11Device, const char* fileName, ID3D11ShaderResourceView** shaderResourceView);
