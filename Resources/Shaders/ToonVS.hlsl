#include "Model.hlsli"

PSInput main(VSInput input)
{
	// �@���Ƀ��[���h�s��ɂ��X�P�[�����O�A��]��K�p
	float4 wNormal = normalize(mul(matWorld, float4(input.normal, 0)));
	float4 wPos = mul(matWorld, input.pos);


	// �s�N�Z���V�F�[�_�[�ɓn���l
	PSInput output;


	// �V�X�e�����_
	output.svPos = mul(mul(matViewProj, matWorld), input.pos);

	// ���[���h���W
	output.worldPos = wPos;

	// �@���x�N�g��
	output.normal = wNormal.xyz;

	// UV���W
	output.uv = input.uv;

	// ���_���王�_�ւ̕����x�N�g��
	output.eyeDir = normalize(cameraPos - wPos.xyz);


	return output;
}