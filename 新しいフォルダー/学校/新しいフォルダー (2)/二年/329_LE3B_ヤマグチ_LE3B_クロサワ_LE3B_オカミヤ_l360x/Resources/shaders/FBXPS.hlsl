#include "FBX.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

//π
static const float PI = 3.141592654f;
//反射点の法線ベクトル
static float3 N;

float SchlickFresnel(float f0, float f90, float cosine)
{
	float m = saturate(1 - cosine);
	float m2 = m * m;
	float m5 = m2 * m2 * m;
	return lerp(f0, f90, m5);
}
float3 DisneyFresnel(float LdotH)
{
	float luminance = 0.3f * baseColor.r + 0.6 * baseColor.g + 0.1f * baseColor.b;

	float3 tintColor = baseColor / luminance;

	float3 nonMetalColor = specular * 0.08f * tintColor;

	float3 specularColor = lerp(nonMetalColor, baseColor, metalness);

	return SchlickFresnel(specularColor, float3(1, 1, 1), LdotH);
}

float GeometricSmith(float cosine)
{
	float k = (roughness + 1.0f);
	
	k = k * k / 8.0f;

	return cosine / (cosine * (1.0f - k) + k);
}

float DistributionGGX(float alphe,float NdotH)
{
	float alphe2 = alphe * alphe;
	float t = NdotH * NdotH * (alphe2 - 1.0f) + 1.0f;
	return alphe2 / (PI * t * t);
}
float3 CookToranceSpecular(float NdotL,float NdotV,float NdotH,float LdotH)
{
	float Ds = DistributionGGX(roughness * roughness, NdotH);

	float3 Fs = DisneyFresnel(LdotH);

	float Gs = GeometricSmith(NdotL) * GeometricSmith(NdotV);

	float m = 4.0f * NdotL * NdotV;

	return Ds * Fs * Gs / m;
}
float3 BRDF(float3 L, float3 V)
{
	float3 H = normalize(L + V);
	
	float NdotH = dot(N, H);
	
	float LdotH = dot(L, H);
	
	float NdotL = dot(N, L);

	float NdotV = dot(N, V);

	if (NdotL < 0 || NdotV < 0) {
		return float3(0, 0, 0); 
	}

	float diffuseReflectance = 1.0f / PI;

	float energyBias = 0.5f * roughness;

	float Fd90 = energyBias + 2 * LdotH * LdotH * roughness;

	float FL = SchlickFresnel(1.0f, Fd90, NdotL);

	float FV = SchlickFresnel(1.0f, Fd90, NdotV);

	float energyFactory = lerp(1.0f, 1.0f / 1.51f, roughness);

	float Fd = FL * FV;
										//NdotLを変更
	float3 diffuseColor = diffuseReflectance * Fd* baseColor * (1 - metalness);

	float3 specularColor = CookToranceSpecular(NdotL, NdotV, NdotH, LdotH);

	return diffuseColor+ specularColor;
}

struct PSOutput
{
	float4 target0:SV_TARGET0;
	float4 target1:SV_TARGET1;
	float4 target2:SV_TARGET2;
};

struct PSInput
{
	float4 target0:SV_TARGET0;
	float4 target1:SV_TARGET1;
	float4 target2:SV_TARGET2;
};
PSInput main(VSOutput input) : SV_TARGET
{
	PSOutput output;
	// テクスチャマッピング
	float4 texcolor = tex.Sample(smp, input.uv);
	// Lambert反射
	float3 light = normalize(float3(1,-1,1)); // 右下奥　向きのライト
	float diffuse = saturate(dot(-light, input.normal));
	float brightness = diffuse + 0.3f;
	float4 shadecolor = float4(brightness, brightness, brightness, 1.0f);
	// 陰影とテクスチャの色を合成
	output.target0 = shadecolor * texcolor;
	//output.target1 = float4(1 - (shadecolor * texcolor).rgb, 1);
	output.target1 = shadecolor * texcolor;
	output.target2 = shadecolor * texcolor;

	//return float4(ambientLightColor, 1);
	//return float4(baseColor, 1);
	//return output;
	PSInput psinput;

	N = input.normal;
	float3 finalRGB = float3(0, 0, 0);
	float3 eyedir = normalize(cameraPos - input.worldpos.xyz);

	for (int i = 0; i < DIRLIGHT_NUM; i++)
	{
		if (!dirLight[i].activ)
		{
			continue;
		}
		finalRGB += BRDF(dirLight[i].lightv, eyedir) * dirLight[i].lightcolor;
	}
	//return float4(finalRGB, 1);
	psinput.target0= float4(finalRGB, 1);
	psinput.target1 = float4(finalRGB, 1);
	psinput.target2 = float4(finalRGB, 1);

	return psinput;
}