#include "Sprite3D.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(PSInput input) : SV_TARGET
{
	// テクスチャ色
	//float4 texColor = tex.Sample(smp, input.uv * tiling + offset) * texColorRate;
	float4 texColor = tex.Sample(smp, input.uv);

	// 計算した色で描画
	return texColor * color;
}