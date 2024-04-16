#include "InputLayout.h"

// Create Input Layout
bool d3d11_input_layout_create(ID3D11Device1* d3d11Device, ID3D11InputLayout** inputLayout, const D3D11_INPUT_ELEMENT_DESC* inputElementDesc, int numElements, ID3DBlob* vsBlob)
{
	HRESULT hResult = ID3D11Device_CreateInputLayout(d3d11Device, inputElementDesc, numElements, ID3D10Blob_GetBufferPointer(vsBlob), ID3D10Blob_GetBufferSize(vsBlob), inputLayout);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
