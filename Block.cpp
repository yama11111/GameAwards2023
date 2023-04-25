#include "Block.h"
using namespace std;


//�C���N�������g
Block::Block()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//�f�N�������g
Block::~Block()
{
}

//������
void Block::Initialize()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
}

//�X�V
void Block::Update(YGame::Transform filter)
{
	/*if (ClearFlag)
	{
		timer_--;
	}*/

	if (timer_ < 1)
	{
		ClearFlag = false;
	}

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
		if (ClearFlag == false || nowKind != ColorB)
		{
			blockDra_.Draw();
		}
	}
}

//���Z�b�g
void Block::Reset()
{
	block_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
	blockDra_.Initialize(&block_, IMode::Type::Normal);
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
		blockDra_.Initialize(&block_, IMode::Type::Movable);
		return;
	}

	////�����`�悵�Ȃ�
	//if (nowKind == None)
	//{
	//	blockDra_.Initialize(&block_, IDrawer::Mode::None);
	//	return;
	//}

	//���ʂ̃u���b�N
	if (nowKind == Normal)
	{
		blockDra_.Initialize(&block_, IMode::Type::Normal);
		return;
	}
}

//void Block::LoadCSVFile(std::vector<std::vector<int>>& data, const char* fileName, int _height, int _width)
//{
//	string str;
//	stringstream ss;
//	ifstream csvFile(fileName);
//
//	int height = _height;
//	int width = _width;
//	data.resize(height, vector<int>(width));
//
//	for (int f_row = 0; f_row < height; f_row++)
//	{
//		for (int f_col = 0; f_col < width - 1; f_col++)
//		{
//			std::getline(csvFile.seekg(0, ios_base::cur), str, ',');
//
//			ss.str(str);
//
//			ss >> data[f_row][f_col];
//
//			//stringstream�̃N���A
//			ss.str("");
//			ss.clear(stringstream::goodbit);
//		}
//
//		//��ԍŌ�̗�̐��l��ǂݍ���
//		std::getline(csvFile.seekg(0, ios_base::cur), str, '\n');
//		ss.str(str);
//		ss >> data[f_row][width - 1];
//
//		ss.str("");
//		ss.clear(stringstream::goodbit);
//	}
//
//	csvFile.close();
//}
//
//void LoadCsv(std::string UserCsv)
//{
//	std::ifstream ifs{ UserCsv };
//	std::string line, temp;
//
//	std::getline(ifs, line);
//	if (line != "UserInfomation") return;
//
//	size_t lineCount{ 1 };
//	PlayerInfo_t pInfo{};
//	FilterInfo_t fInfo{};
//
//	while (std::getline(ifs, line)) {
//		std::size_t wordCount{ 0 };
//
//		// �e���ڂɉ����č폜�B�d�����͗��p��
//		if (line.find("pos :") != std::string::npos) {
//			line.erase(0, 5);
//		}
//		if (line.find("size :") != std::string::npos) {
//			line.erase(0, 6);
//		}
//		if (line.find("moveSpeed :") != std::string::npos) {
//			line.erase(0, 11);
//		}
//		if (line.find("jumpPower :") != std::string::npos) {
//			line.erase(0, 11);
//		}
//		if (line.find("fallValue :") != std::string::npos) {
//			line.erase(0, 11);
//		}
//		if (line.find("gravity :") != std::string::npos) {
//			line.erase(0, 9);
//		}
//		if (line.find("color :") != std::string::npos) {
//			line.erase(0, 7);
//		}
//
//		std::istringstream line_stream{ line };
//		while (std::getline(line_stream, temp, ',')) {
//			switch (lineCount)
//			{
//				// =====player=====
//			case 3: // pos :float,float
//				!wordCount ? pInfo.pos.x = std::stof(temp) : pInfo.pos.y = std::stof(temp);
//				break;
//
//			case 4: // size :float,float
//				!wordCount ? pInfo.size.x = std::stof(temp) : pInfo.size.y = std::stof(temp);
//				break;
//
//			case 5: // moveSpeed :float
//				pInfo.moveSpeed = std::stof(temp);
//				break;
//
//			case 6: // jumpPower :float
//				pInfo.jumpPower = std::stof(temp);
//				break;
//
//			case 7: // fallValue :float
//				pInfo.fallValue = std::stof(temp);
//				break;
//
//			case 8: // gravity :float
//				pInfo.gravity = std::stof(temp);
//				break;
//
//			case 9: // color :color
//				pInfo.color = CheckColor(temp);
//				break;
//
//				// =====filter=====
//			case 12: // pos :float,float
//				!wordCount ? fInfo.pos.x = std::stof(temp) : fInfo.pos.y = std::stof(temp);
//				break;
//
//			case 13: // size :float,float
//				!wordCount ? fInfo.size.x = std::stof(temp) : fInfo.size.y = std::stof(temp);
//				break;
//
//			case 14: // moveSpeed :float,float
//				fInfo.moveSpeed = std::stof(temp);
//				break;
//
//			case 15: // color :color
//				fInfo.color = CheckColor(temp);
//				break;
//
//			default:
//				break;
//			}
//			wordCount++;
//		}
//		lineCount++;
//	}
//
//	player_ = std::make_unique<Player>(pInfo.pos, pInfo.size, pInfo.moveSpeed, pInfo.jumpPower, pInfo.fallValue, pInfo.gravity, pInfo.color);
//	filter_ = std::make_unique<Filter>(fInfo.pos, fInfo.size, fInfo.moveSpeed, fInfo.color);
//
//	player_->SetFilterPtr(filter_.get());
//}