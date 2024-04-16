#pragma once
#include "Core.h"

bool d3d11_input_layout_create(ID3D11Device1* d3d11Device, ID3D11InputLayout** inputLayout, const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int numElements, ID3DBlob* vsBlob);
