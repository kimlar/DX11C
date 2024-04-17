#include "VertexBuffer.h"

// Create Vertex Buffer
//bool d3d11_vertex_buffer_create(ID3D11Device1* d3d11Device, float* vertexData, unsigned int vertexDataSize, enum D3D11_USAGE usage, enum D3D11_CPU_ACCESS_FLAG cpuAccess, ID3D11Buffer** vertexBuffer)
bool d3d11_vertex_buffer_create(ID3D11Device1* d3d11Device, float* vertexData, unsigned int vertexDataSize, enum D3D11_USAGE usage, ID3D11Buffer** vertexBuffer)
{
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = vertexDataSize;
	vertexBufferDesc.Usage = usage; //D3D11_USAGE_DEFAULT; //D3D11_USAGE_DYNAMIC //D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDesc.CPUAccessFlags = cpuAccess; // Note: D3D11_USAGE_DYNAMIC must be set in .Usage field if you want to have CPU access to write to it.

	D3D11_SUBRESOURCE_DATA vertexSubresourceData = { vertexData };

	HRESULT hResult = ID3D11Device_CreateBuffer(d3d11Device, &vertexBufferDesc, &vertexSubresourceData, vertexBuffer);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
