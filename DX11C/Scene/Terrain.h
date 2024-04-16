#pragma once
#include "../D3D11/Core.h"
#include "../Math/gpu_math.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"

ID3D11VertexShader* terrain_vertexShader = NULL;
ID3D11PixelShader* terrain_pixelShader = NULL;
ID3D11InputLayout* terrain_inputLayout = NULL;
ID3D11Buffer* terrain_vertexBuffer = NULL;
unsigned int terrain_stride = 0;
unsigned int terrain_numVerts = 0;
unsigned int terrain_offset = 0;
ID3D11SamplerState* terrain_samplerState = NULL;
ID3D11ShaderResourceView* terrain_textureView = NULL;
ID3D11Buffer* terrain_constantBuffer = NULL;
ID3D11RasterizerState* terrain_rasterizerState = NULL;
float3 terrain_position = { 0.0f, 0.0f, 0.0f };

static bool terrain_create()
{
	// Create Vertex Shader
	//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/terrain_shader_vs.hlsl", &terrain_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(terrain_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/terrain_shader_ps.hlsl", &terrain_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(terrain_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &terrain_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(terrain_inputLayout != NULL);




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
			// **** -4
			// -5
			-5.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, -4.0f + 0.0f,     0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, -4.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, -4.0f + 1.0f,     1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -4.0f + 1.0f,     1.0f, 1.0f,
			// **** -3
			// -5
			-5.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, -3.0f + 0.0f,     0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, -3.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, -3.0f + 1.0f,     1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -3.0f + 1.0f,     1.0f, 1.0f,
			// **** -2
			// -5
			-5.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, -2.0f + 0.0f,     0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, -2.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, -2.0f + 1.0f,     1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -2.0f + 1.0f,     1.0f, 1.0f,
			// **** -1
			// -5
			-5.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, -1.0f + 0.0f,     0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, -1.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, -1.0f + 1.0f,     1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, -1.0f + 1.0f,     1.0f, 1.0f,
			// **** 0
			// -5
			-5.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, 0.0f + 0.0f,     0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, 0.0f + 0.0f,     0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, 0.0f + 1.0f,     1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 0.0f + 1.0f,     1.0f, 1.0f,
			// **** 1
			// -5
			-5.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, 1.0f + 0.0f, 0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, 1.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, 1.0f + 1.0f, 1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 1.0f + 1.0f, 1.0f, 1.0f,
			// **** 2
			// -5
			-5.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, 2.0f + 0.0f, 0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, 2.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, 2.0f + 1.0f, 1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 2.0f + 1.0f, 1.0f, 1.0f,
			// **** 3
			// -5
			-5.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			-5.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			-5.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-5.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			-5.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// -4
			-4.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			-4.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			-4.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-4.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			-4.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// -3
			-3.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			-3.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			-3.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-3.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			-3.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// -2
			-2.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			-2.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			-2.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-2.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			-2.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// -1
			-1.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			-1.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			-1.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			-1.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			-1.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// 0
			0.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			0.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			0.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			0.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			0.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// 1
			1.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			1.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			1.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			1.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			1.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			// 2
			2.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
			2.0f + 1.0f, 0.0f, 3.0f + 0.0f, 0.0f, 1.0f,
			2.0f + 0.0f, 0.0f, 3.0f + 0.0f, 0.0f, 0.0f,
			2.0f + 0.0f, 0.0f, 3.0f + 1.0f, 1.0f, 0.0f,
			2.0f + 1.0f, 0.0f, 3.0f + 1.0f, 1.0f, 1.0f,
		};
		terrain_stride = 5 * sizeof(float);
		terrain_numVerts = sizeof(vertexData) / terrain_stride;
		terrain_offset = 0;
		unsigned int size_in_bytes = sizeof(vertexData);
		float* myVertexData = malloc(size_in_bytes);
		if (myVertexData == NULL)
		{
			return false; // Failure
		}
		memcpy(myVertexData, vertexData, size_in_bytes);
		if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DEFAULT, &terrain_vertexBuffer))
		{
			return false; // Failure
		}
		free(myVertexData);
		myVertexData = NULL;
	}
	assert(terrain_vertexBuffer != NULL);



	// Place the terrain into the world
	terrain_position = (float3){ 0.0f, 0.0f, 0.0f };


	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &terrain_samplerState))
	{
		return false; // Failure
	}
	assert(terrain_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create(d3d11Device, "Data/Textures/Grass-00/grass09.png", &terrain_textureView))
	{
		return false; // Failure
	}
	assert(terrain_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &terrain_constantBuffer))
	{
		return false; // Failure
	}
	assert(terrain_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	if (!d3d11_rasterizer_state_create(d3d11Device, &terrain_rasterizerState, true))
	{
		return false; // Failure
	}
	assert(terrain_rasterizerState != NULL);


	return true; // Success
}

static void terrain_update()
{
	//...
	//float4x4 terrain_modelMat = rotateYMat(0.2f * (float)(M_PI * currentTimeInSeconds));
	float4x4 terrain_modelMat = translationMat(terrain_position);

	// Calculate model-view-projection matrix to send to shader
	float4x4 modelViewProj = mul44x3(terrain_modelMat, viewMat, perspectiveMat);

	// Update constant buffer (Upload to GPU constant buffer)
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)terrain_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->modelViewProj = modelViewProj;
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)terrain_constantBuffer, 0);
}

static void terrain_pipeline()
{
	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, terrain_rasterizerState);

	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, terrain_inputLayout);

	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, terrain_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, terrain_pixelShader, NULL, 0);

	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &terrain_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &terrain_samplerState);

	ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &terrain_constantBuffer);

	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &terrain_vertexBuffer, &terrain_stride, &terrain_offset);
}

static void terrain_render()
{
	unsigned int startVertex = 0;
	ID3D11DeviceContext1_Draw(d3d11DeviceContext, terrain_numVerts, startVertex);
}
