#include "GPUResource.h"
#include "YAssert.h"

using YDX::GPUResource;

ID3D12Device* GPUResource::spDevice_ = nullptr;

void GPUResource::StaticInitialize(ID3D12Device* pDevice)
{
	assert(pDevice);
	spDevice_ = pDevice;
}

void GPUResource::Create(const CreateStatus& state)
{
	Result(spDevice_->CreateCommittedResource(
		&state.heapProp_, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&state.resDesc_, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&buffer_)));
}