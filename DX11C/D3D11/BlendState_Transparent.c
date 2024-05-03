#include "BlendState_Transparent.h"

bool d3d11_blend_state_transparent_create(ID3D11Device1* d3d11Device, ID3D11DeviceContext1* d3d11DeviceContext, ID3D11BlendState** blendState)
{
	D3D11_BLEND_DESC blendStateDesc = { 0 };
	blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	HRESULT hResult = ID3D11Device1_CreateBlendState(d3d11Device, &blendStateDesc, blendState);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}


	float blendColor[4];
	blendColor[0] = 0.0f;
	blendColor[1] = 0.0f;
	blendColor[2] = 0.0f;
	blendColor[3] = 0.0f;
	ID3D11DeviceContext1_OMSetBlendState(d3d11DeviceContext, *blendState, blendColor, 0xffffffff);

	return true; // Success
}
