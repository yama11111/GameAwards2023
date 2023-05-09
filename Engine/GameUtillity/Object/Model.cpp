#include "Model.h"
#include "CalcTransform.h"
#include "MathUtillity.h"
#include "FileUtillity.h"
#include <cassert>
#include <fstream>
#include <sstream>

#pragma region 名前空間

using std::array;
using std::vector;
using std::list;
using std::unique_ptr;
using YGame::ModelObject;
using YGame::Model;
using YDX::PipelineSet;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;
using YGame::DrawLocation;
using YGame::DrawLocationNum;

#pragma endregion

#pragma region ルートパラメータ番号

static const UINT TraIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::TransformCB); // transform
static const UINT ColIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::ColorCB); // color
static const UINT LigIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::LightCB); // light
static const UINT MateIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::MaterialCB); // material
static const UINT TexIndex = static_cast<UINT>(Model::Pipeline::RootParameterIndex::TexDT); // tex

#pragma endregion

#pragma region Static

vector<unique_ptr<Model>> Model::models_{};
array<PipelineSet, DrawLocationNum> Model::Pipeline::sPipelineSets_{};
array<list<unique_ptr<Model::Pipeline::DrawSet>>, DrawLocationNum> Model::Pipeline::sDrawSets_;
FbxManager* Model::FbxLoader::sFbxMan_ = nullptr;
FbxImporter* Model::FbxLoader::sFbxImp_ = nullptr;

#pragma endregion

#pragma region Model

Model* Model::CreateCube()
{
	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// メッシュロード
	newMesh.reset(Mesh::CreateCube());

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::CreateCube(const std::string& texFileName)
{
	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// メッシュロード
	newMesh.reset(Mesh::CreateCube(texFileName));

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::LoadObj(const std::string& modelFileName, const bool isSmoothing)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < models_.size(); i++)
	{
		// ファイルパス が同じなら
		if (modelFileName == models_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return models_[i].get();
		}
	}

	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;
	
	// ディレクトリパス (モデルのファイル名と同じフォルダから)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";
	
	// FBXファイル名
	std::string objFileName = modelFileName + ".obj";
	objFileName = YUtil::FilePath(objFileName);
	

	// メッシュロード
	newMesh.reset(Mesh::LoadObj(directoryPath, objFileName, isSmoothing));

	// 追加
	newModel->meshes_.push_back(std::move(newMesh));

	// ファイル名代入
	newModel->fileName_ = modelFileName;


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

Model* Model::LoadFbx(const std::string& modelFileName, const bool isSmoothing)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < models_.size(); i++)
	{
		// ファイルパス が同じなら
		if (modelFileName == models_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return models_[i].get();
		}
	}

	// モデル生成
	unique_ptr<Model> newModel = std::make_unique<Model>();


	// メッシュ生成
	std::unique_ptr<Mesh> newMesh;

	// ディレクトリパス (モデルのファイル名と同じフォルダから)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// FBXファイル名
	std::string fbxFileName = modelFileName + ".fbx";

	//フルパス
	std::string fullPath = directoryPath + fbxFileName;

	// ファイル名代入
	newModel->fileName_ = modelFileName;

	// ファイル名を指定してFBXファイル読み込み
	assert(FbxLoader::sFbxImp_->Initialize(fullPath.c_str(), -1, FbxLoader::sFbxMan_->GetIOSettings()));


	// シーン生成
	FbxScene* fbxScene = FbxScene::Create(FbxLoader::sFbxMan_, "fbxScene");

	// ファイルからロードしたFBX情報をインポート
	FbxLoader::sFbxImp_->Import(fbxScene);


	// FBXノードの数
	int nodeCount = fbxScene->GetNodeCount();

	// 必要分のメモリ確保 (アドレスのずれを予防)
	newModel->nodes_.reserve(nodeCount);

	// ルートノードから順に解析してモデルに流し込む
	FbxLoader::ParseNodeRecursive(newModel.get(), fbxScene->GetRootNode(), isSmoothing);


	// FBXシーン開放
	fbxScene->Destroy();


	// ポインタを獲得
	Model* newModelPtr = newModel.get();

	// モデルを保存
	models_.push_back(std::move(newModel));

	// モデルポインタを返す
	return newModelPtr;
}

void Model::AllClear()
{
	// モデル全消去
	for (size_t i = 0; i < models_.size(); i++)
	{
		models_[i].reset(nullptr);
	}
	models_.clear();
}

void Model::SetDrawCommand(ModelObject* pObj, const DrawLocation& location)
{
	// 描画セット生成
	unique_ptr<Pipeline::DrawSet> newDrawSet = std::make_unique<Pipeline::DrawSet>();

	// 初期化
	newDrawSet->pModel_ = this;
	newDrawSet->pObj_ = pObj;

	// 描画セット挿入
	Pipeline::StaticPushBackDrawSet(newDrawSet, location);
}

#pragma endregion


#pragma region FbxLoader

void Model::FbxLoader::StaticInitialize()
{
	// 再初期化チェック
	assert(sFbxMan_ == nullptr);

	// FBXマネージャーの生成
	sFbxMan_ = FbxManager::Create();

	// FBXマネージャーの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(sFbxMan_, IOSROOT);
	sFbxMan_->SetIOSettings(ios);

	// FBXインポーターの生成
	sFbxImp_ = FbxImporter::Create(sFbxMan_, "");
}

void Model::FbxLoader::StaticFinalize()
{
	// 各種FBXインスタンス破棄
	sFbxImp_->Destroy();
	sFbxMan_->Destroy();
}

void Model::FbxLoader::ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent)
{
	// ノード生成
	std::unique_ptr<Node> newNode = std::make_unique<Node>();


	// ノード名
	newNode->name_ = fbxNode->GetName();


	// FBXノードのローカル情報
	FbxDouble3 fbxPos = fbxNode->LclTranslation.Get();
	FbxDouble3 fbxRot = fbxNode->LclRotation.Get();
	FbxDouble3 fbxScale = fbxNode->LclScaling.Get();

	// 変換
	Vector3 pos = { static_cast<float>(fbxPos[0]), static_cast<float>(fbxPos[1]), static_cast<float>(fbxPos[2]) };
	Vector3 rot = { static_cast<float>(fbxRot[0]), static_cast<float>(fbxRot[1]), static_cast<float>(fbxRot[2]) };
	Vector3 scale = { static_cast<float>(fbxScale[0]), static_cast<float>(fbxScale[1]), static_cast<float>(fbxScale[2]) };

	// 回転角を Degree -> Radianに
	rot.x_ = YMath::ConvertFromDegreeToRadian(rot.x_);
	rot.y_ = YMath::ConvertFromDegreeToRadian(rot.y_);
	rot.z_ = YMath::ConvertFromDegreeToRadian(rot.z_);

	// ローカルトランスフォーム初期化
	newNode->local_.Initialize({ pos, rot, scale });

	// グローバル変形行列の計算
	newNode->globalMat_ = newNode->local_.m_;

	// 親があるなら
	if (parent)
	{
		// 代入
		newNode->parent_ = parent;

		// 親行列を乗算
		newNode->globalMat_ *= parent->globalMat_;
	}


	// ノード配列に追加
	pModel->nodes_.push_back(std::move(newNode));


	// FBXノードのメッシュ情報を解析
	FbxNodeAttribute* fbxNodeAttribute = fbxNode->GetNodeAttribute();

	// メッシュ情報があるなら
	if (fbxNodeAttribute)
	{
		// メッシュなら
		if (fbxNodeAttribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
		{
			// メッシュ生成
			std::unique_ptr<Mesh> newMesh;
			
			// メッシュロード
			newMesh.reset(Mesh::LoadFbx("Resources/Models/" + pModel->fileName_ + "/", fbxNode, isSmoothing));

			// 追加
			pModel->meshes_.push_back(std::move(newMesh));
		}
	}


	// 子ノードに対して再帰呼び出し
	for (int i = 0; i < fbxNode->GetChildCount(); i++)
	{
		ParseNodeRecursive(pModel, fbxNode->GetChild(i), isSmoothing, newNode.get());
	}
}

#pragma endregion


#pragma region Pipeline

void Model::Pipeline::DrawSet::Draw()
{
	// 描画しないなら弾く
	if (pModel_->isInvisible_) { return; }

	// 定数バッファをシェーダーに送る
	pObj_->SetDrawCommand(TraIndex, ColIndex, LigIndex, MateIndex);

	// メッシュ毎に違うバッファ
	for (size_t i = 0; i < pModel_->meshes_.size(); i++)
	{
		// 描画
		pModel_->meshes_[i]->Draw(TexIndex);
	}
}

void Model::Pipeline::ShaderSet::Load()
{

	// エラーオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

	ID3DBlob* vs = nullptr;
	ID3DBlob* ps = nullptr;

	// 頂点シェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelVS.hlsl", "main", "vs_5_0", vs, errorBlob.Get());
	// ピクセルシェーダの読み込みとコンパイル
	LoadShader(L"Resources/Shaders/ModelPS.hlsl", "main", "ps_5_0", ps, errorBlob.Get());

	vsBlob_ = vs;
	psBlob_ = ps;

}

void Model::Pipeline::StaticInitialize()
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
		// 法線		 (x, y, z)
		{
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		// UV座標	 (x, y)
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		//// 接空点	 (x, y, z)
		//{
		//	"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//},
		//// 頂点色	 (x, y, z, w)
		//{
		//	"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		//}
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
	initStatus.pipelineDesc_.PS.pShaderBytecode = shdrs.psBlob_.Get()->GetBufferPointer();
	initStatus.pipelineDesc_.PS.BytecodeLength = shdrs.psBlob_.Get()->GetBufferSize();

	// ラスタライザの設定
	initStatus.pipelineDesc_.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // 背面をカリング

	// デプスステンシルステートの設定
	initStatus.pipelineDesc_.DepthStencilState.DepthEnable = true; // 深度テスト
	initStatus.pipelineDesc_.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL; // 書き込み許可
	initStatus.pipelineDesc_.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS; // 小さければ合格
	initStatus.pipelineDesc_.DSVFormat = DXGI_FORMAT_D32_FLOAT; // 深度フォーマット

	// 図形の形状設定
	initStatus.pipelineDesc_.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

#pragma endregion


#pragma region プリミティブ形状の設定

	initStatus.primitive_ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST; // 三角形リスト

#pragma endregion


	// パイプラインの数だけ
	for (size_t i = 0; i < sPipelineSets_.size(); i++)
	{
		// パイプライン初期化
		sPipelineSets_[i].Initialize(initStatus);
	}
}

void Model::Pipeline::StaticClearDrawSet(const DrawLocation& location)
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

void Model::Pipeline::StaticPushBackDrawSet(unique_ptr<DrawSet>& drawSet, const DrawLocation& location)
{
	// インデックスに変換
	size_t index = static_cast<size_t>(location);

	// 挿入
	sDrawSets_[index].push_back(std::move(drawSet));
}

void Model::Pipeline::StaticDraw(const DrawLocation& location)
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


