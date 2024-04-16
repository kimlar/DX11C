#pragma once

#define _USE_MATH_DEFINES 
#include <math.h>

typedef struct float2
{
    float x, y;
} float2;

typedef struct float3
{
    float x, y, z;
} float3;

typedef struct float4
{
    float x, y, z, w;
} float4;

typedef struct float4x4
{
    float m[4][4];
} float4x4;

inline float4 row(float4x4* mat4x4, int i)
{ // Returns i-th row of matrix    
    return (float4){ mat4x4->m[0][i], mat4x4->m[1][i], mat4x4->m[2][i], mat4x4->m[3][i] };
}

inline float4 cols(float4x4* mat4x4, int i)
{ // Returns i-th col of matrix    
    return (float4) { mat4x4->m[i][0], mat4x4->m[i][1], mat4x4->m[i][2], mat4x4->m[i][3] };
}

inline float degreesToRadians(float degs)
{
    return degs * ((float)M_PI / 180.0f);
}

inline float length(float3 v)
{
    float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return result;
}

inline float dot(float4 a, float4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline float3 mul(float3 v, float f)
{
    return (float3){ v.x * f, v.y * f, v.z * f };
}

inline float3 normalise(float3 v)
{
    return mul(v, 1.f / length(v));
}

inline float3 cross(float3 a, float3 b)
{
    return (float3)
    {
        (a.y * b.z - a.z * b.y),
        (a.z * b.x - a.x * b.z),
        (a.x * b.y - a.y * b.x)
    };
}

// 'a' is source and 'b' is increment
inline void add_equal(float3* a, float3 b)
{
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

// 'a' is source and 'b' is decrement
inline void sub_equal(float3* a, float3 b)
{
	a->x -= b.x;
	a->y -= b.y;
	a->z -= b.z;
}

inline float3 negate(float3 v)
{
	return (float3){ -v.x, -v.y, -v.z };
}

inline float4x4 rotateXMat(float rad)
{
    float sinTheta = sinf(rad);
    float cosTheta = cosf(rad);
    return (float4x4)
    {
        1, 0, 0, 0,
        0, cosTheta, -sinTheta, 0,
        0, sinTheta, cosTheta, 0,
        0, 0, 0, 1
    };
}

inline float4x4 rotateYMat(float rad)
{
    float sinTheta = sinf(rad);
    float cosTheta = cosf(rad);
    return (float4x4)
    {
        cosTheta, 0, sinTheta, 0,
        0, 1, 0, 0,
        -sinTheta, 0, cosTheta, 0,
        0, 0, 0, 1
    };
}

inline float4x4 translationMat(float3 trans)
{
    return (float4x4)
    {
        1, 0, 0, trans.x,
        0, 1, 0, trans.y,
        0, 0, 1, trans.z,
        0, 0, 0, 1
    };
}

inline float4x4 translationMatPtr(float3 trans, float4x4* mat4x4)
{
	return (float4x4)
	{
		mat4x4->m[0][0], mat4x4->m[0][1], mat4x4->m[0][2], mat4x4->m[0][3] + trans.x,
		mat4x4->m[1][0], mat4x4->m[1][1], mat4x4->m[1][2], mat4x4->m[1][3] + trans.y,
		mat4x4->m[2][0], mat4x4->m[2][1], mat4x4->m[2][2], mat4x4->m[2][3] + trans.z,
		mat4x4->m[3][0], mat4x4->m[3][1], mat4x4->m[3][2], mat4x4->m[3][3],
	};

	/*
	return (float4x4)
	{
		1, 0, 0, trans.x,
		0, 1, 0, trans.y,
		0, 0, 1, trans.z,
		0, 0, 0, 1
	};
	*/
}

inline float4x4 makePerspectiveMat(float aspectRatio, float fovYRadians, float zNear, float zFar)
{
    // float yScale = 1 / tanf(0.5f * fovYRadians); 
    // NOTE: 1/tan(X) = tan(90degs - X), so we can avoid a divide
    // float yScale = tanf((0.5f * M_PI) - (0.5f * fovYRadians));
    float yScale = tanf(0.5f * ((float)M_PI - fovYRadians));
    float xScale = yScale / aspectRatio;
    float zRangeInverse = 1.f / (zNear - zFar);
    float zScale = zFar * zRangeInverse;
    float zTranslation = zFar * zNear * zRangeInverse;

    float4x4 result = {
        xScale, 0, 0, 0,
        0, yScale, 0, 0,
        0, 0, zScale, zTranslation,
        0, 0, -1, 0
    };
    return result;
}

inline float4x4 mul44(float4x4 a, float4x4 b)
{
    return (float4x4)
    {
        dot(row(&a, 0), cols(&b, 0)),
        dot(row(&a, 1), cols(&b, 0)),
        dot(row(&a, 2), cols(&b, 0)),
        dot(row(&a, 3), cols(&b, 0)),

        dot(row(&a, 0), cols(&b, 1)),
        dot(row(&a, 1), cols(&b, 1)),
        dot(row(&a, 2), cols(&b, 1)),
        dot(row(&a, 3), cols(&b, 1)),

        dot(row(&a, 0), cols(&b, 2)),
        dot(row(&a, 1), cols(&b, 2)),
        dot(row(&a, 2), cols(&b, 2)),
        dot(row(&a, 3), cols(&b, 2)),
        
        dot(row(&a, 0), cols(&b, 3)),
        dot(row(&a, 1), cols(&b, 3)),
        dot(row(&a, 2), cols(&b, 3)),
        dot(row(&a, 3), cols(&b, 3)),
    };
}

inline float4x4 mul44x3(float4x4 a, float4x4 b, float4x4 c)
{
    return mul44(mul44(a, b), c);
}

inline float4x4 identityMat()
{
	return (float4x4)
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

inline float3 get_position_from_matrix(float4x4* mat4x4)
{
	return (float3){ mat4x4->m[3][0], mat4x4->m[3][1], mat4x4->m[3][2] };
}
