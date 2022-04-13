#include "PostEffectTest.hlsli"
Texture2D<float4> tex0 : register(t0);  // 0番スロットに設定されたテクスチャ
Texture2D<float4> tex1 : register(t1);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(VSOutput input) : SV_TARGET
{
	float shiftWidth = shift;

	/*float4 color = tex0.Sample(smp, input.uv);
	color.rgb = float3(0, color.g, color.b);*/
	float4 color = float4(0, 0, 0, 1);
	color+= tex0.Sample(smp, input.uv+float2(-shiftWidth, -shiftWidth));
	color+= tex0.Sample(smp, input.uv+float2(0, -shiftWidth));
	color+= tex0.Sample(smp, input.uv+float2(shiftWidth, -shiftWidth));
	color+= tex0.Sample(smp, input.uv+float2(-shiftWidth, 0));
	color+= tex0.Sample(smp, input.uv+float2(0, 0));
	color+= tex0.Sample(smp, input.uv+float2(shiftWidth, 0));
	color+= tex0.Sample(smp, input.uv+float2(-shiftWidth, shiftWidth));
	color+= tex0.Sample(smp, input.uv+float2(0, shiftWidth));
	color+= tex0.Sample(smp, input.uv+float2(shiftWidth, shiftWidth));

	color.rgb = color.rgb / 9;
	return color;
}