#include "VertexShader.h"

// Create Vertex Shader
bool d3d11_vertex_shader_create(ID3D11Device1* d3d11Device, WCHAR* vsFileName, ID3D11VertexShader** vertexShader, ID3DBlob** vsBlob)
{
	ID3DBlob* shaderCompileErrorsBlob = NULL;
	//HRESULT hResult = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "vs_main", "vs_5_0", 0, 0, vsBlob, &shaderCompileErrorsBlob);
	HRESULT hResult = D3DCompileFromFile(vsFileName, NULL, NULL, "vs_main", "vs_5_0", 0, 0, vsBlob, &shaderCompileErrorsBlob);
	if (FAILED(hResult))
	{
		const char* errorString = NULL;
		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
		{
			errorString = "Could not find vertex shader file";
		}
		else if (shaderCompileErrorsBlob)
		{
			errorString = (const char*)ID3D10Blob_GetBufferPointer(shaderCompileErrorsBlob);
			ID3D10Blob_Release(shaderCompileErrorsBlob);
		}
		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
		return false; // Failure
	}

	hResult = ID3D11Device_CreateVertexShader(d3d11Device, ID3D10Blob_GetBufferPointer(*vsBlob), ID3D10Blob_GetBufferSize(*vsBlob), NULL, vertexShader);
	assert(SUCCEEDED(hResult));
	if (FAILED(hResult))
	{
		return false; // Failure
	}

	return true; // Success
}
