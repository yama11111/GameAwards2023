#pragma once
#include "Model.h"

class SkydomeDrawerCommon
{

protected:
	
	// 静的モデル
	static YGame::Model* spModel_;

public:
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

public:
	
	virtual ~SkydomeDrawerCommon() = default;

};

class SkydomeDrawer :
	public SkydomeDrawerCommon
{

private:
	
	// オブジェクト
	std::unique_ptr<YGame::ModelObject> obj_;
	
	// 色
	std::unique_ptr<YGame::Color> color_;

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pParent"> : 親ポインタ</param>
	/// <param name="scaleSize"> : 大きさ</param>
	void Initialize(YMath::Matrix4* pParent, const float scaleSize);
	
	/// <summary>
	/// リセット
	/// </summary>
	/// <param name="scaleSize"> : 大きさ</param>
	void Reset(const float scaleSize);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

};

