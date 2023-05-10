#include "Model.hlsli"

Texture2D<float4> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���}�b�s���O
	float4 texColor = tex.Sample(smp, input.uv);

	// ���F
	float4 originalColor = texColor * color;


	// ����x
	const float shininess = 4.0f;


	// �����ˌ�
	float3 ambient = originalColor.rgb * mAmbient;

	// �V�F�[�f�B���O�F
	float3 shaderColor = ambientColor * ambient;


	// ���C�g���̌v�Z
	for (int i = 0; i < DireLightNum; i++)
	{
		// ���s����
		if (direLights[i].active)
		{
			// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);

			// �g�U���ˌ�
			float3 diffuse = dotLightNormal * texColor.rgb * color.rgb * mDiffuse;

			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-direLights[i].lightVec + (2.0f * dotLightNormal * input.normal));
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;

			// �S�ĉ��Z
			shaderColor += (ambient + diffuse + specular) * direLights[i].lightColor;
		}
	}

	// �v�Z�����F�ŕ`��
	return float4(shaderColor, texColor.a * mAlpha);
}