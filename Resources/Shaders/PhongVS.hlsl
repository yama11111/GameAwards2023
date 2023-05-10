#include "Model.hlsli"

PSInput main(VSInput input)
{
	// 法線にワールド行列によるスケーリング、回転を適用
	float4 wNormal = normalize(mul(matWorld, float4(input.normal, 0)));
	float4 wPos = mul(matWorld, input.pos);


	// ピクセルシェーダーに渡す値
	PSInput output;


	// システム頂点
	output.svPos = mul(mul(matViewProj, matWorld), input.pos);

	// ワールド座標
	output.worldPos = wPos;

	// 法線ベクトル
	output.normal = wNormal.xyz;

	// UV座標
	output.uv = input.uv;

	// 頂点から視点への方向ベクトル
	output.eyeDir = normalize(cameraPos - wPos.xyz);


	return output;
}