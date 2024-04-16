#include "ConstantBuffer.h"

// Create Constant Buffer
bool d3d11_constant_buffer_create(ID3D11Device1* d3d11Device, ID3D11Buffer** constantBuffer)
{
	D3D11_BUFFER_DESC constantBufferDesc = { 0 };
	// ByteWidth must be a multiple of 16, per the docs
	constantBufferDesc.ByteWidth = sizeof(Constants) + 0xf & 0xfffffff0;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	HRESULT hResult = ID3D11Device1_CreateBuffer(d3d11Device, &constantBufferDesc, NULL, constantBuffer);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
