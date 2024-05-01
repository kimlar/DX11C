#pragma once

//FILESOURCE: #include <C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/D3DX10Math.h>
typedef struct D3DXVECTOR3 {
	float x;
	float y;
	float z;
} D3DXVECTOR3, * LPD3DXVECTOR3;

typedef struct Vertex
{
	D3DXVECTOR3 position; //a 3D point even in 2D rendering
} Vertex, * LPVertex;
