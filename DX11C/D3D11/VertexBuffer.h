#pragma once
#include "Core.h"

bool d3d11_vertex_buffer_create(ID3D11Device1* d3d11Device, float* vertexData, unsigned int vertexDataSize, enum D3D11_USAGE usage, ID3D11Buffer** vertexBuffer);
