#include "CardDrawer.h"
#include "CalcTransform.h"
#include "DrawerConfig.h"
#include "StageConfig.h"
#include <cassert>
#include <cmath>

#pragma region ���O���

using std::array;
using std::vector;
using std::unique_ptr;
using YGame::Transform;
using YGame::Sprite2DObject;
using YGame::Sprite2D;
using YGame::TextureManager;
using YGame::Color;
using YGame::SlimeActor;
using YMath::Vector3;
using namespace DrawerConfig::Card;

#pragma endregion

std::array<std::unique_ptr<YGame::Sprite2D>, 10> CardDrawerCommon::sNumberSpr_ =
{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
std::unique_ptr<YGame::Sprite2D> CardDrawerCommon::sCardSpr_ = nullptr;

void CardDrawerCommon::StaticInitialize()
{
	// �e�N�X�`���}�l�[�W���[�擾
	TextureManager* pTexMan = TextureManager::GetInstance();

	// ----- �X�v���C�g�ǂݍ��� ----- //

	// ����
	sNumberSpr_[0].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/0.png", false) }));
	sNumberSpr_[1].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/1.png", false) }));
	sNumberSpr_[2].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/2.png", false) }));
	sNumberSpr_[3].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/3.png", false) }));
	sNumberSpr_[4].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/4.png", false) }));
	sNumberSpr_[5].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/5.png", false) }));
	sNumberSpr_[6].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/6.png", false) }));
	sNumberSpr_[7].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/7.png", false) }));
	sNumberSpr_[8].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/8.png", false) }));
	sNumberSpr_[9].reset(Sprite2D::Create({}, { pTexMan->Load("Numbers/9.png", false) }));

	// �X�e�[�W�J�[�h
	sCardSpr_.reset(Sprite2D::Create({}, { pTexMan->Load("Select/card.png", false) }));
}

void CardDrawer::Initialize(YGame::Transform* pParent, const int number)
{
	// ����
	// 0�ȉ��Ȃ�e��
	assert(number > 0);
	// ���
	number_ = number;

	// ----- ���� ----- //

	// �j
	core_.reset(new Transform());
	core_->parent_ = &pParent->m_;

	// �F
	color_.reset(Color::Create());

	// �X�e�[�W�J�[�h�I�u�W�F�N�g
	cardObjs_.reset(Sprite2DObject::Create({}, color_.get()));
	cardObjs_->parent_ = &core_->m_;

	// �����p�I�u�W�F�N�g
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i].reset(Sprite2DObject::Create({}, color_.get()));
		numObjs_[i]->parent_ = &core_->m_;
	}

	// ���Z�b�g
	Reset();
}

void CardDrawer::Reset()
{
	// �u���u���A�j���[�V����������
	SlimeActor::Initialize();

	// ----- �I�u�W�F�N�g������ ----- //

	// �j
	core_->Initialize({});

	// ����
	{
		// �傫��
		float scale = 0.5f;

		numObjs_[0]->Initialize({ {0.0f,0.0f,0.0f},{},{scale,scale,0.0f} });

		// ��
		float x = 16.0f;

		numObjs_[1]->Initialize({ {+x,0.0f,0.0f},{},{scale,scale,0.0f} });
		numObjs_[2]->Initialize({ {-x,0.0f,0.0f},{},{scale,scale,0.0f} });
	}

	// �J�[�h
	cardObjs_->Initialize({});

	// �F������
	color_->SetRGBA({ 1.0f,1.0f,1.0f,1.0f });

	// ----- �A�j���[�V���� ----- //

	// �I������Ă��邩
	isSelected_ = false;
	// �I������Ă�����
	isElderSelected_ = false;
	// ���肳�ꂽ��
	isDetermined_ = false;
	
	// �ړ��p�C�[�W���O
	moveEas_.Initialize(0.0f, Animation::Move::ValueX, Animation::Move::Exponent);
	// �g��p�C�[�W���O
	scaleEas_.Initialize(0.0f, Animation::Scale::Value, Animation::Scale::Exponent);
	// �I��p�p���[
	selectPow_.Initialize(Animation::Frame);
}

void CardDrawer::UpdateSelectAnimation()
{
	// ----- �u���u���A�j���[�V���� ----- //
	
	// �I�����ꂽ�u��
	if (isSelected_ && isElderSelected_ == false)
	{
		// �L�k��
		Vector3 val = core_->scale_ * SlimeAction::Value;

		// �ׂ��L�΂�
		Vector3 squash = +val;
		Vector3 streach = -val;

		// ����
		unsigned int frame = SlimeAction::Frame;
		// �w��
		float exponent = SlimeAction::Exponent;

		// ���삷��
		SlimeActor::Activate(
			{ 
				{ {}, frame, exponent},
				{ streach, frame, exponent },
				{ squash, frame, exponent },
				{ {}, frame, exponent }
			}
		);
	}

	// �I�����L�^
	isElderSelected_ = isSelected_;


	// -------- �A�j���[�V���� --------- //

	// �I�𒆂Ȃ�p���[�X�V
	selectPow_.Update(isSelected_);
	
	// ----- �ړ� ----- //

	// �ړ���
	float moveVal = 0.0f;
	
	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �C�[�Y�C�����
		moveVal = moveEas_.In(selectPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g���
		moveVal = moveEas_.Out(selectPow_.Ratio());
	}

	// �ړ��ʑ��
	core_->pos_.x_ = moveVal;

	
	// ----- �g�� ----- //

	// �ړ���
	float scaleVal = 0.0f;

	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �C�[�Y�C�����
		scaleVal = scaleEas_.In(selectPow_.Ratio());
	}
	// ����ȊO�Ȃ�
	else
	{
		// �C�[�Y�A�E�g���
		scaleVal = scaleEas_.Out(selectPow_.Ratio());
	}

	// �ړ��ʑ��
	core_->scale_ = Vector3(1.0f, 1.0f, 1.0f) + Vector3(scaleVal, scaleVal, 0.0f);


	
	// -------------- �F -------------- //

	// �F�̒l
	Vector3 colorVal = {};

	// �I�΂�Ă���Ȃ�
	if (isSelected_)
	{
		// �ʏ�F��
		colorVal = { 1.0f,1.0f,1.0f };
	}
	// ����ȊO�Ȃ�
	else
	{
		// �Â��F��
		colorVal = { 0.25f,0.25f,0.25f };
	}

	// �F�ݒ�
	color_->SetRGB(colorVal);
}


void CardDrawer::Update()
{
	// �I���A�j���[�V�����X�V
	UpdateSelectAnimation();

	// �u���u���A�j���[�V�����X�V
	SlimeActor::Update();

	// �j
	core_->UpdateMatrix(
		{
			{},
			{},
			SlimeActor::JiggleValue()
		}
	);

	// ����
	for (size_t i = 0; i < numObjs_.size(); i++)
	{
		numObjs_[i]->UpdateMatrix();
	}

	// �J�[�h
	cardObjs_->UpdateMatrix();
}

void CardDrawer::Draw()
{
	// �J�[�h�`��

	sCardSpr_->Draw(cardObjs_.get());

	// ����
	// 10�����Ȃ�
	if (number_ < 10)
	{
		// 1�����f��
		sNumberSpr_[number_]->Draw(numObjs_[0].get());
	}
	// ����ȊO�Ȃ�
	else
	{
		int ones = static_cast<int>(number_) % 10;
		int tens = static_cast<int>(number_) / 10;

		sNumberSpr_[ones]->Draw(numObjs_[1].get());
		sNumberSpr_[tens]->Draw(numObjs_[2].get());
	}
}

void CardDrawer::Determine()
{

	// ����t���O�� true ��
	isDetermined_ = true;
}