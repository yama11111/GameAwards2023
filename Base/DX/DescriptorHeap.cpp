#include "DescriptorHeap.h"
#include "YAssert.h"

using YDX::DescriptorHeap;

ID3D12Device* DescriptorHeap::pDevice_ = nullptr;
ID3D12GraphicsCommandList* DescriptorHeap::pCommandList_ = nullptr;

void DescriptorHeap::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pDevice_);
	assert(state.pCommandList_);

	pDevice_  = state.pDevice_;
	pCommandList_ = state.pCommandList_;
}

void DescriptorHeap::Initialize()
{
	// カウント初期化
	srvCount_ = uavCount_ = cbvCount_ = 0;

	// デスクリプタヒープ設定
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // シェーダーから見えるように
	heapDesc.NumDescriptors = MaxSRVCount_  + MaxUAVCount_ + MaxCBVCount_;

	// 設定をもとにデスクリプタヒープ(SRV,UAV,CBV用)を生成
	Result(pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));

	// インクリメントサイズ取得
	incSize_ = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

DescriptorHeap::Handle DescriptorHeap::CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	// カウントが最大値を超えたら弾く
	assert(srvCount_ < MaxSRVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);

	// ハンドルの指す位置にSRV作成
	pDevice_->CreateShaderResourceView(buff, &srvDesc, handle.cpu_);

	// カウントを進める
	srvCount_++;

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc)
{
	// カウントが最大値を超えたら弾く
	assert(uavCount_ < MaxUAVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// UAV + 最大SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));

	// ハンドルの指す位置にUAV作成
	pDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, handle.cpu_);

	// カウントを進める
	uavCount_++;

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc)
{
	// カウントが最大値を超えたら弾く
	assert(cbvCount_ < MaxCBVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// CBV + 最大SRV + 最大UAV がある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// ハンドルの指す位置にCBV作成
	pDevice_->CreateConstantBufferView(&cbvDesc, handle.cpu_);

	// カウントを進める
	cbvCount_++;

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddSRV()
{
	// カウントが最大値を超えたら弾く
	assert(srvCount_ < MaxSRVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);

	// カウントを進める
	srvCount_++;

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddUAV()
{
	// カウントが最大値を超えたら弾く
	assert(uavCount_ < MaxUAVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// UAV + 最大SRVがある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));

	// カウントを進める
	uavCount_++;

	// ハンドルを返す
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddCBV()
{
	// カウントが最大値を超えたら弾く
	assert(cbvCount_ < MaxCBVCount_);

	// 戻り値用ハンドル
	Handle handle{};

	// デスクリプターヒープの先頭ハンドル(CPU)を取得
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// デスクリプターヒープの先頭ハンドル(GPU)を取得
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// CBV + 最大SRV + 最大UAV がある分だけハンドルを進める
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// カウントを進める
	cbvCount_++;

	// ハンドルを返す
	return handle;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRVヒープの設定コマンド
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}
