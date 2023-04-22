#include "Filter.h"
#include "imgui.h"

//インクリメント
Filter::Filter()
{
	// フィルター
	filter_.Initialize({ {}, {}, {3.0f,2.0f,1.0f} });
	filterDra_.Initialize(&filter_);

	//初期化
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {3.0f,2.0f,1.0f} });
		filterDras[i].Initialize(&filters[i]);

		drawFlag[i] = true;
	}

	//一回全部0にしとく
	for (int i = 0; i < mapCountX; i++)
	{
		for (int j = 0; j < mapCountY; j++)
		{
			Fmap[j][i] = 0;
		}
	}
}

//デクリメント
Filter::~Filter()
{
}

//初期化
void Filter::Initialize()
{
	// フィルター
	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });
	filterDra_.Initialize(&filter_);

	//初期化
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {0.5f,0.5f,0.5f} });

		drawFlag[i] = true;
	}

	//
	int x = 0;
	int y = 0;

	//位置調整
	for (int i = 0; i < countX * countY; i++)
	{
		if (x >= y)
		{
			y++;
		}
		else
		{
			x++;
		}

		filters[i].pos_.x_ += (filters[i].scale_.x_) * (i + x - countX);
		filters[i].pos_.y_ += (filters[i].scale_.y_) * (i + y - countY);

		filterDras[i].Initialize(&filters[i]);
	}
}

void Filter::Initialize(YMath::Vector3 pos_, YMath::Vector3 rot_, YMath::Vector3 scale_)
{
	// フィルター
	filter_.Initialize({ pos_, rot_, scale_ });
	filterDra_.Initialize(&filter_);

	//調整用
	int size = -1;

	//半径
	float harfscale = 1.0f;

	//初期化
	for (int i = 0; i < countY * countX; i++)
	{
		filters[i].Initialize({ pos_, rot_, {0.5f,0.5f,0.5f} });

		filters[i].pos_.y_ += harfscale * 4;
		
		filterDras[i].Initialize(&filters[i]);

		drawFlag[i] = true;
	}

	for (int i = 0; i < countX - 1; i++)
	{
		filters[i].pos_.x_ += (filters[i].scale_.x_);
		filters[i + countY].pos_.x_ += (filters[i].scale_.x_) + (harfscale * 2);
		filters[i + (2 * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * 4);
		//filters[i + (3 * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * 6);

		filters[i].pos_.y_ += (filters[i].scale_.y_) * (countX * i);
		filters[i + countY].pos_.y_ += (filters[i].scale_.y_) * (countX * i);
		filters[i + (2 * countY)].pos_.y_ += (filters[i].scale_.y_) * (countX * i);
		//filters[i + (3 * countY)].pos_.y_ += (filters[i].scale_.y_) * (countX * i);
	}
}

//mマップ を外からもって来る
void Filter::InitializeMap(int i, int j, int chenge)
{
	Fmap[i][j] = chenge;
}

//更新
void Filter::Update()
{
	//動きを足す
	//filter_.pos_ += movePos;

	for (int i = 0; i < countX * countY; i++)
	{
		//動きを足す
		filters[i].pos_ += movePos;
	}

	//更新
	filter_.UpdateMatrix();
	filterDra_.Update();

	//更新
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].UpdateMatrix();
		filterDras[i].Update();
	}

	ImGui::Begin("Filter_");
	ImGui::SliderFloat("pos", &filters[0].pos_.x_, -500, 500);
	ImGui::SliderFloat("pos", &filters[0].pos_.y_, -500, 500);
	ImGui::SliderFloat("pos", &filters[8].pos_.x_, -500, 500);
	ImGui::SliderFloat("pos", &filters[8].pos_.y_, -500, 500);
	ImGui::End();
}

//描画ほかのPostとPreの間に描画する
void Filter::Draw()
{
	//描画
	//filterDra_.Draw();

	for (int i = 0; i < countX * countY; i++)
	{
		if (drawFlag[i] == true)
		{
			filterDras[i].Draw();
		}
	}
}

//リセット
void Filter::Reset()
{
	// フィルター
	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });

	//必ずリセットすること
	filterDra_.Reset();
}
