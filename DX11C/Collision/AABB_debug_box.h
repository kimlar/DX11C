#pragma once
#include "../D3D11/Core.h"
#include "../Math/gpu_math.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"

ID3D11VertexShader* AABB_debug_box_vertexShader = NULL;
ID3D11PixelShader*  AABB_debug_box_pixelShader = NULL;
ID3D11InputLayout*  AABB_debug_box_inputLayout = NULL;
ID3D11Buffer* AABB_debug_box_vertexBuffer = NULL;
ID3D11SamplerState* AABB_debug_box_samplerState = NULL;
ID3D11ShaderResourceView* AABB_debug_box_textureView = NULL;
ID3D11Buffer* AABB_debug_box_constantBuffer = NULL;
ID3D11RasterizerState* AABB_debug_box_rasterizerState = NULL;
//float3 AABB_debug_box_position = { 0.0f, 0.0f, 0.0f }; // TODO: Make an array of AABBs instead of a single one
//float6 AABB_debug_box_dimensions = { -0.25f, 0.25f, 0.0f, 1.0f, -0.25f, 0.25f }; // minX, maxX, minY, maxY, minZ, maxZ;

//static bool AABB_debug_box_create(float3 spawn_position)
static bool AABB_debug_box_create()
{
	// Create Vertex Shader
	//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/AABB_debug_box_shader_vs.hlsl", &AABB_debug_box_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/AABB_debug_box_shader_ps.hlsl", &AABB_debug_box_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &AABB_debug_box_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_inputLayout != NULL);




	// Clean up shader blobs
	ID3D10Blob_Release(vsBlob);
	ID3D10Blob_Release(psBlob);






	// Create Vertex Buffer
	float6 AABB_debug_box_dimensions = { -0.25f, 0.25f, 0.0f, 1.0f, -0.25f, 0.25f }; // minX, maxX, minY, maxY, minZ, maxZ;
	{
		float vertexData[] = { // x, y, z, u, v
			// Front
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			// Back
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	1.0f, 1.0f,
			// Left
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	1.0f, 1.0f,
			// Right
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			// Bottom
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.minY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			// Top
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 1.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.minZ,	0.0f, 0.0f,
			AABB_debug_box_dimensions.minX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 0.0f,
			AABB_debug_box_dimensions.maxX, AABB_debug_box_dimensions.maxY, AABB_debug_box_dimensions.maxZ,	1.0f, 1.0f,
		};
		unsigned int stride = 20;			// To calculate: stride = n * sizeof(float) <--- n = {x, y, z, u, v} = 5
		unsigned int numVerts = 36;			// To calculate: numVerts = sizeof(vertexData) / AABB_debug_box_stride;
		unsigned int offset = 0;			//
		unsigned int size_in_bytes = 720;	// To calculate: size_in_bytes = sizeof(vertexData);
		float* myVertexData = malloc(size_in_bytes);
		if (myVertexData == NULL)
		{
			return false; // Failure
		}
		memcpy(myVertexData, vertexData, size_in_bytes);
		//if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, &AABB_debug_box_vertexBuffer))
		if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DEFAULT, &AABB_debug_box_vertexBuffer))
		{
			return false; // Failure
		}
		free(myVertexData);
		myVertexData = NULL;
	}
	assert(AABB_debug_box_vertexBuffer != NULL);



	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &AABB_debug_box_samplerState))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create(d3d11Device, "Data/Textures/Debug/AABB_debug_box.png", &AABB_debug_box_textureView))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &AABB_debug_box_constantBuffer))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	//if (!d3d11_rasterizer_state_create(d3d11Device, &player_rasterizerState))
	//if (!d3d11_rasterizer_state_create(d3d11Device, &player_rasterizerState, true))
	if (!d3d11_rasterizer_state_wireframe_create(d3d11Device, &AABB_debug_box_rasterizerState, true))
	{
		return false; // Failure
	}
	assert(AABB_debug_box_rasterizerState != NULL);


	return true; // Success
}

static void AABB_debug_box_update(float3 object_position)
{
	// Place the AABB_debug_box into the world
	float4x4 AABB_debug_box_modelMat = mul44(identityMat(), translationMat(object_position));

	//-----------------------------------------------------------------------------

	// Calculate model-view-projection matrix to send to shader
	float4x4 modelViewProj = mul44x3(AABB_debug_box_modelMat, viewMat, perspectiveMat);

	// Update constant buffer (Upload to GPU constant buffer)
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)AABB_debug_box_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->modelViewProj = modelViewProj;
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)AABB_debug_box_constantBuffer, 0);
}

static void AABB_debug_box_pipeline()
{
	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, AABB_debug_box_rasterizerState);

	//ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, NULL);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, AABB_debug_box_inputLayout);

	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, AABB_debug_box_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, AABB_debug_box_pixelShader, NULL, 0);

	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &AABB_debug_box_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &AABB_debug_box_samplerState);

	ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &AABB_debug_box_constantBuffer);

	unsigned int stride = 20;
	unsigned int offset = 0;
	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &AABB_debug_box_vertexBuffer, &stride, &offset);
}

static void AABB_debug_box_render()
{
	//unsigned int startVertex = 0;
	//ID3D11DeviceContext1_Draw(d3d11DeviceContext, AABB_debug_box_numVerts, startVertex);
	ID3D11DeviceContext1_Draw(d3d11DeviceContext, 36, 0);
}
