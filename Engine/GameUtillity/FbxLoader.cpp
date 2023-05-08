#include "FbxLoader.h"
#include "FileUtillity.h"
#include <cassert>

void FbxLoader::LoadModel(const std::string& modelFileName)
{
	// ディレクトリパス (モデルのファイル名と同じフォルダから)
	std::string directoryPath = "Resources/Models/" + modelFileName + "/";

	// FBXファイル名
	std::string fbxFileName = modelFileName + ".fbx";

	//フルパス
	std::string fullPath = directoryPath + fbxFileName;


	// ファイル名を指定してFBXファイル読み込み
	assert(fbxImp_->Initialize(fullPath.c_str(), -1, fbxMan_->GetIOSettings()));


	// シーン生成
	FbxScene* fbxScene = FbxScene::Create(fbxMan_, "fbxScene");

	// ファイルからロードしたFBX情報をインポート
	fbxImp_->Import(fbxScene);


}

void FbxLoader::Initialize(ID3D12Device* pDevice)
{
	// 再初期化チェック
	assert(fbxMan_ == nullptr);

	// nullチェック
	assert(pDevice);
	// 代入
	pDevice_ = pDevice;

	// FBXマネージャーの生成
	fbxMan_ = FbxManager::Create();

	// FBXマネージャーの入出力設定
	FbxIOSettings* ios = FbxIOSettings::Create(fbxMan_, IOSROOT);
	fbxMan_->SetIOSettings(ios);

	// FBXインポーターの生成
	fbxImp_ = FbxImporter::Create(fbxMan_, "");
}

void FbxLoader::Finalize()
{
	// 各種FBXインスタンス破棄
	fbxImp_->Destroy();
	fbxMan_->Destroy();
}

FbxLoader* FbxLoader::GetInstance()
{
	static FbxLoader instance;
	return &instance;
}
