#pragma once
#include "../D3D11/Core.h"
#include "../Math/gpu_math.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"

ID3D11VertexShader* player_vertexShader = NULL;
ID3D11PixelShader* player_pixelShader = NULL;
ID3D11InputLayout* player_inputLayout = NULL;
ID3D11Buffer* player_vertexBuffer = NULL;
unsigned int player_stride = 0;
unsigned int player_numVerts = 0;
unsigned int player_offset = 0;
ID3D11SamplerState* player_samplerState = NULL;
ID3D11ShaderResourceView* player_textureView = NULL;
ID3D11Buffer* player_constantBuffer = NULL;
ID3D11RasterizerState* player_rasterizerState = NULL;
float3 player_position = { 0.0f, 0.0f, 0.0f };
float3 player_forward = { 0.0f, 0.0f, -1.0f };

static bool player_create()
{
	// Create Vertex Shader
	//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/player_shader_vs.hlsl", &player_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(player_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/player_shader_ps.hlsl", &player_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(player_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &player_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(player_inputLayout != NULL);




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
			-0.25f, 0.0f, 0.25f,	0.0f, 0.0f,
			 0.25f, 1.0f, 0.25f,	1.0f, 1.0f,
			-0.25f, 1.0f, 0.25f,	0.0f, 1.0f,
			-0.25f, 0.0f, 0.25f,	0.0f, 0.0f,
			 0.25f, 0.0f, 0.25f,	1.0f, 0.0f,
			 0.25f, 1.0f, 0.25f,	1.0f, 1.0f,
			// Back
			-0.25f, 1.0f, -0.25f,	0.0f, 0.0f,
			 0.25f, 0.0f, -0.25f,	1.0f, 1.0f,
			-0.25f, 0.0f, -0.25f,	0.0f, 1.0f,
			-0.25f, 1.0f, -0.25f,	0.0f, 0.0f,
			 0.25f, 1.0f, -0.25f,	1.0f, 0.0f,
			 0.25f, 0.0f, -0.25f,	1.0f, 1.0f,
			// Left
			-0.25f, 1.0f, 0.25f,	0.0f, 0.0f,
			-0.25f, 0.0f,-0.25f,	1.0f, 1.0f,
			-0.25f, 0.0f, 0.25f,	0.0f, 1.0f,
			-0.25f, 1.0f, 0.25f,	0.0f, 0.0f,
			-0.25f, 1.0f,-0.25f,	1.0f, 0.0f,
			-0.25f, 0.0f,-0.25f,	1.0f, 1.0f,
			// Right
			0.25f, 1.0f,-0.25f,		0.0f, 0.0f,
			0.25f, 0.0f, 0.25f,		1.0f, 1.0f,
			0.25f, 0.0f,-0.25f,		0.0f, 1.0f,
			0.25f, 1.0f,-0.25f,		0.0f, 0.0f,
			0.25f, 1.0f, 0.25f,		1.0f, 0.0f,
			0.25f, 0.0f, 0.25f,		1.0f, 1.0f,
			// Bottom
			 0.25f, 0.0f,-0.25f,	0.0f, 0.0f,
			-0.25f, 0.0f, 0.25f,	1.0f, 1.0f,
			-0.25f, 0.0f,-0.25f,	0.0f, 1.0f,
			 0.25f, 0.0f,-0.25f,	0.0f, 0.0f,
			 0.25f, 0.0f, 0.25f,	1.0f, 0.0f,
			-0.25f, 0.0f, 0.25f,	1.0f, 1.0f,
			// Top
			-0.25f, 1.0f,-0.25f,	0.0f, 0.0f,
			 0.25f, 1.0f, 0.25f,	1.0f, 1.0f,
			 0.25f, 1.0f,-0.25f,	0.0f, 1.0f,
			-0.25f, 1.0f,-0.25f,	0.0f, 0.0f,
			-0.25f, 1.0f, 0.25f,	1.0f, 0.0f,
			 0.25f, 1.0f, 0.25f,	1.0f, 1.0f,
		};
		player_stride = 5 * sizeof(float);
		player_numVerts = sizeof(vertexData) / player_stride;
		player_offset = 0;
		unsigned int size_in_bytes = sizeof(vertexData);
		float* myVertexData = malloc(size_in_bytes);
		if (myVertexData == NULL)
		{
			return false; // Failure
		}
		memcpy(myVertexData, vertexData, size_in_bytes);
		if (!d3d11_vertex_buffer_create(d3d11Device, myVertexData, size_in_bytes, D3D11_USAGE_DEFAULT, &player_vertexBuffer))
		{
			return false; // Failure
		}
		free(myVertexData);
		myVertexData = NULL;
	}
	assert(player_vertexBuffer != NULL);



	// Place the player into the world
	player_position = (float3){ 0.0f, 0.0f, 0.0f };


	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &player_samplerState))
	{
		return false; // Failure
	}
	assert(player_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create(d3d11Device, "Data/Textures/General-01/player-simple-frame.png", &player_textureView))
	{
		return false; // Failure
	}
	assert(player_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &player_constantBuffer))
	{
		return false; // Failure
	}
	assert(player_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	//if (!d3d11_rasterizer_state_create(d3d11Device, &player_rasterizerState))
	//if (!d3d11_rasterizer_state_create(d3d11Device, &player_rasterizerState, true))
	if (!d3d11_rasterizer_state_wireframe_create(d3d11Device, &player_rasterizerState, true))
	{
		return false; // Failure
	}
	assert(player_rasterizerState != NULL);


	return true; // Success
}

static void player_update(float dt)
{

	float3 playerFwdXZ = normalise((float3) { player_forward.x, 0, player_forward.z });
	float3 playerRightXZ = cross(playerFwdXZ, (float3) { 0, 1, 0 });
	
	float player_speed = 5.0f;
	float player_movementSpeed = player_speed * dt;
	if (global_keyIsDown[GameActionPlayerMoveForward])
	{
		add_equal(&player_position, mul(playerFwdXZ, player_movementSpeed));
	}
	if (global_keyIsDown[GameActionPlayerMoveBackward])
	{
		sub_equal(&player_position, mul(playerFwdXZ, player_movementSpeed));
	}
	if (global_keyIsDown[GameActionPlayerStrafeLeft])
	{
		sub_equal(&player_position, mul(playerRightXZ, player_movementSpeed));
	}
	if (global_keyIsDown[GameActionPlayerStrafeRight])
	{
		add_equal(&player_position, mul(playerRightXZ, player_movementSpeed));
	}


	// Spin the player
	//float4x4 modelMat = rotateYMat(0.2f * (float)(M_PI * currentTimeInSeconds));
	float4x4 player_modelMat = translationMat(player_position);

	

	// Update the forward vector we use for player movement:
	//player_forward = (float3){ -viewMat.m[2][0], -viewMat.m[2][1], -viewMat.m[2][2] };


	//float3 camFwdXZ;
	cameraFwd.x = player_forward.x;
	cameraFwd.y = player_forward.y;
	cameraFwd.z = player_forward.z;

	//float3 cameraRightXZ = cross(cameraFwd, (float3) { 0, 1, 0 });

	cameraPos.x = player_position.x;
	cameraPos.y = player_position.y;
	cameraPos.z = player_position.z;

	add_equal(&cameraPos, mul((float3) { 0.0f, 1.0f, 0.0f }, 1.5f));
	//add_equal(&cameraPos, mul((float3) {0.0f, 0.0f, 1.0f}, 2.0f));
	add_equal(&cameraPos, mul(cameraFwd, -2.0f));

	/*
	*/
	// Calculate view matrix from camera data
	camera_update_view_matrix();
	// Update the forward vector we use for camera movement:
	camera_update_forward_vector();




	// Calculate model-view-projection matrix to send to shader
	float4x4 modelViewProj = mul44x3(player_modelMat, viewMat, perspectiveMat);

	// Update constant buffer (Upload to GPU constant buffer)
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)player_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource);
	Constants* constants = (Constants*)(mappedSubresource.pData);
	constants->modelViewProj = modelViewProj;
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)player_constantBuffer, 0);
}

static void player_pipeline()
{
	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, player_rasterizerState);

	//ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, NULL);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);

	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, player_inputLayout);

	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, player_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, player_pixelShader, NULL, 0);

	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &player_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &player_samplerState);

	ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &player_constantBuffer);

	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &player_vertexBuffer, &player_stride, &player_offset);
}

static void player_render()
{
	unsigned int startVertex = 0;
	ID3D11DeviceContext1_Draw(d3d11DeviceContext, player_numVerts, startVertex);
}
