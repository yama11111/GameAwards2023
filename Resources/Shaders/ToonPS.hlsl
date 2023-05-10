#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(PSInput input) : SV_TARGET
{
	// テクスチャマッピング
	float4 texColor = tex.Sample(smp, input.uv);

	// 原色
	float4 baseColor = texColor * color;


	// 光沢度
	const float shininess = 4.0f;

	// 閾値 (限界) 初期値
	const float thresholdStart = 0.4f;

	// 閾値 (限界) 最終値
	const float thresholdEnd = thresholdStart + 0.05f;


	// 平行光源の向き
	float3 direLightVec = normalize(float3(-1.0f, +1.0f, -1.0f));

	// 平行光源の色
	float3 direLightColor = float3(1.0f, 1.0f, 1.0f);


	// ライトに向かうベクトルと法線の計算
	float3 dotLightNormal = dot(direLightVec, input.normal);


	// 環境反射光
	float3 ambient = baseColor.rgb * mAmbient * ambientColor;


	// ライトに向かうベクトルと法線の内積をクランプ
	float3 intensity = saturate(dotLightNormal);

	// 内積にスムースステップを適応
	intensity = smoothstep(thresholdStart, thresholdEnd, intensity);

	// 拡散反射光
	float3 diffuse = intensity * baseColor.rgb * mDiffuse;


	// 反射光ベクトル
	float3 reflectDir = normalize(-direLightVec + (2.0f * dotLightNormal * input.normal));

	// 鏡面反射光
	float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;

	// 鏡面反射光にスムースステップを適応
	specular = smoothstep(thresholdStart, thresholdEnd, specular);


	// 全て加算
	float3 shaderColor = (ambient + diffuse + specular) * direLightColor;


	// 計算した色で描画
	return float4(shaderColor, baseColor.a * mAlpha);
}