Texture2D CustomTexture: register(t0);
SamplerState CustomSamplerState;

cbuffer CustomFormat
{
	float3 diffuseColor;
	float paddingDC;
	float3 ambientColor;
	float paddingAC;
	float3 specularColor;
	float shininess;
	int textureBool;
	float padding[3];
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float4 Nor: NORMAL;
	float2 uv : UV;
};

float4 PS_main(VS_OUT input) : SV_Target
{
	float3 diffuseLight;
	float4 lightPosition = float4(0.0, 0.0, -10.0, 0.0);
	float3 lightIntensity = { 1.0, 1.0, 1.0 };

	float4 lightDir = normalize(lightPosition - input.WPos);

	float3 diffuseMap = CustomTexture.Sample(CustomSamplerState, input.uv).xyz;
	
	input.Nor = normalize(input.Nor);

	if(textureBool == true)
		diffuseLight = diffuseMap * diffuseColor * max(dot(lightDir, input.Nor), 0.0f);
	else if(textureBool == false)
		diffuseLight = diffuseColor * max(dot(lightDir, input.Nor), 0.0f);

	float4 color = float4((lightIntensity * diffuseLight), 1.0f);

	return color;
};