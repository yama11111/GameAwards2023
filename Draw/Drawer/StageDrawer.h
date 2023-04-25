#pragma once
#include "SlimeActor.h"
#include "TowerDrawer.h"
#include "Sprite3D.h"

class StageDrawerCommon
{

protected:
	
	// 静的数字スプライト
	static std::array<YGame::Sprite3D*, 10> spNumberSpr_;
	
	// ビュープロジェクションポインタ
	static YGame::ViewProjection* spVP_;

public:
	
	// 静的初期化
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:
	
	virtual ~StageDrawerCommon() = default;

};

class StageDrawer : 
	private StageDrawerCommon,
	private YGame::SlimeActor
{

private:
	
	// 核
	std::unique_ptr<YGame::Transform> core_;
	
	// 数字用オブジェクト
	std::array<std::unique_ptr<YGame::Sprite3DObject>, 3> numObjs_;
	
	// タワー描画クラス
	TowerDrawer towerDra_;

	// 色
	std::unique_ptr<YGame::Color> color_;

	
	// 数字
	int number_ = 0;

public:
	
	// 初期化
	void Initialize(YGame::Transform* pParent, const int number);
	
	// リセット
	void Reset();
	
	// 更新
	void Update();

	// 描画 (モデル)
	void DrawModel();

	// 描画 (スプライト3D)
	void DrawSprite3D();

};

