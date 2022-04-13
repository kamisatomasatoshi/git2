#include "PostEffectTest.hlsli"


Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 1番スロットに設定されたテクスチャ
Texture2D<float4> tex2 : register(t2);  // 1番スロットに設定されたテクスチャ

SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float4 color = {0,0,0,0};
	float w = 1280.0f;
	float h = 720.0f;
	float4 ret1 = float4(0, 0, 0, 0);
	float maxpixel = 2.0f;
	float dx = maxpixel / w;
	float dy = maxpixel / h;
	
	float4 ret = float4(0, 0, 0, 0);
	float2 v = float2(3.0f, 3.0f);

	//色反転　左上
	/*if (input.uv.x < 0.35 && input.uv.y < 0.35) {
		float4 change = tex0.Sample(smp, input.uv * v);
		change = 1.0f - change;
		return float4(change.rgb,1);
	}
	*/
	//for文平均ぼかし　左下
	for (int x = 0; x < maxpixel; x++)
	{
		for (int y = 0; y < maxpixel; y++)
		{
			ret += tex0.Sample(smp, (input.uv + float2(x * dx, y * dy)));
		}
	}
	color = ret / (maxpixel * maxpixel);
	
	return float4(color.rgb, 0.2);


	/*float2 nmTex = effect.Sample(smp, input.uv).xy;
	nmTex = nmTex * 2.0f - 1.0f;
	float4 texcolor0 = tex0.Sample(smp, input.uv + nmTex * 0.1f);
	*/
}
