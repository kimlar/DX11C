cbuffer constants : register(b0)
{
    float4x4 modelViewProj;
};

struct VS_Input
{
    float3 pos : POS;
    float2 uv : TEX;
};

struct VS_Output
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

VS_Output vs_main(VS_Input input)
{
    VS_Output output;
    output.pos = mul(float4(input.pos, 1.0f), modelViewProj);
    output.uv = input.uv;
    return output;
}
