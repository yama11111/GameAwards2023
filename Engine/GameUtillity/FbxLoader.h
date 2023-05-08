#pragma once

#include <fbxsdk.h>

#include <d3d12.h>
#include <d3dx12.h>

#include <string>

class FbxLoader
{

public:

	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// </summary>
	/// <param name="modelFileName"> : モデル名</param>
	void LoadModel(const std::string& modelFileName);


public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ID3D12Device* pDevice);

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

private:

	// D3D12デバイスポインタ
	ID3D12Device* pDevice_ = nullptr;

	// FBXマネージャー
	FbxManager* fbxMan_ = nullptr;
	
	// FBXインポーター
	FbxImporter* fbxImp_ = nullptr;

public:
	
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

private:
	
	FbxLoader() = default;

	~FbxLoader() = default;
	
	FbxLoader(const FbxLoader& obj) = delete;
	
	void operator=(const FbxLoader& obj) = delete;
};