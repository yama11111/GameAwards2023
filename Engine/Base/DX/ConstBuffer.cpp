#include "ConstBuffer.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Model.h"
#include "LightGroup.h"
#include "Color.h"
#include "Material.h"
#include "YAssert.h"

using YDX::ConstBufferCommon;

ID3D12GraphicsCommandList* ConstBufferCommon::spCmdList_ = nullptr;
YDX::DescriptorHeap* ConstBufferCommon::spDescHeap_ = nullptr;

void ConstBufferCommon::StaticInitialize(ID3D12GraphicsCommandList* pCmdList, DescriptorHeap* pDescHeap)
{
	assert(pCmdList);
	assert(pDescHeap);

	spCmdList_ = pCmdList;
	spDescHeap_ = pDescHeap;
}

using YDX::ConstBuffer;

template<typename T>
void ConstBuffer<T>::Create(const bool isMutable)
{
	GPUResource::CreateStatus state;
	// ヒープ設定
	state.heapProp_.Type = D3D12_HEAP_TYPE_UPLOAD;
	// リソース設定
	state.resDesc_.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	state.resDesc_.Height = 1;
	state.resDesc_.Width = (sizeof(T) * 0xff) & ~0xff;
	state.resDesc_.DepthOrArraySize = 1;
	state.resDesc_.MipLevels = 1;
	state.resDesc_.SampleDesc.Count = 1;
	state.resDesc_.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 定数バッファの生成
	rsc_.Create(state);

	// 定数バッファのマッピング
	Result(rsc_.Get()->Map(0, nullptr, (void**)&map_));

	// CBV生成
	viewDesc_.BufferLocation = rsc_.Get()->GetGPUVirtualAddress();
	viewDesc_.SizeInBytes = static_cast<UINT>(state.resDesc_.Width);
	spDescHeap_->CreateCBV(viewDesc_, isMutable);
}

template<typename T>
void ConstBuffer<T>::SetDrawCommand(const UINT rootParamIndex)
{
	// 定数バッファビュー(3D変換行列)の設定コマンド
	spCmdList_->SetGraphicsRootConstantBufferView(rootParamIndex, viewDesc_.BufferLocation);
}

template class ConstBuffer<YGame::Sprite2D::Object::CBData>;
template class ConstBuffer<YGame::Sprite3D::Object::CBData>;
template class ConstBuffer<YGame::Model::Object::CBData>;
template class ConstBuffer<YGame::Color::CBData>;
template class ConstBuffer<YGame::LightGroup::CBData>;
template class ConstBuffer<YGame::Material::CBData>;
