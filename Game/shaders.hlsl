
Texture2D shaderTexture;
SamplerState SampleType;

struct VOut
{
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
	float4 worldPos : POSITION;
};

cbuffer uniforms
{
	float4x4 MM;
	float4x4 VM;
	float4x4 PM;
	float4x4 NM;
	float4 lightPos;
};

float linearFog(float zPositionInCameraSpace, float minDistance, float maxDistance) {
	float dist = abs(zPositionInCameraSpace);
	float fogFactor = (maxDistance - dist) / (maxDistance - minDistance);
	fogFactor = clamp(fogFactor, 0.0, 1.0);
	return fogFactor;
}

VOut VShader(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
	VOut output;
	position.w = 1.0;
	normal.w = 0.0;

	position = mul(MM, position);
	position = mul(VM, position);
	output.worldPos = position;
	position = mul(PM, position);
	output.position = position;

	output.normal = mul(NM, normal);;
	output.texcoord = texcoord;

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD, float4 worldPos : POSITION) : SV_TARGET
{
	float4 colour = shaderTexture.Sample(SampleType, texcoord);

	if (lightPos.w == 1.0)
	{
		float3 norm = normalize(normal);
		float diff = dot(float4(norm.xyz, 0.0), float4(-worldPos.xyz / worldPos.w, 0.0));

		float fog = linearFog(worldPos.z, 80.0, 100.0);
		colour = lerp(float4(16.0 / 255.0, 151.0 / 255.0, 220.0 / 255.0, 1.0), colour, fog);
		
		colour *= diff;
		colour.a = 1.0;
	}

	return colour;
}