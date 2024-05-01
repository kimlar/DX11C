#pragma once
#include "../D3D11/Core.h"
#include "../Math/dx_math.h"

/*
//FILESOURCE: #include <C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/D3DX10Math.h>
typedef struct D3DXVECTOR3 {
	float x;
	float y;
	float z;
} D3DXVECTOR3, * LPD3DXVECTOR3;

typedef struct Vertex
{
	D3DXVECTOR3 position; //a 3D point even in 2D rendering
} Vertex, *LPVertex;
*/

Vertex* DrawRectangle_vertices;
unsigned long* DrawRectangle_indices;

D3D11_BUFFER_DESC DrawRectangle_vertexBufferDesc;
D3D11_BUFFER_DESC DrawRectangle_indexBufferDesc;
D3D11_SUBRESOURCE_DATA DrawRectangle_vertexData;
D3D11_SUBRESOURCE_DATA DrawRectangle_indexData;


ID3D11Buffer* DrawRectangle_vertexBuffer;
ID3D11Buffer* DrawRectangle_indexBuffer;

ID3D11VertexShader* DrawRectangle_vertexShader = NULL;
ID3D11PixelShader* DrawRectangle_pixelShader = NULL;
ID3D11InputLayout* DrawRectangle_inputLayout = NULL;

ID3D11SamplerState* DrawRectangle_samplerState = NULL;
ID3D11ShaderResourceView* DrawRectangle_textureView = NULL;
ID3D11Buffer* DrawRectangle_constantBuffer = NULL;
ID3D11RasterizerState* DrawRectangle_rasterizerState = NULL;
float3 DrawRectangle_position = { 0.0f, 0.0f, 0.0f };


bool DrawRectangle_create(float3 posA, float3 posB, float3 posC, float3 posD)
{
	// Create Vertex Shader
//ID3D11VertexShader* vertexShader = NULL;
	ID3DBlob* vsBlob = NULL;
	if (!d3d11_vertex_shader_create(d3d11Device, L"Data/Shaders/DebugBox_shader_vs.hlsl", &DrawRectangle_vertexShader, &vsBlob))
	{
		return false; // Failure
	}
	assert(DrawRectangle_vertexShader != NULL);
	assert(vsBlob != NULL);



	// Create Pixel Shader
	//ID3D11PixelShader* pixelShader = NULL;
	ID3DBlob* psBlob = NULL;
	if (!d3d11_pixel_shader_create(d3d11Device, L"Data/Shaders/DebugBox_shader_ps.hlsl", &DrawRectangle_pixelShader, &psBlob))
	{
		return false; // Failure
	}
	assert(DrawRectangle_pixelShader != NULL);
	assert(psBlob != NULL);





	// Create Input Layout
	//ID3D11InputLayout* inputLayout = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	if (!d3d11_input_layout_create(d3d11Device, &DrawRectangle_inputLayout, inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob))
	{
		return false; // Failure
	}
	assert(DrawRectangle_inputLayout != NULL);




	// Clean up shader blobs
	ID3D10Blob_Release(vsBlob);
	ID3D10Blob_Release(psBlob);










	//Vertex* vertices;
//unsigned long* indices = malloc(sizeof(unsigned long) * 5); //unsigned long* indices = new unsigned long[5];
//D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
//D3D11_SUBRESOURCE_DATA vertexData, indexData;

//create the vertex array	
	DrawRectangle_vertices = malloc(sizeof(Vertex) * 5); //vertices = new Vertex[5];
	if (!DrawRectangle_vertices)
	{
		//handle error
	}
	//load the vertex array with data
	DrawRectangle_vertices[0].position = (D3DXVECTOR3){ posA.x, posA.y, posA.z };
	DrawRectangle_vertices[1].position = (D3DXVECTOR3){ posB.x, posB.y, posB.z };
	DrawRectangle_vertices[2].position = (D3DXVECTOR3){ posC.x, posC.y, posC.z };
	DrawRectangle_vertices[3].position = (D3DXVECTOR3){ posD.x, posD.y, posD.z };
	DrawRectangle_vertices[4].position = (D3DXVECTOR3){ posA.x, posA.y, posA.z };

	/*
	DrawRectangle_vertices[0].position = (D3DXVECTOR3){ left, top, 0.0f };
	DrawRectangle_vertices[1].position = (D3DXVECTOR3){ right, top, 0.0f };
	DrawRectangle_vertices[2].position = (D3DXVECTOR3){ right, bottom, 0.0f };
	DrawRectangle_vertices[3].position = (D3DXVECTOR3){ left, bottom, 0.0f };
	DrawRectangle_vertices[4].position = (D3DXVECTOR3){ left, top, 0.0f };
	*/
	//create the index array
	//unsigned long* indices = malloc(sizeof(unsigned long) * 5);
	DrawRectangle_indices = malloc(sizeof(unsigned long) * 5);
	//indices = new unsigned long[5];
	if (!DrawRectangle_indices)
	{
		//handle error
	}
	//load the index array with data
	for (int i = 0; i < 5; i++)
		DrawRectangle_indices[i] = i;












	//ID3D11Buffer* vertexBuffer;
	//ID3D11Buffer* indexBuffer;
	HRESULT result;

	//set up the description of the dynamic vertex buffer
	DrawRectangle_vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC; //enables recreation and movement of vertices
	DrawRectangle_vertexBufferDesc.ByteWidth = sizeof(Vertex) * 5;
	DrawRectangle_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DrawRectangle_vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //couples with dynamic
	DrawRectangle_vertexBufferDesc.MiscFlags = 0;
	DrawRectangle_vertexBufferDesc.StructureByteStride = 0;
	//give the subresource structure a pointer to the vertex data
	DrawRectangle_vertexData.pSysMem = DrawRectangle_vertices;
	DrawRectangle_vertexData.SysMemPitch = 0;
	DrawRectangle_vertexData.SysMemSlicePitch = 0;

	//now create the vertex buffer
	//result = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	result = ID3D11Device_CreateBuffer(d3d11Device, &DrawRectangle_vertexBufferDesc, &DrawRectangle_vertexData, &DrawRectangle_vertexBuffer);
	if (FAILED(result))
	{
		//handle error
	}

	//set up the description of the static index buffer
	DrawRectangle_indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DrawRectangle_indexBufferDesc.ByteWidth = sizeof(unsigned long) * 5;
	DrawRectangle_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DrawRectangle_indexBufferDesc.CPUAccessFlags = 0;
	DrawRectangle_indexBufferDesc.MiscFlags = 0;
	DrawRectangle_indexBufferDesc.StructureByteStride = 0;
	//give the subresource structure a pointer to the index data
	DrawRectangle_indexData.pSysMem = DrawRectangle_indices;
	DrawRectangle_indexData.SysMemPitch = 0;
	DrawRectangle_indexData.SysMemSlicePitch = 0;

	//create the index buffer
	//result = d3d11Device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	result = ID3D11Device_CreateBuffer(d3d11Device, &DrawRectangle_indexBufferDesc, &DrawRectangle_indexData, &DrawRectangle_indexBuffer);
	if (FAILED(result))
	{
		//handle error
	}












	// Place the DrawRectangle into the world
	DrawRectangle_position = (float3){ 0.0f, 0.0f, 0.0f };


	// Create Sampler State
	//ID3D11SamplerState* samplerState = NULL;
	if (!d3d11_sampler_state_create(d3d11Device, &DrawRectangle_samplerState))
	{
		return false; // Failure
	}
	assert(DrawRectangle_samplerState != NULL);




	// Load ShaderResourceView (texture on GPU)
	//ID3D11ShaderResourceView* textureView = NULL;
	if (!d3d11_shader_resource_view_create(d3d11Device, "Data/Textures/Debug/DebugBox.png", &DrawRectangle_textureView))
	{
		return false; // Failure
	}
	assert(DrawRectangle_textureView != NULL);






	// Create Constant Buffer
	//ID3D11Buffer* constantBuffer = NULL;
	if (!d3d11_constant_buffer_create(d3d11Device, &DrawRectangle_constantBuffer))
	{
		return false; // Failure
	}
	assert(DrawRectangle_constantBuffer != NULL);





	// Create Rasterizer State
	//ID3D11RasterizerState* rasterizerState = NULL;
	//if (!d3d11_rasterizer_state_create(d3d11Device, &wooden_box_rasterizerState))
	if (!d3d11_rasterizer_state_create(d3d11Device, &DrawRectangle_rasterizerState, true))
	{
		return false; // Failure
	}
	assert(DrawRectangle_rasterizerState != NULL);




	return true; // Success
}

/*
void DrawRectangle_create_vertex_buffer_and_index_buffer(float top, float left, float bottom, float right)
{
	//Vertex* vertices;
	//unsigned long* indices = malloc(sizeof(unsigned long) * 5); //unsigned long* indices = new unsigned long[5];
	//D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	//D3D11_SUBRESOURCE_DATA vertexData, indexData;

	//create the vertex array	
	DrawRectangle_vertices = malloc(sizeof(Vertex) * 5); //vertices = new Vertex[5];
	if (!DrawRectangle_vertices)
	{
		//handle error
	}
	//load the vertex array with data
	DrawRectangle_vertices[0].position = (D3DXVECTOR3){ left, top, 0.0f };
	DrawRectangle_vertices[1].position = (D3DXVECTOR3){ right, top, 0.0f };
	DrawRectangle_vertices[2].position = (D3DXVECTOR3){ right, bottom, 0.0f };
	DrawRectangle_vertices[3].position = (D3DXVECTOR3){ left, bottom, 0.0f };
	DrawRectangle_vertices[4].position = (D3DXVECTOR3){ left, top, 0.0f };
	//create the index array
	//unsigned long* indices = malloc(sizeof(unsigned long) * 5);
	DrawRectangle_indices = malloc(sizeof(unsigned long) * 5);
	//indices = new unsigned long[5];
	if (!DrawRectangle_indices)
	{
		//handle error
	}
	//load the index array with data
	for (int i = 0; i < 5; i++)
		DrawRectangle_indices[i] = i;
}
*/

/*
void DrawRectangle_load_buffers()
{
	//ID3D11Buffer* vertexBuffer;
	//ID3D11Buffer* indexBuffer;
	HRESULT result;

	//set up the description of the dynamic vertex buffer
	DrawRectangle_vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC; //enables recreation and movement of vertices
	DrawRectangle_vertexBufferDesc.ByteWidth = sizeof(Vertex) * 5;
	DrawRectangle_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DrawRectangle_vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //couples with dynamic
	DrawRectangle_vertexBufferDesc.MiscFlags = 0;
	DrawRectangle_vertexBufferDesc.StructureByteStride = 0;
	//give the subresource structure a pointer to the vertex data
	DrawRectangle_vertexData.pSysMem = DrawRectangle_vertices;
	DrawRectangle_vertexData.SysMemPitch = 0;
	DrawRectangle_vertexData.SysMemSlicePitch = 0;

	//now create the vertex buffer
	//result = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	result = ID3D11Device_CreateBuffer(d3d11Device, &DrawRectangle_vertexBufferDesc, &DrawRectangle_vertexData, &DrawRectangle_vertexBuffer);
	if (FAILED(result))
	{
		//handle error
	}

	//set up the description of the static index buffer
	DrawRectangle_indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DrawRectangle_indexBufferDesc.ByteWidth = sizeof(unsigned long) * 5;
	DrawRectangle_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DrawRectangle_indexBufferDesc.CPUAccessFlags = 0;
	DrawRectangle_indexBufferDesc.MiscFlags = 0;
	DrawRectangle_indexBufferDesc.StructureByteStride = 0;
	//give the subresource structure a pointer to the index data
	DrawRectangle_indexData.pSysMem = DrawRectangle_indices;
	DrawRectangle_indexData.SysMemPitch = 0;
	DrawRectangle_indexData.SysMemSlicePitch = 0;

	//create the index buffer
	//result = d3d11Device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	result = ID3D11Device_CreateBuffer(d3d11Device, &DrawRectangle_indexBufferDesc, &DrawRectangle_indexData, &DrawRectangle_indexBuffer);
	if (FAILED(result))
	{
		//handle error
	}
}
*/










/*
bool DrawRectangle_update(ID3D11Buffer* vertexBuffer, ID3D11DeviceContext* deviceContext, float top, float left, float bottom, float right)
{
	Vertex* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	//create a temporary vertex array to fill with the updated data
	vertices = new Vertex[5];
	if (!vertices)
	{
		return false;
	}
	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[1].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[2].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[3].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[4].position = D3DXVECTOR3(left, top, 0.0f);

	//lock the vertex buffer so it can be written to
	result = deviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	verticesPtr = (Vertex*)mappedResource.pData;

	//copy the data into the vertex buffer
	memcpy(verticesPtr, (void*)vertices, (sizeof(Vertex) * 5));

	deviceContext->Unmap(vertexBuffer, 0);
	delete[] vertices;
	vertices = 0;

	return true;
}
*/



//bool DrawRectangle_update(ID3D11Buffer* vertexBuffer, ID3D11DeviceContext* deviceContext, float top, float left, float bottom, float right)
//bool DrawRectangle_update(float top, float left, float bottom, float right)
bool DrawRectangle_update(float3 posA, float3 posB, float3 posC, float3 posD)
{
	Vertex* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	//VertexType* verticesPtr;
	LPVertex verticesPtr;
	HRESULT result;

	//create a temporary vertex array to fill with the updated data
	//vertices = new Vertex[5];
	vertices = malloc(sizeof(Vertex) * 5);
	if (!vertices)
	{
		return false;
	}
	vertices[0].position = (D3DXVECTOR3){ posA.x, posA.y, posA.z };
	vertices[1].position = (D3DXVECTOR3){ posB.x, posB.y, posB.z };
	vertices[2].position = (D3DXVECTOR3){ posC.x, posC.y, posC.z };
	vertices[3].position = (D3DXVECTOR3){ posD.x, posD.y, posD.z };
	vertices[4].position = (D3DXVECTOR3){ posA.x, posA.y, posA.z };
	/*
	vertices[0].position = (D3DXVECTOR3){ left, top, 0.0f };
	vertices[1].position = (D3DXVECTOR3){ right, top, 0.0f };
	vertices[2].position = (D3DXVECTOR3){ right, bottom, 0.0f };
	vertices[3].position = (D3DXVECTOR3){ left, bottom, 0.0f };
	vertices[4].position = (D3DXVECTOR3){ left, top, 0.0f };
	*/

	//lock the vertex buffer so it can be written to
	//result = deviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	result = ID3D11DeviceContext1_Map(d3d11DeviceContext, (ID3D11Resource*)DrawRectangle_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	verticesPtr = (Vertex*)mappedResource.pData;

	//copy the data into the vertex buffer
	memcpy(verticesPtr, (void*)vertices, (sizeof(Vertex) * 5));

	//deviceContext->Unmap(vertexBuffer, 0);
	ID3D11DeviceContext1_Unmap(d3d11DeviceContext, (ID3D11Resource*)DrawRectangle_vertexBuffer, 0);
	//delete[] vertices;
	free(vertices);
	vertices = 0;

	return true;
}






void DrawRectangle_render()
{
	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	//deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	//ID3D11DeviceContext1_Draw(d3d11DeviceContext, player_numVerts, startVertex);
	//ID3D11DeviceContext1_DrawIndexed(d3d11DeviceContext, 5, 0, 0);
//	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &DrawRectangle_vertexBuffer, &stride, &offset);
//	ID3D11DeviceContext1_IASetIndexBuffer(d3d11DeviceContext, DrawRectangle_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
//
//
//	ID3D11DeviceContext1_DrawIndexed(d3d11DeviceContext, 5, 0, 0);



	ID3D11DeviceContext1_RSSetState(d3d11DeviceContext, DrawRectangle_rasterizerState);
	ID3D11DeviceContext1_OMSetRenderTargets(d3d11DeviceContext, 1, &d3d11FrameBufferView, d3d11DepthStencilView);


	ID3D11DeviceContext1_IASetVertexBuffers(d3d11DeviceContext, 0, 1, &DrawRectangle_vertexBuffer, &stride, &offset);
	ID3D11DeviceContext1_IASetIndexBuffer(d3d11DeviceContext, DrawRectangle_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	ID3D11DeviceContext1_IASetPrimitiveTopology(d3d11DeviceContext, D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	ID3D11DeviceContext1_IASetInputLayout(d3d11DeviceContext, DrawRectangle_inputLayout);


	ID3D11DeviceContext1_VSSetShader(d3d11DeviceContext, DrawRectangle_vertexShader, NULL, 0);
	ID3D11DeviceContext1_PSSetShader(d3d11DeviceContext, DrawRectangle_pixelShader, NULL, 0);


	ID3D11DeviceContext1_PSSetShaderResources(d3d11DeviceContext, 0, 1, &DrawRectangle_textureView);
	ID3D11DeviceContext1_PSSetSamplers(d3d11DeviceContext, 0, 1, &DrawRectangle_samplerState);


	//ID3D11DeviceContext1_VSSetConstantBuffers(d3d11DeviceContext, 0, 1, &DrawRectangle_constantBuffer);

	

	
	ID3D11DeviceContext1_DrawIndexed(d3d11DeviceContext, 5, 0, 0);


}
