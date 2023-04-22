#include "Filter.h"
#include "imgui.h"

//�C���N�������g
Filter::Filter()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {3.0f,2.0f,1.0f} });
	filterDra_.Initialize(&filter_);

	//������
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {3.0f,2.0f,1.0f} });
		filterDras[i].Initialize(&filters[i]);

		drawFlag[i] = true;
	}

	//���S��0�ɂ��Ƃ�
	for (int i = 0; i < mapCountX; i++)
	{
		for (int j = 0; j < mapCountY; j++)
		{
			Fmap[j][i] = 0;
		}
	}
}

//�f�N�������g
Filter::~Filter()
{
}

//������
void Filter::Initialize()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });
	filterDra_.Initialize(&filter_);

	//������
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {0.5f,0.5f,0.5f} });

		drawFlag[i] = true;
	}

	//
	int x = 0;
	int y = 0;

	//�ʒu����
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
	// �t�B���^�[
	filter_.Initialize({ pos_, rot_, scale_ });
	filterDra_.Initialize(&filter_);

	//�����p
	int size = -1;

	//���a
	float harfscale = 1.0f;

	//������
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

//m�}�b�v ���O��������ė���
void Filter::InitializeMap(int i, int j, int chenge)
{
	Fmap[i][j] = chenge;
}

//�X�V
void Filter::Update()
{
	//�����𑫂�
	//filter_.pos_ += movePos;

	for (int i = 0; i < countX * countY; i++)
	{
		//�����𑫂�
		filters[i].pos_ += movePos;
	}

	//�X�V
	filter_.UpdateMatrix();
	filterDra_.Update();

	//�X�V
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

//�`��ق���Post��Pre�̊Ԃɕ`�悷��
void Filter::Draw()
{
	//�`��
	//filterDra_.Draw();

	for (int i = 0; i < countX * countY; i++)
	{
		if (drawFlag[i] == true)
		{
			filterDras[i].Draw();
		}
	}
}

//���Z�b�g
void Filter::Reset()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,1.0f} });

	//�K�����Z�b�g���邱��
	filterDra_.Reset();
}
