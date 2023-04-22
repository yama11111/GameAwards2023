#include "Block.h"
#include <fstream>
#include <sstream>
using namespace std;

//�C���N�������g
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�f�N�������g
Block::~Block()
{
}

//������
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�X�V
void Block::Update(YGame::Transform filter)
{
	/*if (ClearFlag)
	{
		timer_--;
	}*/

	/*if (timer_ < 1)
	{
		ClearFlag = false;
	}*/

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//�`��
void Block::Draw()
{
	if (nowKind != None)
	{
		//�E�̏��������ƃu���b�N�������
		if (ClearFlag == false)
		{
			blockDra_.Draw();
		}
	}
}

//���Z�b�g
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
}

//�S�u���b�N�̈ʒu���
void Block::SetBlocksPos(YMath::Vector3 pos)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			blocksDra_[i + j];
		}
	}
}

void Block::MovePos(int block)
{
	float spd = 0.1f * block;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd ;

}

void Block::MovePosYUp(int block)
{
	float size = block + 0.55;

	if (block_.scale_.y_ >= block)
	{
		upFlag = false;
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ += spd * 2;
	block_.scale_.y_ += spd;

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

void Block::MovePosYDown()
{
	if (upTimer > 0)
	{
		upTimer--;
		return;
	}

	if (block_.scale_.y_ < 0.55f)
	{
		return;
	}

	float spd = 0.1f;

	block_.pos_.y_ -= spd * 2;
	block_.scale_.y_ -= spd;

	// �u���b�N
	block_.UpdateMatrix();
	blockDra_.Update();
}

//�u���b�N�𐶐���ɕ`�悷���ނ�ς���
void Block::SetMode()
{
	//�F�t���u���b�N
	if (nowKind == ColorB)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Red);
		return;
	}

	//�����`�悵�Ȃ�
	if (nowKind == None)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::None);
		return;
	}

	//���ʂ̃u���b�N
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IDrawer::Mode::Normal);
		return;
	}
}

void Block::LoadCSVFile(std::vector<std::vector<int>>& data, const char* fileName, int _height, int _width)
{
	string str;
	stringstream ss;
	ifstream csvFile(fileName);

	int height = _height;
	int width = _width;
	data.resize(height, vector<int>(width));

	for (int f_row = 0; f_row < height; f_row++)
	{
		for (int f_col = 0; f_col < width - 1; f_col++)
		{
			std::getline(csvFile.seekg(0, ios_base::cur), str, ',');

			ss.str(str);

			ss >> data[f_row][f_col];

			//stringstream�̃N���A
			ss.str("");
			ss.clear(stringstream::goodbit);
		}

		//��ԍŌ�̗�̐��l��ǂݍ���
		std::getline(csvFile.seekg(0, ios_base::cur), str, '\n');
		ss.str(str);
		ss >> data[f_row][width - 1];

		ss.str("");
		ss.clear(stringstream::goodbit);
	}

	csvFile.close();
}

void Block::LoadCSV(std::string csvPath)
{
	std::ifstream ifs{ csvPath };

	std::string line, temp;
	size_t loopY{};

	while (std::getline(ifs, line)) {
		std::istringstream line_stream{ line };
		size_t loopX{};

		while (std::getline(line_stream, temp, ',')) {
			//mapchip_[loopY][loopX] = std::stoi(temp);

			loopX++;
		}
		loopY++;
	}
}