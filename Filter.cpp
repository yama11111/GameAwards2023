#include "Filter.h"
#include "imgui.h"

//�C���N�������g
Filter::Filter()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {1.5f,1.5f,1.5f} });
	filterDra_.Initialize(&filter_);

	//������
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {scales,scales,scales} });
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
	filter_.Initialize({ {}, {}, {0.5f,0.5f,0.5f} });
	filterDra_.Initialize(&filter_);

	//������
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].Initialize({ {}, {}, {scales,scales,scales} });

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
		filters[i].Initialize({ pos_, rot_, {scales,scales,scales } });

		filters[i].pos_.y_ += harfscale * 4;

		filterDras[i].Initialize(&filters[i]);

		drawFlag[i] = true;
	}

	//�S���̈ʒu��U������
	for (int i = 0; i < countX; i++)
	{
		//����
		for (int j = 0; j < countY; j++)
		{
			filters[i + (j * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * (j * 2));
		}

		//�c��
		for (int j = 0; j < countY; j++)
		{
			filters[i + (j * countY)].pos_.y_ += (filters[i].scale_.y_) * (countY * i);
		}
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
	//�X�V
	filter_.UpdateMatrix();
	filterDra_.Update();

	//�X�V
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].UpdateMatrix();
		filterDras[i].Update();
	}

	//ImGui�֌W
	ImGui::Begin("Filter_");
	ImGui::Checkbox("allBlockFlag", &allBlockFlag);
	ImGui::Checkbox("drawFlag", &drawFlag[0]);
	ImGui::Checkbox("blockFlag", &blockFlag[0]);
	ImGui::End();
}

//�`��ق���Post��Pre�̊Ԃɕ`�悷��
void Filter::Draw()
{
	//�`��
	//filterDra_.Draw();

	//�����`��
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

//���Z�b�g
void Filter::Reset()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {1.5f,1.5f,0.5f} });

	//�K�����Z�b�g���邱��
	filterDra_.Reset();

	//���a
	float harfscale = 1.0f;

	allBlockFlag = false;

	for (int i = 0; i < countX * countY; i++)
	{
		//�S���̈ʒu��U������
		for (int i = 0; i < countX; i++)
		{
			//����
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.x_ += (filters[i].scale_.x_) + (harfscale * (j * 2));
			}

			//�c��
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.y_ += (filters[i].scale_.y_) * (countY * i);
			}
		}

		drawFlag[i] = true;
		blockFlag[i] = false;
	}
}

//�����ύX
void Filter::DirectionSet(int direction)
{

}

//�`�悷�����
void Filter::SetDirection(YGame::Transform player, int direction)
{
	//�����𑫂�
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
		//�����𑫂�
		filters[i].pos_ += movePos;
	}

	//�X�V
	filter_.UpdateMatrix();
	filterDra_.Update();

	//���a
	float harfscale = 0.5f * 2;

	//
	if (direction != 0)
	{
		for (int i = 0; i < countX; i++)
		{
			//����
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.x_ = player.pos_.x_ + player.scale_.x_ + ((filters[i].scale_.x_ * 2) + (harfscale * (j * 2))) * direction;

				filters[i + (j * countY)].pos_.x_ += (FilterToPlayer)*direction;
			}

			//�c��
			for (int j = 0; j < countY; j++)
			{
				filters[i + (j * countY)].pos_.y_ = player.pos_.y_ - player.scale_.x_ + ((filters[i].scale_.y_) * (countY * i));
				//filters[i + (j * countY)].pos_.y_ += FilterToPlayer * direction;
			}
		}
	}

	//�X�V
	for (int i = 0; i < countX * countY; i++)
	{
		filters[i].UpdateMatrix();
		filterDras[i].Update();
	}
}