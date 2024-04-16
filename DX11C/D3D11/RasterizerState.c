#include "RasterizerState.h"

// Create Rasterizer State
bool d3d11_rasterizer_state_create(ID3D11Device1* d3d11Device, ID3D11RasterizerState** rasterizerState, bool culling)
{
	D3D11_RASTERIZER_DESC rasterizerDesc = { 0 };
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	if (culling)
	{
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
	}
	else
	{
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
	}
	rasterizerDesc.FrontCounterClockwise = TRUE;

	HRESULT hResult = ID3D11Device1_CreateRasterizerState(d3d11Device, &rasterizerDesc, rasterizerState);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}

// Create Rasterizer State with wire frame (instead of filled frame)
bool d3d11_rasterizer_state_wireframe_create(ID3D11Device1* d3d11Device, ID3D11RasterizerState** rasterizerState, bool culling)
{
	D3D11_RASTERIZER_DESC rasterizerDesc = { 0 };
	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	if (culling)
	{
		rasterizerDesc.CullMode = D3D11_CULL_BACK;
	}
	else
	{
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
	}
	rasterizerDesc.FrontCounterClockwise = TRUE;

	HRESULT hResult = ID3D11Device1_CreateRasterizerState(d3d11Device, &rasterizerDesc, rasterizerState);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
