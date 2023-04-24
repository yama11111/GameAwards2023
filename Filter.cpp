#include "Filter.h"
#include "imgui.h"

//インクリメント
Filter::Filter()
{
	// フィルター
	filter_.Initialize({ {}, {}, {1.5f,1.5f,1.5f} });
	filterDra_.Initialize(&filter_);

	//初期化
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {scales,scales,scales} });
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
	filter_.Initialize({ {}, {}, {0.5f,0.5f,0.5f} });
	filterDra_.Initialize(&filter_);

	//初期化
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {scales,scales,scales} });

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
		filters[i].Initialize({ pos_, rot_, {scales,scales,scales } });

		filters[i].pos_.y_ += harfscale * 4;

		filterDras[i].Initialize(&filters[i]);

		drawFlag[i] = true;
	}

	//全部の位置一旦初期化
	for (int i = 0; i < countX; i++)
	{
		//横列分
		for (int j = 0; j < countY; j++)
		{
			filters[i + (j * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * (j * 2));
		}

		//縦列分
		for (int j = 0; j < countY; j++)
		{
			filters[i + (j * countY)].pos_.y_ += (filters[i].scale_.y_) * (countY * i);
		}
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
	//更新
	filter_.UpdateMatrix();
	filterDra_.Update();

	//更新
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].UpdateMatrix();
		filterDras[i].Update();
	}

	//ImGui関係
	ImGui::Begin("Filter_");
	ImGui::Checkbox("allBlockFlag", &allBlockFlag);
	ImGui::Checkbox("drawFlag", &drawFlag[0]);
	ImGui::Checkbox("blockFlag", &blockFlag[0]);
	ImGui::End();
}

//描画ほかのPostとPreの間に描画する
void Filter::Draw()
{
	//描画
	//filterDra_.Draw();

	//複数描画
	for (int i = 0; i < countX * countY; i++)
	{
		if (i == 3 || i == 4 || i == 5)
		{
			//continue;
		}

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
	filter_.Initialize({ {}, {}, {1.5f,1.5f,0.5f} });

	//必ずリセットすること
	filterDra_.Reset();

	//半径
	float harfscale = 1.0f;

	allBlockFlag = false;

	for (int i = 0; i < countX * countY; i++)
	{
		//全部の位置一旦初期化
		for (int i = 0; i < countX; i++)
		{
			//横列分
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * (j * 2));
			}

			//縦列分
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.y_ += (filters[i].scale_.y_) * (countY * i);
			}
		}

		drawFlag[i] = true;
		blockFlag[i] = false;
	}
}

//向き変更
void Filter::DirectionSet(int direction)
{

}

//描画する向き
void Filter::SetDirection(YGame::Transform player, int direction)
{
	//動きを足す
	if (direction != 0)
	{
		filter_.pos_ = player.pos_;
	}

	if (direction == 1)
	{
		filter_.pos_.x_ += FilterToPlayer;
	}
	else if (direction == -1)
	{
		filter_.pos_.x_ -= FilterToPlayer;
	}

	for (int i = 0; i < countX * countY; i++)
	{
		//動きを足す
		filters[i].pos_ += movePos;
	}

	//更新
	filter_.UpdateMatrix();
	filterDra_.Update();

	//半径
	float harfscale = 0.5f * 2;

	//
	if (direction != 0)
	{
		for (int i = 0; i < countX; i++)
		{
			//横列分
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.x_ = player.pos_.x_ + player.scale_.x_ + ((filters[i].scale_.x_ * 2) + (harfscale * (j * 2))) * direction;

				filters[i + (j * countY)].pos_.x_ += (FilterToPlayer)*direction;
			}

			//縦列分
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.y_ = player.pos_.y_ - player.scale_.x_ + ((filters[i].scale_.y_) * (countY * i));
				//filters[i + (j * countY)].pos_.y_ += FilterToPlayer * direction;
			}
		}
	}

	//更新
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].UpdateMatrix();
		filterDras[i].Update();
	}
}