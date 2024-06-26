#pragma once
#include "../D3D11/Core.h"
#include "../Math/gpu_math.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"
//#include "../D3D11/BlendState_Transparent.h"

ID3D11VertexShader* transparent_quad_vertexShader = NULL;
ID3D11PixelShader* transparent_quad_pixelShader = NULL;
ID3D11InputLayout* transparent_quad_inputLayout = NULL;
ID3D11Buffer* transparent_quad_vertexBuffer = NULL;
unsigned int transparent_quad_stride = 0;
unsigned int transparent_quad_numVerts = 0;
unsigned int transparent_quad_offset = 0;
ID3D11SamplerState* transparent_quad_samplerState = NULL;
ID3D11ShaderResourceView* transparent_quad_textureView = NULL;
ID3D11Buffer* transparent_quad_constantBuffer = NULL;
ID3D11RasterizerState* transparent_quad_rasterizerState = NULL;
float3 transparent_quad_position = { 0.0f, 0.0f, 0.0f };
ID3D11BlendState* transparent_quad_blendState = NULL;


static bool transparent_quad_create()
{
	// Create Vertex Shader
	//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/transparent_vs.hlsl", &transparent_quad_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(transparent_quad_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/transparent_ps.hlsl", &transparent_quad_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(transparent_quad_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &transparent_quad_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(transparent_quad_inputLayout != NULL);




	// Clean up shader blobs
	ID3D10Blob_Release(vsBlob);
	ID3D10Blob_Release(psBlob);






	// Create Vertex Buffer
	//ID3D11Buffer* vertexBuffer = NULL;
	//unsigned int stride = 0;
	//unsigned int numVerts = 0;
	//unsigned int offset = 0;
	{
		float vertexData[] = { // x, y, z, u, v
			-0.5f,  1.f, 0.0f,     0.0f, 0.0f,
			0.5f, 0.0f, 0.0f,      1.0f, 1.0f,
			-0.5f, 0.0f, 0.0f,     0.0f, 1.0f,
			-0.5f,  1.0f, 0.0f,     0.0f, 0.0f,
			0.5f,  1.0f, 0.0f,      1.0f, 0.0f,
			0.5f, 0.0f, 0.0f,      1.0f, 1.0f
		};
		transparent_quad_stride = 5 * sizeof(float);
		transparent_quad_numVerts = sizeof(vertexData) / transparent_quad_stride;
		transparent_quad_offset = 0;
		unsigned int size_in_bytes = sizeof(vertexData);
		float* myVertexData = malloc(size_in_bytes);
		if (myVertexData == NULL)
		{
			return false; // Failure
		}
		memcpy(myVertexData, vertexData, size_in_bytes);
		if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DEFAULT, &transparent_quad_vertexBuffer))
		{
			return false; // Failure
		}
		free(myVertexData);
		myVertexData = NULL;
	}
	assert(transparent_quad_vertexBuffer != NULL);



	// Place the spinning quad into the world
	transparent_quad_position = (float3){ 0.0f, 0.0f, 1.0f };


	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &transparent_quad_samplerState))
	{
		return false; // Failure
	}
	assert(transparent_quad_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create_rgba(d3d11Device, "Data/Textures/General/transparent_red_x.rgba", &transparent_quad_textureView))
	{
		return false; // Failure
	}
	assert(transparent_quad_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &transparent_quad_constantBuffer))
	{
		return false; // Failure
	}
	assert(transparent_quad_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	//if (!d3d11_rasterizer_state_create(d3d11Device, &rasterizerState))
	if (!d3d11_rasterizer_state_create(d3d11Device, &transparent_quad_rasterizerState, false))
	{
		return false; // Failure
	}
	assert(transparent_quad_rasterizerState != NULL);




	// Create Blend State
	if (!d3d11_blend_state_transparent_create(d3d11Device, d3d11DeviceContext, &transparent_quad_blendState))
	{
		return false; // Failure
	}
	assert(transparent_quad_blendState != NULL);


	return true; // Success
}

//static void transparent_quad_update(ID3D11DeviceContext1* d3d11DeviceContext, ID3D11Buffer* constantBuffer)
static void transparent_quad_update()
{
	// Spin the quad
	float4x4 modelMat = rotateYMat(0.2f * (float)(M_PI * currentTimeInSeconds));
	modelMat = translationMatPtr(transparent_quad_position, &modelMat);


	// Calculate model-view-projection matrix to send to shader
	float4x4 modelViewProj = mul44x3(modelMat, viewMat, perspectiveMat);

	// Update constant buffer (Upload to GPU constant buffer)
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)transparent_quad_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->modelViewProj = modelViewProj;
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)transparent_quad_constantBuffer, 0);
}

static void transparent_quad_pipeline()
{
	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, transparent_quad_rasterizerState);

	//ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, NULL);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, transparent_quad_inputLayout);

	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, transparent_quad_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, transparent_quad_pixelShader, NULL, 0);

	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &transparent_quad_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &transparent_quad_samplerState);

	ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &transparent_quad_constantBuffer);

	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &transparent_quad_vertexBuffer, &transparent_quad_stride, &transparent_quad_offset);
}

//static void transparent_quad_render(ID3D11DeviceContext1* d3d11DeviceContext, unsigned int numVerts, unsigned int startVertex)
static void transparent_quad_render()
{
	unsigned int startVertex = 0;
	ID3D11DeviceContext1_Draw(d3d11DeviceContext, transparent_quad_numVerts, startVertex);
}
