#include "SamplerState.h"

// Create Sampler State
bool d3d11_sampler_state_create(ID3D11Device1* d3d11Device, ID3D11SamplerState** samplerState)
{
	D3D11_SAMPLER_DESC samplerDesc = { 0 };
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP; //D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP; //D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP; //D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0] = 1.0f;
	samplerDesc.BorderColor[1] = 1.0f;
	samplerDesc.BorderColor[2] = 1.0f;
	samplerDesc.BorderColor[3] = 1.0f;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;





	HRESULT hResult = ID3D11Device_CreateSamplerState(d3d11Device, &samplerDesc, samplerState);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
