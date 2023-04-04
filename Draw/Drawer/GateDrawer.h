#pragma once
#include "IDrawer.h"
#include <array>

// ゲート描画用コモンクラス
class GateDrawerCommon
{
public:
	// パーツの名前
	enum class Parts
	{
		Inside, // 内枠
		InsideLight, // 内枠 (光)
		Outside, // 外枠
		OutsideLight, // 外枠 (光)
	};
protected:
	// モードの総数
	static const size_t ModeNum_ = 3;
	// パーツの総数
	static const size_t PartsNum_ = 4;
protected:
	// モデル (パーツの数だけ)
	static std::array<std::array<std::unique_ptr<YGame::Model>, PartsNum_>, ModeNum_> sModels_;
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;
public:
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

// ゲート描画用クラス
class GateDrawer :
	private IDrawer,
	private GateDrawerCommon
{
private:
	// モデル用オブジェクト (子)
	std::array<std::array<std::unique_ptr<YGame::ModelObject>, PartsNum_>, ModeNum_> modelObjs_;

	// 透明色
	std::unique_ptr<YGame::Color> invisibleColor_;
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ (この行列に追従する)</param>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Initialize(YGame::Transform* pParent, const Mode& mode);
	/// <summary>
	/// リセット (中身だけ初期化)
	/// </summary>
	/// <param name="mode"> : 状態</param>
	/// <param name="---------------------------------------------"></param>
	/// <param name="Mode::Noraml"> : 通常状態</param>
	/// <param name="Mode::Red"> : 赤色状態</param>
	/// <param name="Mode::None"> : 無し (使わない)</param>
	void Reset(const Mode& mode);
	// 更新
	void Update();
	// 前方描画 (フィルターより 先 に呼ぶ)
	void PreDraw();
	// 後方描画 (フィルターより 後 に呼ぶ)
	void PostDraw();
private:
	// 立ちモーション
	void IdleAnimation() override;
public:
	~GateDrawer() = default;
};

