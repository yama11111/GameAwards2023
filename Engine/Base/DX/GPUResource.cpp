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
		&state.heapProp_, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&state.resDesc_, // リソース設定
		state.resState_,
		state.pClearValue_, 
		IID_PPV_ARGS(&buffer_)));
}
