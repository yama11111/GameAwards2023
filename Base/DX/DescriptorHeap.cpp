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
	// �J�E���g������
	srvCount_ = uavCount_ = cbvCount_ = 0;

	// �f�X�N���v�^�q�[�v�ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; // �V�F�[�_�[���猩����悤��
	heapDesc.NumDescriptors = MaxSRVCount_  + MaxUAVCount_ + MaxCBVCount_;

	// �ݒ�����ƂɃf�X�N���v�^�q�[�v(SRV,UAV,CBV�p)�𐶐�
	Result(pDevice_->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));

	// �C���N�������g�T�C�Y�擾
	incSize_ = pDevice_->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

DescriptorHeap::Handle DescriptorHeap::CreateSRV(ID3D12Resource* buff, const D3D12_SHADER_RESOURCE_VIEW_DESC& srvDesc)
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(srvCount_ < MaxSRVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);

	// �n���h���̎w���ʒu��SRV�쐬
	pDevice_->CreateShaderResourceView(buff, &srvDesc, handle.cpu_);

	// �J�E���g��i�߂�
	srvCount_++;

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateUAV(ID3D12Resource* buff, const D3D12_UNORDERED_ACCESS_VIEW_DESC& uavDesc)
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(uavCount_ < MaxUAVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// UAV + �ő�SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));

	// �n���h���̎w���ʒu��UAV�쐬
	pDevice_->CreateUnorderedAccessView(buff, nullptr, &uavDesc, handle.cpu_);

	// �J�E���g��i�߂�
	uavCount_++;

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle DescriptorHeap::CreateCBV(const D3D12_CONSTANT_BUFFER_VIEW_DESC& cbvDesc)
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(cbvCount_ < MaxCBVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// CBV + �ő�SRV + �ő�UAV �����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// �n���h���̎w���ʒu��CBV�쐬
	pDevice_->CreateConstantBufferView(&cbvDesc, handle.cpu_);

	// �J�E���g��i�߂�
	cbvCount_++;

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddSRV()
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(srvCount_ < MaxSRVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * srvCount_);

	// �J�E���g��i�߂�
	srvCount_++;

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddUAV()
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(uavCount_ < MaxUAVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// UAV + �ő�SRV�����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (uavCount_ + MaxSRVCount_));

	// �J�E���g��i�߂�
	uavCount_++;

	// �n���h����Ԃ�
	return handle;
}

DescriptorHeap::Handle YDX::DescriptorHeap::AddCBV()
{
	// �J�E���g���ő�l�𒴂�����e��
	assert(cbvCount_ < MaxCBVCount_);

	// �߂�l�p�n���h��
	Handle handle{};

	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(CPU)���擾
	handle.cpu_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// �f�X�N���v�^�[�q�[�v�̐擪�n���h��(GPU)���擾
	handle.gpu_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();

	// CBV + �ő�SRV + �ő�UAV �����镪�����n���h����i�߂�
	handle.cpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));
	handle.gpu_.ptr += static_cast<SIZE_T>(incSize_ * (cbvCount_ + MaxSRVCount_ + MaxUAVCount_));

	// �J�E���g��i�߂�
	cbvCount_++;

	// �n���h����Ԃ�
	return handle;
}

void DescriptorHeap::SetDrawCommand()
{
	// SRV�q�[�v�̐ݒ�R�}���h
	ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap_.Get() };
	pCommandList_->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}
