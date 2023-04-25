//#include "Filter.h"
//#include "imgui.h"
//
////インクリメント
//Filter::Filter()
//{
//	// フィルター
//	filter_.Initialize({ {}, {}, {3.0f,2.0f,1.0f} });
//	filterDra_.Initialize(&filter_);
//}
//
////デクリメント
//Filter::~Filter()
//{
//}
//
////初期化
//void Filter::Initialize()
//{
//	// フィルター
//	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });
//	filterDra_.Initialize(&filter_);
//}
//
//void Filter::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
//{
//	// フィルター
//	filter_.Initialize({ pos_, rot_, scale_ });
//	filterDra_.Initialize(&filter_);
//}
//
////更新
//void Filter::Update()
//{
//	filter_.pos_ += movePos;
//
//	//更新
//	filter_.UpdateMatrix();
//	filterDra_.Update();
//
//	/*ImGui::Begin("Filter_");
//	ImGui::SliderFloat("pos", &filter_.pos_.x_, -500, 500);
//	ImGui::SliderFloat("pos", &filter_.pos_.y_, -500, 500);
//	ImGui::SliderFloat("scale", &filter_.scale_.x_, 0, 10);
//	ImGui::SliderFloat("scale", &filter_.scale_.y_, 0, 10);
//	ImGui::End();*/
//}
//
////描画ほかのPostとPreの間に描画する
//void Filter::Draw()
//{
//	//描画
//	filterDra_.Draw();
//}
//
////リセット
//void Filter::Reset()
//{
//	// フィルター
//	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });
//
//	//必ずリセットすること
//	filterDra_.Reset();
//}
