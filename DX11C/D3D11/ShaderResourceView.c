#include "ShaderResourceView.h"
#include "../Resource/Image/LoadPNG.h"
#include "../FileSystem/file_system_read_binary.h"

// Load ShaderResourceView (texture on GPU)
bool d3d11_shader_resource_view_create(ID3D11Device1* d3d11Device, const char* fileName, ID3D11ShaderResourceView** shaderResourceView)
{
	// Load temporary image
	int texWidth;
	int texHeight;
	int texNumChannels;
	unsigned char* tempTextureData = resource_load_png(fileName, &texWidth, &texHeight, &texNumChannels);
	assert(tempTextureData);
	if(tempTextureData == NULL)
	{
		return false; // Failure
	}

	// Create Texture
	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	textureDesc.Width = texWidth;
	textureDesc.Height = texHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA textureSubresourceData = { 0 };
	textureSubresourceData.pSysMem = tempTextureData;
	textureSubresourceData.SysMemPitch = texNumChannels * texWidth;

	ID3D11Texture2D* texture = NULL;
	ID3D11Device_CreateTexture2D(d3d11Device, &textureDesc, &textureSubresourceData, &texture);
	assert(texture);
	if(texture == NULL)
	{
		return false; // Failure
	}

	HRESULT hResult = ID3D11Device_CreateShaderResourceView(d3d11Device, (ID3D11Resource*)texture, NULL, shaderResourceView);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}
	ID3D11Texture2D_Release(texture);

	// Unload temporary image
	free(tempTextureData);
	tempTextureData = NULL;

	return true; // Success
}

// Load ShaderResourceView (texture on GPU)
bool d3d11_shader_resource_view_create_rgba(ID3D11Device1* d3d11Device, const char* fileName, ID3D11ShaderResourceView** shaderResourceView)
{
	// Load temporary image
	int texType = 2; // 0: Unknown, 1: RGB, 2: RGBA, 3: Grayscale(1 byte per pixel), 4: Grayscale(2 bytes per pixel), 5: Grayscale(3 bytes per pixel), 6: Grayscale(4 bytes per pixel), 7: Grayscale(4 bytes per pixel as float)
	int texWidth = 256; // TODO: Get from file
	int texHeight = 256; // TODO: Get from file
	int texNumChannels = 4; // TODO: Get from file
	//unsigned char* tempTextureData = resource_load_png(fileName, &texWidth, &texHeight, &texNumChannels);
	unsigned int fileSize = texWidth * texHeight * texNumChannels;
	unsigned char* tempTextureData = file_system_read_binary(fileName, fileSize);

	assert(tempTextureData);
	if (tempTextureData == NULL)
	{
		return false; // Failure
	}

	// Create Texture
	D3D11_TEXTURE2D_DESC textureDesc = { 0 };
	textureDesc.Width = texWidth;
	textureDesc.Height = texHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA textureSubresourceData = { 0 };
	textureSubresourceData.pSysMem = tempTextureData;
	textureSubresourceData.SysMemPitch = texNumChannels * texWidth;

	ID3D11Texture2D* texture = NULL;
	ID3D11Device_CreateTexture2D(d3d11Device, &textureDesc, &textureSubresourceData, &texture);
	assert(texture);
	if (texture == NULL)
	{
		return false; // Failure
	}

	HRESULT hResult = ID3D11Device_CreateShaderResourceView(d3d11Device, (ID3D11Resource*)texture, NULL, shaderResourceView);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}
	ID3D11Texture2D_Release(texture);

	// Unload temporary image
	free(tempTextureData);
	tempTextureData = NULL;

	return true; // Success
}
