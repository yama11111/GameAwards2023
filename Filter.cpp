#include "Filter.h"

//インクリメント
Filter::Filter()
{
	// フィルター
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_);
}

//デクリメント
Filter::~Filter()
{
}

//初期化
void Filter::Initialize()
{
	// フィルター
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });
	filterDra_.Initialize(&filter_);
}

void Filter::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// フィルター
	filter_.Initialize({ pos_, rot_, scale_ });
	filterDra_.Initialize(&filter_);
}

//更新
void Filter::Update()
{
	//更新
	filter_.UpdateMatrix();
	filterDra_.Update();
}

//描画ほかのPostとPreの間に描画する
void Filter::Draw()
{
	//描画
	filterDra_.Draw();
}

//リセット
void Filter::Reset()
{
	// フィルター
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });

	//必ずリセットすること
	filterDra_.Reset();
}
