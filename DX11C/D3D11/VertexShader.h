#pragma once
#include "Core.h"

bool d3d11_vertex_shader_create(ID3D11Device1* d3d11Device, WCHAR* vsFileName, ID3D11VertexShader** vertexShader, ID3DBlob** vsBlob);
