#pragma once
#include "IMode.h"
#include "Model.h"

// タワー描画用コモンクラス
class TowerDrawerCommon
{

public:
	
	// パーツの名前
	enum class Parts
	{
		Core, // 核
		Shell, // 殻
	};

protected:
	
	// パーツの総数
	static const size_t PartsNum_ = 2;

protected:
	
	// モデル (パーツの数だけ)
	static std::array<std::array<YGame::Model*, PartsNum_>, IMode::sTypeNum_> spModels_;
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

	// マテリアルポインタ
	static YGame::Material* spMate_;

public:

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="pVP"> : ビュープロジェクションポインタ</param>
	/// <param name="pMate"> : マテリアルポインタ</param>
	/// <param name="pCoreColors"> : 核色ポインタ配列</param>
	/// <param name="pCoreMate"> : 核マテリアルポインタ</param>
	static void StaticInitialize(YGame::ViewProjection* pVP, YGame::Material* pMate);

public:
	
	virtual ~TowerDrawerCommon() = default;

};

// タワー描画用クラス
class TowerDrawer :
	private IMode,
	private TowerDrawerCommon
{

private:
	
	// 核
	std::unique_ptr<YGame::Transform> core_;
	
	// モデル用オブジェクト (子)
	std::array<std::unique_ptr<YGame::Model::Object>, PartsNum_> modelObjs_;

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="modeType"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="IMode::Type::Noraml"> : 通常状態</param>
	/// <param name="IMode::Type::Movable"> : 可動状態</param>
	void Initialize(YMath::Matrix4* pParent, const IMode::Type& modeType);

	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="modeType"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="IMode::Type::Noraml"> : 通常状態</param>
	/// <param name="IMode::Type::Movable"> : 可動状態</param>
	void Reset(const IMode::Type& modeType);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="location"> : 描画場所</param>
	void Draw(const YGame::DrawLocation& location);

private:

};

