#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")
namespace YDX
{
	class DescriptorHeap
	{
	private:
		// �f�X�N���v�^�[�q�[�v
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
		// �C���N�������g�p
		UINT incSize_ = 0;
	private:
		// SRV ��
		UINT srvCount_ = 0;
		// UAV ��
		UINT uavCount_ = 0;
		// CBV ��
		UINT cbvCount_ = 0;
	public:
		// �n���h�� (CPU, GPU)
		struct Handle
		{
			D3D12_CPU_DESCRIPTOR_HANDLE cpu_; // CPU
			D3D12_GPU_DESCRIPTOR_HANDLE gpu_; // GPU
		};
	public:
		// ������
		void Initialize();
		// �`��O�R�}���h (�ŏ��Ɉ��)
		void SetDrawCommand();
	public:
		// SRV ����
		Handle CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc);
		// UAV ����
		Handle CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc);
		// CBV ����
		Handle CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc);
	public:
		// SRV �ǉ�
		Handle AddSRV();
		// UAV �ǉ�
		Handle AddUAV();
		// CBV �ǉ�
		Handle AddCBV();
	public:
		// �|�C���^�擾
		ID3D12DescriptorHeap* Get() { return descriptorHeap_.Get(); }
	private:
		// �ő� SRV ��
		static const UINT MaxSRVCount_ = 262144;
		// �ő� UAV ��
		static const UINT MaxUAVCount_ = 262144;
		// �ő� CBV ��
		static const UINT MaxCBVCount_ = 262144;
	private:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* pDevice_;
		// �ÓI�R�}���h���X�g�|�C���^
		static ID3D12GraphicsCommandList* pCommandList_;
	public:
		// �ÓI�������ݒ�
		struct StaticInitStatus
		{
			ID3D12Device* pDevice_;
			ID3D12GraphicsCommandList* pCommandList_;
		};
	public:
		// �ÓI������
		static void StaticInitialize(const StaticInitStatus& state);
	};
}
