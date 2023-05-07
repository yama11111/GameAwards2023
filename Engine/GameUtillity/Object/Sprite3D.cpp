#include "Sprite3D.h"
#include <cassert>

#pragma region 名前空間

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

#pragma region ルートパラメータ番号

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
	// スプライト生成
	unique_ptr<Sprite3D> newSprite = std::make_unique<Sprite3D>();


	// 初期化
	newSprite->vt_.Initialize({ {} });

	// テクスチャ番号
	newSprite->pTex_ = pTex;

	// 描画する
	newSprite->isInvisible_ = false;


	// ポインタを獲得
	Sprite3D* newSpritePtr = newSprite.get();

	// スプライトを保存
	sprites_.push_back(std::move(newSprite));

	// スプライトポインタを返す
	return newSpritePtr;
}

void Sprite3D::AllClear()
{
	// スプライト3D全消去
	for (size_t i = 0; i < sprites_.size(); i++)
	{
		sprites_[i].reset(nullptr);
	}
	sprites_.clear();
}

void Sprite3D::SetDrawCommand(Sprite3DObject* pObj, const DrawLocation& location)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pSprite3D_ = this;
	newDrawSet->pObj_ = pObj;

	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(newDrawSet, location);
}

#pragma endregion

#pragma region Pipeline

void Sprite3D::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pSprite3D_->isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex);

	// テクスチャ
	pSprite3D_->pTex_->SetDrawCommand(TexIndex);

	// 頂点バッファを送る + 描画コマンド
	pSprite3D_->vt_.Draw();
}

void Sprite3D::Pipeline::ShaderSet::Load()
{
	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* gs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// ジオメトリシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DGS.hlsl", "main", "gs_5_0", gs, errorBlob.Get());
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/Sprite3DPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	gsBlob_ = gs;
	psBlob_ = ps;
}

void Sprite3D::Pipeline::StaticInitialize()
{
	// 描画場所の数だけ
	for (size_t i = 0; i < sDrawSets_.size(); i++)
	{
		// 変換
		DrawLocation location = static_cast<DrawLocation>(i);

		// クリア
		StaticClearDrawSet(location);
	}


	// パイプライン初期化用設定
	PipelineSet::InitStatus initStatus;


#pragma region シェーダー読み込み

	ShaderSet shdrs;
	shdrs.Load();

#pragma endregion


#pragma region 頂点レイアウトの設定

	initStatus.inputLayout_ =
	{
		// 頂点座標	 (x, y, z)
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

#pragma endregion


#pragma region テクスチャサンプラーの設定

	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 横折り返し   (タイリング)
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 縦折り返し   (タイリング)
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP; // 奥行折り返し (タイリング)
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK; // ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;   // 全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX; // ミニマップ最大値
	samplerDesc.MinLOD = 0.0f;              // ミニマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL; // ピクセルシェーダーからのみ使用可能

	initStatus.samplerDescs_.push_back(samplerDesc);

#pragma endregion


#pragma region ルートパラメータの設定

	size_t rpIdxCBNum = static_cast<size_t> (RootParameterIndex::TexDT);

	for (size_t i = 0; i < rpIdxCBNum; i++)
	{
		// 定数バッファ
		D3D12_ROOT_PARAMETER rootParam{};
		rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;  // 定数バッファビュー
		rootParam.Descriptor.ShaderRegister = static_cast<UINT>(i); // 定数バッファ番号
		rootParam.Descriptor.RegisterSpace = 0;					  // デフォルト値
		rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

		initStatus.rootParams_.push_back(rootParam);
	}

	// デスクリプタレンジの設定
	initStatus.descriptorRange_.NumDescriptors = 1; // 1度の描画に使うテクスチャが1枚なので1
	initStatus.descriptorRange_.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	initStatus.descriptorRange_.BaseShaderRegister = 0; // テクスチャレジスタ0番
	initStatus.descriptorRange_.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// テクスチャレジスタ
	D3D12_ROOT_PARAMETER rootParam{};
	rootParam.ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParam.DescriptorTable.pDescriptorRanges = &initStatus.descriptorRange_;
	rootParam.DescriptorTable.NumDescriptorRanges = 1;
	rootParam.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL; // 全てのシェーダから見える

	initStatus.rootParams_.push_back(rootParam);

#pragma endregion


#pragma region パイプライン設定

	// シェーダーの設定
	initStatus.pipelineDesc_.VS.pShaderBytecode = shdrs.vsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.VS.BytecodeLength = shdrs.vsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.GS.pShaderBytecode = shdrs.gsBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.GS.BytecodeLength = shdrs.gsBlob_.Get()->GetBufferSize();
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

	// ラスタライザの設定
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_NONE; // 背面をカリングしない

	// デプスステンシルステートの設定
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = false; // 深度テストしない
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書き

	// 図形の形状設定
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;

	// 画像の透過適用
	//initStatus.pipelineDesc_.BlendState.AlphaToCoverageEnable = true;

#pragma endregion


#pragma region プリミティブ形状の設定

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_POINTLIST; // ポイントリスト

#pragma endregion


	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプライン初期化
		sPipelineSets_[i].Initialize(initStatus);
	}
}

void Sprite3D::Pipeline::StaticClearDrawSet(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// あるなら
	if (sDrawSets_[index].empty() == false)
	{
		// クリア
		sDrawSets_[index].clear();
	}
}

void Sprite3D::Pipeline::StaticPushBackDrawSet(unique_ptr<DrawSet>& drawSet, const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// 挿入
	sDrawSets_[index].push_back(std::move(drawSet));
}

void Sprite3D::Pipeline::StaticDraw(const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// パイプラインをセット
	sPipelineSets_[index].SetDrawCommand();

	// モデル描画
	for (std::unique_ptr<DrawSet>& drawSet : sDrawSets_[index])
	{
		drawSet->Draw();
	}
}

#pragma endregion