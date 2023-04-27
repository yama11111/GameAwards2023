#include "Pises.h"
#include "imgui.h"

Pises::Pises()
{

}

Pises::~Pises()
{

}

void Pises::Initialize()
{
	//transform������
	pises_.Initialize({ {-5.0f,10.0f,0.0f}, {}, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&pises_, IMode::Type::Normal);

	//���u���b�N��
	int count = blockX * blockY;

	//�u���b�N�����
	for (int i = 0; i < count; i++)
	{
		CreateBlock(map[i], pises_, i);
	}
}

void Pises::Initialize(YMath::Vector3 pos, YMath::Vector3 rot, YMath::Vector3 scale)
{
	//transform������
	pises_.Initialize({ pos,rot, {4.5f,4.5f,0.5f} });
	blockDra_.Initialize(&pises_, IMode::Type::Normal);

	//���u���b�N��
	int count = blockX * blockY;

	//�u���b�N�����
	for (int i = 0; i < count; i++)
	{
		CreateBlock(map[i], pises_, i);
	}
}

void Pises::Update()
{

	// �s�[�X�̍X�V
	pises_.UpdateMatrix();
	blockDra_.Update();

	//�u���b�N�̍X�V
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Update();
	}
}

//�����`��
void Pises::Draw()
{
	//�s�[�X�̕`��
	blockDra_.Draw();

	//�u���b�N�̕`��
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Draw();
	}
}

//�u���b�N�̂ݕ`��
void Pises::DrawBlock()
{
	//�u���b�N�̕`��
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i]->Draw();
	}
}

//�s�[�X�̂ݕ`��
void Pises::DrawPiese()
{
	//�s�[�X�̕`��
	blockDra_.Draw();
}

//�u���b�N����
void Pises::CreateBlock(int mode, YGame::Transform pises, int number)
{
	//�c��
	int x = number;
	int y = number;

	//�ʒu���v�Z��

	y = number / blockX;
	x = number - (y * blockY);

	//mode�i�[
	int nowmode = mode;

	//�T�C�Y
	float harfsize = 1.0f;

	//�i�[�pVector
	YMath::Vector3 result;

	//����
	std::unique_ptr<Block> newBlock;
	newBlock.reset(new Block());

	//������
	newBlock->Initialize();

	//��ނ��i�[
	newBlock->SetKind(nowmode);

	//�s�[�X��pos���i�[
	result = pises_.pos_;

	//����Ɉʒu�𒲐�
	result.x_ -= pises_.scale_.x_ + (harfsize * 3) + (harfsize / 2);
	result.y_ += pises_.scale_.y_ + (harfsize * 3) + (harfsize / 2);

	//pos
	result.x_ += x * (harfsize * 2);
	result.y_ -= y * (harfsize * 2);
	result.z_ = 0;

	//pos�i�[ 
	newBlock->SetPos(result);

	//scale�قڂ���ł���
	result = { harfsize / 2,harfsize / 2,harfsize };

	////scale�i�[
	newBlock->SetScale(result);

	//�i�[
	blocks.push_back(std::move(newBlock));
}
