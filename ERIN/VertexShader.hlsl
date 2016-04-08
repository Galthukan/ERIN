struct VS_IN
{
	float3 Pos : POSITION;
	float3 Color : COLOR;

};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float3 Color : COLOR;
};

cbuffer MATRICES:register(b0)
{
	matrix worldViewProj;
	matrix world;
	matrix view;
	matrix projection;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = mul(float4(input.Pos, 1), worldViewProj);
	output.WPos = mul(float4(input.Pos, 1), world);
	output.Color = input.Color;

	return output;

}