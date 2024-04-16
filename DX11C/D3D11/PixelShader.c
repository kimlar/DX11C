#include "PixelShader.h"

// Create Pixel Shader
bool d3d11_pixel_shader_create(ID3D11Device1* d3d11Device, WCHAR* psFileName, ID3D11PixelShader** pixelShader, ID3DBlob** psBlob)
{
	ID3DBlob* shaderCompileErrorsBlob = NULL;
	HRESULT hResult = D3DCompileFromFile(psFileName, NULL, NULL, "ps_main", "ps_5_0", 0, 0, psBlob, &shaderCompileErrorsBlob);
	if (FAILED(hResult))
	{
		const char* errorString = NULL;
		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			errorString = "Could not find pixel shader file";
		}
		else if (shaderCompileErrorsBlob)
		{
			errorString = (const char*)ID3D10Blob_GetBufferPointer(shaderCompileErrorsBlob);
			ID3D10Blob_Release(shaderCompileErrorsBlob);
		}
		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return false; // Failure
	}

	hResult = ID3D11Device_CreatePixelShader(d3d11Device, ID3D10Blob_GetBufferPointer(*psBlob), ID3D10Blob_GetBufferSize(*psBlob), NULL, pixelShader);
	assert(SUCCEEDED(hResult));
	if(FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
