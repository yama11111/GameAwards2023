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


	// �����ˌ�
	float3 ambient = baseColor.rgb * mAmbient * ambientColor;

	// �V�F�[�f�B���O�F
	float3 shaderColor = ambient;


	// ���C�g���̌v�Z
	for (int i = 0; i < DireLightNum; i++)
	{
		// ���s����
		if (direLights[i].active)
		{
			// ���C�g�Ɍ������x�N�g���Ɩ@���̌v�Z
			float3 dotLightNormal = dot(direLights[i].lightVec, input.normal);


			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * baseColor.rgb * mDiffuse;


			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-direLights[i].lightVec + (2.0f * dotLightNormal * input.normal));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;


			// �S�ĉ��Z
			shaderColor += (diffuse + specular) * direLights[i].lightColor;
		}
	}
	for (int j = 0; j < PointLightNum; j++)
	{
		// �_����
		if (pointLights[j].active)
		{
			// ���C�g�̃x�N�g��
			float3 lightVec = normalize(pointLights[j].lightPos - input.worldPos.xyz);
			
			// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
			float3 dotLightNormal = dot(lightVec, input.normal);
			

			// ���C�g�Ɍ������x�N�g���Ɩ@���̓��ς��N�����v
			float3 intensity = saturate(dotLightNormal);

			// �g�U���ˌ�
			float3 diffuse = intensity * baseColor.rgb * mDiffuse;
			

			// ���ˌ��x�N�g��
			float3 reflectDir = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
			
			// ���ʔ��ˌ�
			float3 specular = pow(saturate(dot(reflectDir, input.eyeDir)), shininess) * mSpecular;
			

			// �x�N�g���̒���
			float d = length(lightVec);

			// ���������W��
			float atten = 1.0f /
				((pointLights[j].lightAtten.x) +
					(pointLights[j].lightAtten.y * d) +
					(pointLights[j].lightAtten.z * d * d));

			// �S�ĉ��Z
			shaderColor += atten * (diffuse + specular) * pointLights[j].lightColor;
		}
	}
	for (int k = 0; k < SpotLightNum; k++)
	{
	//	// �X�|�b�g���C�g����
	//	if (spotLights[k].active)
	//	{
	//		// ���C�g�̃x�N�g��
	//		float3 lightVec = spotLights[k].lightPos - input.worldPos.xyz;
	//		// �x�N�g���̒���
	//		float d = length(lightVec);
	//		// ���K��
	//		lightVec = normalize(lightVec);
	//		// ���������W��
	//		float atten = 1.0f / (spotLights[k].lightAtten.x + (spotLights[k].lightAtten.y * d) + (spotLights[k].lightAtten.z * d * d));
	//		// �p�x����
	//		float cos = dot(lightVec, spotLights[k].lightVec);
	//		// �J�n�p�x���I���p�x�Ɍ��� (�J�n���� : 1�{, �I���O�� : 0�{ �̋P�x)
	//		float angleAtten = smoothstep(spotLights[k].lightEndFactorAngleCos, spotLights[k].lightStartFactorAngleCos, cos);
	//		// �p�x��������Z
	//		atten *= angleAtten;
	//		// ���C�g�Ɍ������x�N�g���Ɩ@���̓���
	//		float3 dotLightNormal = dot(lightVec, input.normal);
	//		// ���ˌ��x�N�g��
	//		float3 reflect = normalize(-lightVec + (2.0f * dotLightNormal * input.normal));
	//		// �g�U���ˌ�
	//		float3 diffuse = dotLightNormal * mDiffuse;
	//		// ���ʔ��ˌ�
	//		float3 specular = pow(saturate(dot(reflect, eyeDir)), shininess) * mSpecular;

	//		// �S�ĉ��Z
	//		shaderColor += atten * (diffuse + specular) * pointLights[k].lightColor;
	//	}
	}

	// �v�Z�����F�ŕ`��
	return float4(shaderColor, baseColor.a * mAlpha);
}