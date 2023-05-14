#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	//float4 texColor = tex.Sample(smp, input.uv * tiling + offset) * texColorRate;
	float4 texColor = tex.Sample(smp, input.uv);

	// ���F
	float4 baseColor = texColor * color;


	// ����x
	const float shininess = 4.0f;


	// ���s�����̌���
	float3 direLightVec = normalize(float3(-1.0f, +1.0f, -1.0f));

	// ���s�����̐F
	float3 direLightColor = float3(1.0f, 1.0f, 1.0f);
	

	// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
	float3 dotLightNormal = dot(direLightVec, input.normal);


	// �����ˌ�
	float3 ambient = baseColor.rgb * mAmbient * ambientColor;


	// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
	float3 intensity = saturate(dotLightNormal);

	// �g�U���ˌ�
	float3 diffuse =  intensity * baseColor.rgb * mDiffuse;


	// ���ˌ��x�N�g��
	float3 reflectDir = normalize(-direLightVec + (2.0f * dotLightNormal * input.normal));

	// ���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;


	// �S�ĉ��Z
	float3 shaderColor = (ambient + diffuse + specular) * direLightColor;


	// �v�Z�����F�ŕ`��
	return float4(shaderColor, baseColor.a * mAlpha);
}
