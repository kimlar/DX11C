#pragma once
#include "../D3D11/Core.h"
#include "../Math/gpu_math.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"

ID3D11VertexShader* wooden_box_vertexShader = NULL;
ID3D11PixelShader* wooden_box_pixelShader = NULL;
ID3D11InputLayout* wooden_box_inputLayout = NULL;
ID3D11Buffer* wooden_box_vertexBuffer = NULL;
unsigned int wooden_box_stride = 0;
unsigned int wooden_box_numVerts = 0;
unsigned int wooden_box_offset = 0;
ID3D11SamplerState* wooden_box_samplerState = NULL;
ID3D11ShaderResourceView* wooden_box_textureView = NULL;
ID3D11Buffer* wooden_box_constantBuffer = NULL;
ID3D11RasterizerState* wooden_box_rasterizerState = NULL;
float3 wooden_box_position = { 0.0f, 0.0f, 0.0f };

static bool wooden_box_create()
{
	// Create Vertex Shader
	//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/wooden_box_shader_vs.hlsl", &wooden_box_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(wooden_box_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/wooden_box_shader_ps.hlsl", &wooden_box_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(wooden_box_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &wooden_box_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(wooden_box_inputLayout != NULL);




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
			// Front
			-1.0f,  -1.0f, 1.0f,     0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
			-1.0f,  -1.0f, 1.0f,     0.0f, 0.0f,
			1.0f,  -1.0f, 1.0f,      1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
			// Back
			-1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			1.0f, -1.0f, -1.0f,      1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,
			-1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			1.0f,  1.0f, -1.0f,      1.0f, 0.0f,
			1.0f, -1.0f, -1.0f,      1.0f, 1.0f,
			// Left
			-1.0f,  1.0f, 1.0f,     0.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,      1.0f, 1.0f,
			-1.0f, -1.0f, 1.0f,     0.0f, 1.0f,
			-1.0f,  1.0f, 1.0f,     0.0f, 0.0f,
			-1.0f,  1.0f, -1.0f,      1.0f, 0.0f,
			-1.0f, -1.0f, -1.0f,      1.0f, 1.0f,
			// Right
			1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			1.0f, -1.0f, 1.0f,      1.0f, 1.0f,
			1.0f, -1.0f, -1.0f,     0.0f, 1.0f,
			1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			1.0f,  1.0f, 1.0f,      1.0f, 0.0f,
			1.0f, -1.0f, 1.0f,      1.0f, 1.0f,
			// Bottom
			1.0f,  -1.0f, -1.0f,     0.0f, 0.0f,
			-1.0f, -1.0f, 1.0f,      1.0f, 1.0f,
			-1.0f, -1.0f, -1.0f,     0.0f, 1.0f,
			1.0f,  -1.0f, -1.0f,     0.0f, 0.0f,
			1.0f,  -1.0f, 1.0f,      1.0f, 0.0f,
			-1.0f, -1.0f, 1.0f,      1.0f, 1.0f,
			// Top
			-1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
			1.0f, 1.0f, -1.0f,     0.0f, 1.0f,
			-1.0f,  1.0f, -1.0f,     0.0f, 0.0f,
			-1.0f,  1.0f, 1.0f,      1.0f, 0.0f,
			1.0f, 1.0f, 1.0f,      1.0f, 1.0f,
		};
		wooden_box_stride = 5 * sizeof(float);
		wooden_box_numVerts = sizeof(vertexData) / wooden_box_stride;
		wooden_box_offset = 0;
		unsigned int size_in_bytes = sizeof(vertexData);
		float* myVertexData = malloc(size_in_bytes);
		if (myVertexData == NULL)
		{
			return false; // Failure
		}
		memcpy(myVertexData, vertexData, size_in_bytes);
		if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DEFAULT, &wooden_box_vertexBuffer))
		{
			return false; // Failure
		}
		free(myVertexData);
		myVertexData = NULL;
	}
	assert(wooden_box_vertexBuffer != NULL);



	// Place the wooden box into the world
	wooden_box_position = (float3) { -3.0f, 1.0f, 0.0f };


	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &wooden_box_samplerState))
	{
		return false; // Failure
	}
	assert(wooden_box_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create(d3d11Device, "Data/Textures/General/tile03.png", &wooden_box_textureView))
	{
		return false; // Failure
	}
	assert(wooden_box_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &wooden_box_constantBuffer))
	{
		return false; // Failure
	}
	assert(wooden_box_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	//if (!d3d11_rasterizer_state_create(d3d11Device, &wooden_box_rasterizerState))
	if (!d3d11_rasterizer_state_create(d3d11Device, &wooden_box_rasterizerState, true))
	{
		return false; // Failure
	}
	assert(wooden_box_rasterizerState != NULL);


	return true; // Success
}

static void wooden_box_update()
{
	// Spin the wooden box
	//float4x4 modelMat = rotateYMat(0.2f * (float)(M_PI * currentTimeInSeconds));
	float4x4 wooden_box_modelMat = translationMat(wooden_box_position);

	// Calculate model-view-projection matrix to send to shader
	float4x4 modelViewProj = mul44x3(wooden_box_modelMat, viewMat, perspectiveMat);

	// Update constant buffer (Upload to GPU constant buffer)
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)wooden_box_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->modelViewProj = modelViewProj;
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)wooden_box_constantBuffer, 0);
}

static void wooden_box_pipeline()
{
	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, wooden_box_rasterizerState);

	//ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, NULL);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, wooden_box_inputLayout);

	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, wooden_box_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, wooden_box_pixelShader, NULL, 0);

	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &wooden_box_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &wooden_box_samplerState);

	ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &wooden_box_constantBuffer);

	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &wooden_box_vertexBuffer, &wooden_box_stride, &wooden_box_offset);
}

static void wooden_box_render()
{
	unsigned int startVertex = 0;
	ID3D11DeviceContext1_Draw(d3d11DeviceContext, wooden_box_numVerts, startVertex);
}
