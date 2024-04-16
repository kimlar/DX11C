#include "Device.h"

// Create D3D11 Device and Device Context
bool d3d11_device_create(ID3D11Device1** d3d11Device, ID3D11DeviceContext1** d3d11DeviceContext)
{
	ID3D11Device* baseDevice = NULL;
	ID3D11DeviceContext* baseDeviceContext = NULL;
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
		0, creationFlags,
		featureLevels, ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION, &baseDevice,
		0, &baseDeviceContext);
	if (FAILED(hResult))
	{
		MessageBoxA(0, "D3D11CreateDevice() failed", "Fatal Error", MB_OK);
		DWORD dw = GetLastError();
		return false; // Failure
	}

	// Get 1.1 interface of D3D11 Device and Context        
	hResult = ID3D11Device_QueryInterface(baseDevice, &IID_ID3D11Device1, (void**)d3d11Device);
	assert(SUCCEEDED(hResult));
	ID3D11Device_Release(baseDevice);
	//
	hResult = ID3D11DeviceContext_QueryInterface(baseDeviceContext, &IID_ID3D11DeviceContext1, (void**)d3d11DeviceContext);
	assert(SUCCEEDED(hResult));
	ID3D11DeviceContext_Release(baseDeviceContext);

	return true; // Success
}