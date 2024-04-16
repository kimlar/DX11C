#include "DebugLayer.h"

// Initialize debug layer
bool d3d11_debug_layer_init(ID3D11Device1* d3d11Device)
{
	// Set up debug layer to break on D3D11 errors
	ID3D11Debug* d3dDebug = NULL;
	ID3D11Device1_QueryInterface(d3d11Device, &IID_ID3D11Debug, (void**)&d3dDebug);
	if (!d3dDebug)
	{
		return false; // Failure
	}

	ID3D11InfoQueue* d3dInfoQueue = NULL;
	if (FAILED(ID3D11Debug_QueryInterface(d3dDebug, &IID_ID3D11InfoQueue, (void**)&d3dInfoQueue)))
	{
		return false; // Failure
	}

	ID3D11InfoQueue_SetBreakOnSeverity(d3dInfoQueue, D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
	ID3D11InfoQueue_SetBreakOnSeverity(d3dInfoQueue, D3D11_MESSAGE_SEVERITY_ERROR, true);
	ID3D11InfoQueue_Release(d3dInfoQueue);

	ID3D11Debug_Release(d3dDebug);
	
	return true;
}
