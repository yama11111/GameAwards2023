#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(PSInput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv);

	// 原色
	float4 originalColor = texColor * color;


	// 光沢度
	const float shininess = 4.0f;


	// 環境反射光
	float3 ambient = originalColor.rgb * mAmbient;

	// シェーディング色
	float3 shaderColor = ambientColor * ambient;


	// ライト毎の計算
	for (int i = 0; i < DireLightNum; i++)
	{
		// 平行光源
		if (direLights[i].active)
		{
			// ライトに向かうベクトルと法線の計算
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);

			// 拡散反射光
			float3 diffuse = dotLightNormal * texColor.rgb * color.rgb * mDiffuse;

			// 反射光ベクトル
			float3 reflectDir = normalize(-direLights[i].lightVec + (2.0f * dotLightNormal * input.normal));
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;

			// 全て加算
			shaderColor += (ambient + diffuse + specular) * direLights[i].lightColor;
		}
	}

	// 計算した色で描画
	return float4(shaderColor, texColor.a * mAlpha);
}