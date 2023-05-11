#pragma once
#include <d3d12.h>
#include <wrl.h>

#pragma comment(lib, "d3d12.lib")

namespace YDX
{
	class GPUResource
	{
	private:
		// �o�b�t�@
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer_ = nullptr;
	public:
		// �����p�X�e�[�^�X
		struct CreateStatus
		{
			// �o�b�t�@�ݒ�
			D3D12_HEAP_PROPERTIES heapProp_{};
			// ���\�[�X�ݒ�
			D3D12_RESOURCE_DESC resDesc_{};
			// ���\�[�X�X�e�[�g
			D3D12_RESOURCE_STATES resState_ = D3D12_RESOURCE_STATE_GENERIC_READ;
		};
	public:
		// ����
		void Create(const CreateStatus& state);
	public:
		// �o�b�t�@�|�C���^
		ID3D12Resource* Get() { return buffer_.Get(); }
	private:
		// �ÓI�f�o�C�X�|�C���^
		static ID3D12Device* spDevice_;
	public:
		// �ÓI�����o������
		static void StaticInitialize(ID3D12Device* pDevice);
	};
}