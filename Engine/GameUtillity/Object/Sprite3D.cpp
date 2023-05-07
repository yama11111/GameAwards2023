#include "Sprite3D.h"
#include <cassert>

#pragma region ���O���

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::Sprite3DObject;
using YGame::Sprite3D;
using YDX::PipelineSet;
using YMath::Vector3;
using YMath::Matrix4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ���[�g�p�����[�^�ԍ�

static const UINT TraIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::TransformCB); // obj
static const UINT ColIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::ColorCB); // color
static const UINT TexIndex = static_cast<UINT>(Sprite3D::Pipeline::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

std::vector<std::unique_ptr<Sprite3D>> Sprite3D::sprites_{};
array<PipelineSet, DrawLocationNum> Sprite3D::Pipeline::sPipelineSets_{};
array<list<unique_ptr<Sprite3D::Pipeline::DrawSet>>, DrawLocationNum> Sprite3D::Pipeline::sDrawSets_;

#pragma endregion

#pragma region Sprite3D

Sprite3D* Sprite3D::Create(Texture* pTex)
{
	// �X�v���C�g����
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();


	// ������
	newSprite->vt_.Initialize({ {} });

	// �e�N�X�`���ԍ�
	newSprite->pTex_ = pTex;

	// �`�悷��
	newSprite->isInvisible_ = false;


	// �|�C���^���l��
	Sprite3D* newSpritePtr = newSprite.get();

	// �X�v���C�g��ۑ�
	sprites_.push_back(std::move(newSprite));

	// �X�v���C�g�|�C���^��Ԃ�
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// �X�v���C�g3D�S����
	for (size_t i = 0; i < sprites_.size(); i++)
	{
		sprites_[i].reset(nullptr);
	}
	sprites_.clear();
}

void Sprite3D::SetDrawCommand(Sprite3DObject* pObj, const DrawLocation& location)
{
	// �`��Z�b�g����
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// ������
	newDrawSet->pSprite3D_ = this;
	newDrawSet->pObj_ = pObj;

	// �`��Z�b�g�}��
	Pipeline::StaticPushBackDrawSet(newDrawSet, location);
}

#pragma endregion

#pragma region Pipeline

void Sprite3D::Pipeline::DrawSet::Draw()
{
	// �`�悵�Ȃ��Ȃ�e��
	if (pSprite3D_->isInvisible_) { return; }

	// �萔�o�b�t�@���V�F�[�_�[�ɑ���
	pObj_->SetDrawCommand(TraIndex, ColIndex);

	// �e�N�X�`��
	pSprite3D_->pTex_->SetDrawCommand(TexIndex);

	// ���_�o�b�t�@�𑗂� + �`��R�}���h
	pSprite3D_->vt_.Draw();
}

void Sprite3D::Pipeline::ShaderSet::Load()
{
	// �G���[�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* gs = nullptr;
	ID3DBlob* ps = nullptr;

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite3DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// �W�I���g���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite3DGS.hlsl", "main", "gs_5_0", gs, errorBlob.Get());
	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	LoadShader(L"Resources/Shaders/Sprite3DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	gsBlob_ = gs;
	psBlob_ = ps;
}

void Sprite3D::Pipeline::StaticInitialize()
{
	// �`��ꏊ�̐�����
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// �ϊ�
		DrawLocation location = static_cast<DrawLocation>(i);

		// �N���A
		StaticClearDrawSet(location);
	}


	// �p�C�v���C���������p�ݒ�
	PipelineSet::InitStatus initStatus;


#pragma region �V�F�[�_�[�ǂݍ���

	ShaderSet shdrs;
	shdrs.Load();

#pragma endregion


#pragma region ���_���C�A�E�g�̐ݒ�

	initStatus.inputLayout_ =
	{
		// ���_���W	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

#pragma endregion


#pragma region �e�N�X�`���T���v���[�̐ݒ�

	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // �c�܂�Ԃ�   (�^�C�����O)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // ���s�܂�Ԃ� (�^�C�����O)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // �{�[�_�[�̎��͍�
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // �S�ă��j�A���
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // �~�j�}�b�v�ő�l
	samplerDesc.MinLOD = 0.0f;              // �~�j�}�b�v�ŏ��l
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // �s�N�Z���V�F�[�_�[����̂ݎg�p�\

	initStatus.samplerDescs_.push_back(samplerDesc);

#pragma endregion


#pragma region ���[�g�p�����[�^�̐ݒ�

	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// �萔�o�b�t�@
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // �萔�o�b�t�@�r���[
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // �萔�o�b�t�@�ԍ�
		rootParam.Descriptor.RegisterSpace = 0;					  // �f�t�H���g�l
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

		initStatus.rootParams_.push_back(rootParam);
	}

	// �f�X�N���v�^�����W�̐ݒ�
	initStatus.descriptorRange_.NumDescriptors = 1; // 1�x�̕`��Ɏg���e�N�X�`����1���Ȃ̂�1
	initStatus.descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	initStatus.descriptorRange_.BaseShaderRegister = 0; // �e�N�X�`�����W�X�^0��
	initStatus.descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// �e�N�X�`�����W�X�^
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &initStatus.descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // �S�ẴV�F�[�_���猩����

	initStatus.rootParams_.push_back(rootParam);

#pragma endregion


#pragma region �p�C�v���C���ݒ�

	// �V�F�[�_�[�̐ݒ�
	initStatus.pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.GS.pShaderBytecode = shdrs.gsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.GS.BytecodeLength = shdrs.gsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

	// ���X�^���C�U�̐ݒ�
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // �w�ʂ��J�����O���Ȃ�

	// �f�v�X�X�e���V���X�e�[�g�̐ݒ�
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = false; // �[�x�e�X�g���Ȃ�
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // ��ɏ㏑��

	// �}�`�̌`��ݒ�
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	// �摜�̓��ߓK�p
	//initStatus.pipelineDesc_.BlendState.AlphaToCoverageEnable = true;

#pragma endregion


#pragma region �v���~�e�B�u�`��̐ݒ�

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // �|�C���g���X�g

#pragma endregion


	// �p�C�v���C���̐�����
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// �p�C�v���C��������
		sPipelineSets_[i].Initialize(initStatus);
	}
}

void Sprite3D::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// ����Ȃ�
	if (sDrawSets_[index].empty() == false)
	{
		// �N���A
		sDrawSets_[index].clear();
	}
}

void Sprite3D::Pipeline::StaticPushBackDrawSet(unique_ptr<DrawSet>& drawSet, const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �}��
	sDrawSets_[index].push_back(std::move(drawSet));
}

void Sprite3D::Pipeline::StaticDraw(const DrawLocation& location)
{
	// �C���f�b�N�X�ɕϊ�
	size_t index = static_cast<size_t>(location);

	// �p�C�v���C�����Z�b�g
	sPipelineSets_[index].SetDrawCommand();

	// ���f���`��
	for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index])
	{
		drawSet->Draw();
	}
}

#pragma endregion