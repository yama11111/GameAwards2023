#include "PostEffect.hlsli"

Texture2D<float3> tex : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0);      // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(PSInput input) : SV_TARGET
{
	// �e�N�X�`���F
	//float4 texColor = tex.Sample(smp, input.uv * tiling + offset) * texColorRate;
	float4 texColor = float4(tex.Sample(smp, input.uv), 1.0f) * texColorRate;

	// �v�Z�����F�ŕ`��
	return float4(texColor.xyz, 1.0f) * color;
}