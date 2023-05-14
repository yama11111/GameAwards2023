#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(PSInput input) : SV_TARGET
{
	// テクスチャマッピング
	//float4 texColor = tex.Sample(smp, input.uv * tiling + offset) * texColorRate;
	float4 texColor = tex.Sample(smp, input.uv);

	// 原色
	float4 baseColor = texColor * color;


	// 光沢度
	const float shininess = 4.0f;


	// 環境反射光
	float3 ambient = baseColor.rgb * mAmbient * ambientColor;

	// シェーディング色
	float3 shaderColor = ambient;


	// ライト毎の計算
	for (int i = 0; i < DireLightNum; i++)
	{
		// 平行光源
		if (direLights[i].active)
		{
			// ライトに向かうベクトルと法線の計算
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);


			// ライトに向かうベクトルと法線の内積をクランプ
			float3 intensity = saturate(dotLightNormal);

			// 拡散反射光
			float3 diffuse = intensity * baseColor.rgb * mDiffuse;


			// 反射光ベクトル
			float3 reflectDir = normalize(-direLights[i].lightVec + (2.0f * dotLightNormal * input.normal));
			
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;


			// 全て加算
			shaderColor += (diffuse + specular) * direLights[i].lightColor;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// 点光源
		if (pointLights[j].active)
		{
			// ライトのベクトル
			float3 lightVec = normalize(pointLights[j].lightPos - input.worldPos.xyz);
			
			// ライトに向かうベクトルと法線の内積
			float3 dotLightNormal = dot(lightVec, input.normal);
			

			// ライトに向かうベクトルと法線の内積をクランプ
			float3 intensity = saturate(dotLightNormal);

			// 拡散反射光
			float3 diffuse = intensity * baseColor.rgb * mDiffuse;
			

			// 反射光ベクトル
			float3 reflectDir = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			
			// 鏡面反射光
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;
			

			// ベクトルの長さ
			float d = length(lightVec);

			// 距離減衰係数
			float atten = 1.0f /
				((pointLights[j].lightAtten.x) +
					(pointLights[j].lightAtten.y * d) +
					(pointLights[j].lightAtten.z * d * d));

			// 全て加算
			shaderColor += atten * (diffuse + specular) * pointLights[j].lightColor;
		}
	}
	for (int k = 0; k < SpotLightNum; k++)
	{
	//	// スポットライト光源
	//	if (spotLights[k].active)
	//	{
	//		// ライトのベクトル
	//		float3 lightVec = spotLights[k].lightPos - input.worldPos.xyz;
	//		// ベクトルの長さ
	//		float d = length(lightVec);
	//		// 正規化
	//		lightVec = normalize(lightVec);
	//		// 距離減衰係数
	//		float atten = 1.0f / (spotLights[k].lightAtten.x + (spotLights[k].lightAtten.y * d) + (spotLights[k].lightAtten.z * d * d));
	//		// 角度減衰
	//		float cos = dot(lightVec, spotLights[k].lightVec);
	//		// 開始角度→終了角度に減衰 (開始内側 : 1倍, 終了外側 : 0倍 の輝度)
	//		float angleAtten = smoothstep(spotLights[k].lightEndFactorAngleCos, spotLights[k].lightStartFactorAngleCos, cos);
	//		// 角度減衰を乗算
	//		atten *= angleAtten;
	//		// ライトに向かうベクトルと法線の内積
	//		float3 dotLightNormal = dot(lightVec, input.normal);
	//		// 反射光ベクトル
	//		float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
	//		// 拡散反射光
	//		float3 diffuse = dotLightNormal * mDiffuse;
	//		// 鏡面反射光
	//		float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;

	//		// 全て加算
	//		shaderColor += atten * (diffuse + specular) * pointLights[k].lightColor;
	//	}
	}

	// 計算した色で描画
	return float4(shaderColor, baseColor.a * mAlpha);
}