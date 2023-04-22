#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#include "DrawerManager.h"

#pragma region ���O��Ԑ錾
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

//y����+�����|

//bool�^BoxCollision
static bool BoxCollision(YGame::Transform obj1, YGame::Transform obj2, bool nibai)
{
	YMath::Vector3 obj3 = obj1.scale_;

	if (nibai)
	{
		obj3 *= 2;
	}

	//�v���C���[�̏㉺���E
	float p_top = obj1.pos_.y_ - obj3.y_;
	float p_bottom = obj1.pos_.y_ + obj3.y_;
	float p_right = obj1.pos_.x_ + obj3.x_;
	float p_left = obj1.pos_.x_ - obj3.x_;

	obj3 = obj2.scale_;

	if (nibai)
	{
		obj3 *= 2;
	}

	//�t�B���^�[�̏㉺���E
	float f_top = obj2.pos_.y_ - obj3.y_;
	float f_bottom = obj2.pos_.y_ + obj3.y_;
	float f_right = obj2.pos_.x_ + obj3.x_;
	float f_left = obj2.pos_.x_ - obj3.x_;

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		return true;
	}

	return false;
}

//Pos��Ԃ�BOxCollision(���E�T�C�Y�Œ�)
static YMath::Vector3 BoxCollision(YMath::Vector3 posP, YMath::Vector2 sizePRL, YMath::Vector2 sizePUD, YMath::Vector3 posF, YMath::Vector2 sizeF, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YMath::Vector3 nowPosP = posP;
	YMath::Vector3 nowPosF = posF;

	//�v���C���[�̏㉺���E
	float p_top = nowPosP.y_ - sizePUD.x_;
	float p_bottom = nowPosP.y_ + sizePUD.y_;
	float p_right = nowPosP.x_ + sizePRL.x_;
	float p_left = nowPosP.x_ - sizePRL.y_;

	//�t�B���^�[�̏㉺���E
	float f_top = nowPosF.y_ - sizeF.y_;
	float f_bottom = nowPosF.y_ + sizeF.y_;
	float f_right = nowPosF.x_ + sizeF.x_;
	float f_left = nowPosF.x_ - sizeF.x_;

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.x_ -= DS.x_ * 0.01f;
			nowPosP.y_ -= DS.y_ * 0.01f;

			nowPosP.x_ += AW.x_ * 0.01f;
			nowPosP.y_ += AW.y_ * 0.01f;

			//�v���C���[�̏㉺���E
			p_top = nowPosP.y_ - sizePUD.x_;
			p_bottom = nowPosP.y_ + sizePUD.y_;
			p_right = nowPosP.x_ + sizePRL.x_;
			p_left = nowPosP.x_ - sizePRL.y_;
		}
	}

	return nowPosP;
}

//Pos��Ԃ�BOxCollision(���E�T�C�Y�o���o��)
static YMath::Vector3 BoxCollision(YMath::Vector3 posP, YMath::Vector2 sizePRL, YMath::Vector2 sizePUD, YMath::Vector3 posF, YMath::Vector2 sizeLR, YMath::Vector2 sizeUD, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YMath::Vector3 nowPosP = posP;
	YMath::Vector3 nowPosF = posF;

	YMath::Vector2 Ds = DS;
	YMath::Vector2 Aw = AW;

	Ds.x_ *= 0.1f;
	Ds.y_ *= 0.1f;
	Aw.x_ *= 0.1f;
	Aw.y_ *= 0.1f;

	//�v���C���[�̏㉺���E
		//�v���C���[�̏㉺���E
	float p_top = nowPosP.y_ - sizePUD.x_;
	float p_bottom = nowPosP.y_ + sizePUD.y_;
	float p_right = nowPosP.x_ + sizePRL.x_;
	float p_left = nowPosP.x_ - sizePRL.y_;

	//�t�B���^�[�̏㉺���E
	float f_top = nowPosF.y_ - sizeUD.x_;
	float f_bottom = nowPosF.y_ + sizeUD.y_;
	float f_right = nowPosF.x_ + sizeLR.y_;
	float f_left = nowPosF.x_ - sizeLR.x_;

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.x_ -= DS.x_ * 0.1f;
			nowPosP.y_ -= DS.y_ * 0.1f;

			nowPosP.x_ += AW.x_ * 0.1f;
			nowPosP.y_ += AW.y_ * 0.1f;

			//�v���C���[�̏㉺���E
			p_top = nowPosP.y_ - sizePUD.x_;
			p_bottom = nowPosP.y_ + sizePUD.y_;
			p_right = nowPosP.x_ + sizePRL.x_;
			p_left = nowPosP.x_ - sizePRL.y_;
		}
	}

	return nowPosP;
}

//Pos��Ԃ�BoxCollision(Transform�̂�)
static YMath::Vector3 BoxCollision(YGame::Transform posP, YGame::Transform posF, YMath::Vector2 DS, YMath::Vector2 AW)
{
	YGame::Transform nowPosP = posP;
	YGame::Transform nowPosF = posF;

	posP.scale_ *= 2;
	posF.scale_ *= 2;

	//�v���C���[�̏㉺���E
	float p_top = nowPosP.pos_.y_ - posP.scale_.y_;
	float p_bottom = nowPosP.pos_.y_ + posP.scale_.y_;
	float p_right = nowPosP.pos_.x_ + posP.scale_.x_;
	float p_left = nowPosP.pos_.x_ - posP.scale_.x_;

	//�t�B���^�[�̏㉺���E
	float f_top = nowPosF.pos_.y_ - posF.scale_.y_;
	float f_bottom = nowPosF.pos_.y_ + posF.scale_.y_;
	float f_right = nowPosF.pos_.x_ + posF.scale_.x_;
	float f_left = nowPosF.pos_.x_ - posF.scale_.x_;

	//�t�B���^�[�ɓ������Ă��邩
	if (p_left < f_right &&
		p_right > f_left &&
		p_top  < f_bottom &&
		p_bottom > f_top)
	{
		while (p_left < f_right &&
			p_right > f_left &&
			p_top  < f_bottom &&
			p_bottom > f_top)
		{
			nowPosP.pos_.x_ -= DS.x_ * 0.01f;
			nowPosP.pos_.y_ -= DS.y_ * 0.01f;

			nowPosP.pos_.x_ += AW.x_ * 0.01f;
			nowPosP.pos_.y_ += AW.y_ * 0.01f;

			//�v���C���[�̏㉺���E
			p_top = nowPosP.pos_.y_ - posP.scale_.y_;
			p_bottom = nowPosP.pos_.y_ + posP.scale_.y_;
			p_right = nowPosP.pos_.x_ + posP.scale_.x_;
			p_left = nowPosP.pos_.x_ - posP.scale_.x_;
		}
	}

	return nowPosP.pos_;
}

#pragma region �ǂݍ���
void PlayScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	conSpr_ = Sprite2D::Create({}, { Texture::Load("operateSign.png") });
	conSpr2_ = Sprite2D::Create({}, { Texture::Load("forFilter.png") });
	conSpr3_ = Sprite2D::Create({}, { Texture::Load("forFilter2.png") });

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �G�t�F�N�g
	EffectManager::StaticInitialize(&particleMan_);

	// �`��N���X�S��
	DrawerManager::StaticInitialize(&transferVP_, &particleMan_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	conObj_.reset(Sprite2DObject::Create({ {WinSize.x_ / 2.0f + 220, WinSize.y_ - 100, 0.0f},{},{0.5f,0.5f,0.0f} }));
	conObj2_.reset(Sprite2DObject::Create({ {WinSize.x_ - 165, WinSize.y_ - 180, 0.0f},{},{0.5f,0.5f,0.0f} }));
	conObj3_.reset(Sprite2DObject::Create({ {WinSize.x_ - 165, WinSize.y_ - 70, 0.0f},{},{0.5f,0.5f,0.0f} }));

	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- �v���C���[ ----- //

	// ����
	player.reset(new Player());

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	player->Initialize({ -50.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, { scale.x_ * 2.0f - 0.2f,scale.y_ * 2.0f - 0.2f,scale.z_ * 2.0f - 0.2f });

	//�f�B���N�V����(����)
	player->SetDirection(YMath::Vector3{ +1.0f, 0.0f, 0.0f });

	player->Reset();

	//config
	stageConfig_ = StageConfig::GetInstance();
	//StageConfig::GetCurrentStageIndex();
	//
	//player_->SetClearFlag(true);

	int Idx = stageConfig_->GetCurrentStageIndex();

	switch (Idx)
	{
	case 1:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map1[i][j];
			}
		}

		break;

	case 2:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map2[i][j];
			}
		}
		break;

	case 3:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map3[i][j];
			}
		}
		break;

	case 4:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map4[i][j];
			}
		}

		break;

	case 5:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map5[i][j];
			}
		}
		break;

	case 6:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map6[i][j];
			}
		}
		break;

	case 7:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map7[i][j];
			}
		}

		break;

	case 8:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map8[i][j];
			}
		}

		break;

	case 9:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map9[i][j];
			}
		}
		break;

	case 10:

		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map10[i][j];
			}
		}
		break;

	default:
		for (int i = 0; i < blockCountY; i++)
		{
			for (int j = 0; j < blockCountX; j++)
			{
				map[i][j] = map1[i][j];
			}
		}
		break;
	}

	// ----- �t�B���^�[ ----- //

	// ����
	filter.reset(new Filter());

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	filter->Initialize({ -10.0f, 0.0f, 3.0f }, {}, { 1.5f,1.5f,1.5f });

	filter->Reset();

	// ----- �S�[�� ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[��)
	goalDra_.Initialize(&goal_);

	// ----- �u���b�N ----- //

	//�u���b�N
	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			//None��������̂���(return)
			if (map[i][j] == None)
			{
				continue;
			}

			//�T�C�Y
			float size = harfScale * 2;

			//�i�[�pVector
			YMath::Vector3 result;

			//��ނɂ����
			//�����n�_
			if (map[i][j] == Start)
			{
				//posXY
				result.x_ = (j - (blockCountX / 3)) * size;
				result.y_ = ((blockCountY / 2) - i) * size;

				//pos�i�[
				player->SetPos(result);

				//StartPos�i�[
				player->SetStartPos(result);

				////��ނ��󔒂�
				//newBlock->SetKind(None);

				//����
				continue;
			}

			//�S�[���n�_
			if (map[i][j] == Gorl)
			{
				//pos�i�[
				goal_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				goal_.pos_.y_ = ((blockCountY / 2) - i) * size;

				//scale�i�[
				goal_.scale_.x_ = size / 4.0f;
				goal_.scale_.y_ = size / 4.0f;

				////��ނ��󔒂�
				//newBlock->SetKind(None);

				//����
				continue;
			}

			//�R���N�g�A�C�e��
			if (map[i][j] == Collect)
			{

				////��ނ��󔒂�
				//newBlock->SetKind(None);

				//����
				continue;
			}

			//����
			std::unique_ptr<Block> newBlock;
			newBlock.reset(new Block());

			//������
			newBlock->Initialize();

			//��ނ��i�[
			newBlock->SetKind(map[i][j]);

			////�T�C�Y
			//float size = harfScale * 2;

			////�i�[�pVector
			//YMath::Vector3 result;

			//z�͓��ɂ�����Ȃ�
			result.z_ = size / 4;

			//posXY
			result.x_ = (j - (blockCountX / 3)) * size - 8;
			result.y_ = ((blockCountY / 2) - i) * size;

			//pos�i�[
			newBlock->SetPos(result);

			//scaleXY
			result.x_ = size / 4;
			result.y_ = size / 4;

			//scale�i�[
			newBlock->SetScale(result);

			//�i�[
			block.push_back(std::move(newBlock));
		}
	}

	//��ނɂ���ău���b�N��ύX
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	//�t�B���^�[�̈ʒu���v���C���[�̏��
	YMath::Vector3 Ppos = player->GetPos();
	Ppos.y_ += harfScale * 10;
	filter->SetPos(Ppos);

	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			filter->InitializeMap(i, j, map[i][j]);
		}
	}

	// �V��������
	skydome_.Initialize();

	// HUD������
	hud_.Initalize();

	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �J�����Ǐ]�_
	followPoint_ = {};

	// �X�N���[���J����
	scrollCamera_.Initialize({ 0,0,-50 }, &followPoint_, { 0.0f,0.0f,0.0f });

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({});
}
#pragma endregion

#pragma region �I������
void PlayScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void PlayScene::Update()
{
	// HUD�X�V
	hud_.Update();

	// �|�[�Y���Ȃ�e��
	if (hud_.IsPause()) { return; }


	// ����؂�ւ�
	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		//�v���C���[�ƃt�B���^�[���������ĂȂ��Ȃ�
		if (!BoxCollision(player->GetTransform(), filter->GetTransform(), true))
		{
			//����t���O�𔽓]
			player->ChengePlayFlag();

			//���삵�Ă�obj��\������X�v���C�g�̕ύX
			if (player->GetPlayFlag()) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
			else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }
		}
		else
		{
			// �J�����h���
			scrollCamera_.Shaking(10, 2);
		}
	}

	////�f�o�b�O�p�̃��Z�b�g�{�^��
	//if (sKeys_->IsTrigger(DIK_R))
	//{
	//	player->Reset();
	//	filter->Reset();
	//}

	//�i�[�pVector
	YMath::Vector3 result(0.0f, 0.0f, 0.0f);

	//�l��0��
	player->SetMovePos(result);
	filter->SetMovePos(result);

	//���͏�Ԃ����
	result.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD);
	result.y_ = sKeys_->Vertical(Keys::MoveStandard::WASD);
	result.z_ = 0.0f;

	//�ړ���
	float playerA = harfScale * 2;
	float filterA = harfScale * 2;

	//���̃A�N�e�B�u���
	if (player->GetPlayFlag())
	{
		//�ړ���
		//result.x_ *= playerA;
		result.x_ = filterA * (sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A));

		//�v���C���[��y���̓W�����v�̂�
		result.y_ = 0.0f;

		//�v���C���[�̈ړ��ʊi�[
		player->SetMovePos(result);
	}
	else
	{
		//�ړ���
		result.x_ = filterA * (sKeys_->IsTrigger(DIK_D) - sKeys_->IsTrigger(DIK_A));
		result.y_ = filterA * (sKeys_->IsTrigger(DIK_W) - sKeys_->IsTrigger(DIK_S));

		//�t�B���^�[�̈ړ��ʊi�[
		filter->SetMovePos(result);
	}

	//Player��Update
	player->Update(filter->GetTransform());

	//filter��Update
	filter->Update();

	// �u���b�N
	for (int i = 0; i < block.size(); i++)
	{
		//�X�V
		block[i]->Update(filter->GetTransform());
		 
		//�t�B���^�[�Ɠ������Ă���
		for (int j = 0; j < 12; j++)
		{
			if (filter->GetDrawFlag(j) == true)
			{
				if (block[i]->GetClearFlag() == false)
				{
					if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(j), true))
					{
						filter->SetDrawFlag(j, false);

						//������t���O��on��
						block[i]->SetClearFlag(true);

						// �J�����h���
						scrollCamera_.Shaking(10, 2);
					}
				}
			}
		}

		//�Ԃ��F�Ȃ�
		if (block[i]->GetKind() == ColorB)
		{
			//player�Ɠ������Ă��牄��
			if (BoxCollision(block[i]->GetTransform(), player->GetTransform(), true))
			{
				//�^�C�}�[��ݒ�
				block[i]->SetTimer(10);
			}

			////�t�B���^�[�Ɠ������Ă���
			//if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(), true))
			//{
			//	//������t���O��on��
			//	block[i]->SetClearFlag(true);

			//	//�^�C�}�[��ݒ�
			//	block[i]->SetTimer(50);
			//}
		}

		//�ʏ�u���b�N����
		//if (block[i]->GetKind() == Normal)
		//{
		//	//������t���O��on��
		//	block[i]->SetClearFlag(false);

		//	if (BoxCollision(block[i]->GetTransform(), filter->GetTransform(), true))
		//	{
		//		//������t���O��on��
		//		block[i]->SetClearFlag(true);
		//	}
		//}

		//�u���b�N�グ�������u
		if (player->GetPlayFlag())
		{
			//�オ��t���O��on�Ȃ�
			if (block[i]->GetUpFlag())
			{
				//�u���b�N��pos,scale���g��
				block[i]->MovePosYUp(blockcount);
			}
			else
			{
				//�u���b�N��pos,scale���k��
				block[i]->MovePosYDown();

				if (sKeys_->IsTrigger(DIK_7))
				{
					blockcount = 1;
				}

				if (sKeys_->IsTrigger(DIK_8))
				{
					blockcount = 2;
				}

				if (sKeys_->IsTrigger(DIK_9))
				{
					blockcount = 3;
				}
			}
		}
	}

	//�i�[
	YGame::Transform CheckTrans1;

	//�i�[
	YGame::Transform CheckTrans2;

	//�v���C���[���샂�[�h��n�̎�
	if (player->GetPlayFlag())
	{
		//�v���C���[�𑀍삵�Ă���Ƃ��J�E���g��i�߂�
		for (int i = 0; i < block.size(); i++)
		{
			block[i]->CountDown();
		}

		//W�������ăW�����v����
		if (sKeys_->IsTrigger(DIK_W))
		{
			//�W�����v�t���O��off�̎�
			if (!player->GetJumpFlag())
			{
				//�d�͊֌W���Z�b�g
				player->JumpReset();
			}
		}

		//�v���C���[�W�����v����

		//�d�́A���͂����Z
		player->AddGravity();

		//�t�B���^�[�Əd�Ȃ��Ă��邩
		//player->SetClearFlag(BoxCollision(player->GetTransform(), filter->GetTransform(), true));

		//�W�����v�t���O��ON�Ȃ�
		if (player->GetJumpFlag())
		{
			if (player->GetJump() < 0.0f)
			{
				//���͕����蓮���
				DS.x_ = 0;
				DS.y_ = 0.0f;
				AW.x_ = 0;
				AW.y_ = 1.0f;
			}
			else
			{
				//���͕����蓮���
				DS.x_ = 0;
				DS.y_ = 1.0f;
				AW.x_ = 0;
				AW.y_ = 0.0f;
			}

			//�t�B���^�[�̒��ɂ��邩
			if (player->GetClearFlag() == false)
			{
				//�u���b�N���J��Ԃ�
				for (int i = 0; i < block.size(); i++)
				{
					//�u���b�N�̎�ނ��󔒂�
					if (block[i]->GetKind() != None)
					{
						//�u���b�N���t�B���^�[�̒��ɂ��邩
						if (block[i]->GetClearFlag() == false)
						{
							//�v���C���[��Transform����
							CheckTrans1 = player->GetTransform();

							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));

								//���ɖ��܂����u�ԃW�����v�t���O��false��
								player->SetJumpFlag(false);

								//�d�͊֌W���Z�b�g
								player->JumpReset();

								//�t���O��OFF��
								player->SetJumpFlag(false);
							}
						}
					}
				}
			}
		}
		//�W�����v��false�Ȃ��ɏC��
		//�W�����v��true�Ȃ牺�ɏC��
		//if (true)//player->GetJumpFlag())
		else
		{
			//�d�͉��Z
			player->SetGravity(0.3f);

			//���͕����蓮���
			DS.x_ = 0;
			DS.y_ = 0.0f;
			AW.x_ = 0;
			AW.y_ = 1.0f;

			//�t�B���^�[�̒��ɂ��邩
			if (player->GetClearFlag() == false)
			{
				//�u���b�N���J��Ԃ�
				for (int i = 0; i < block.size(); i++)
				{
					//�u���b�N�̎�ނ��󔒂�
					if (block[i]->GetKind() != None)
					{
						//�u���b�N���t�B���^�[�̒��ɂ��邩
						if (block[i]->GetClearFlag() == false)
						{
							//�v���C���[��Transform����
							CheckTrans1 = player->GetTransform();

							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));

								//���ɖ��܂����u�ԃW�����v�t���O��false��
								player->SetJumpFlag(false);
								//player->Landing();


								if (sKeys_->IsTrigger(DIK_C))
								{
									if (block[i]->GetUpFlag() == false)
									{
										block[i]->SetUpFlag(true);
										block[i]->SetUpTimer(50);
									}
								}
							}
						}
					}
				}
			}
		}

		//�E�������Ă�Ƃ����ɏC��
		if (sKeys_->IsDown(DIK_D))
		{
			//���͕����蓮���
			DS.x_ = 1.0f;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 0;

			//���ړ�
			player->PlayerMove(player->GetMovePos());

			//�t�B���^�[�̒��ɂ��邩
			if (player->GetClearFlag() == false)
			{
				//�u���b�N���J��Ԃ�
				for (int i = 0; i < block.size(); i++)
				{
					//�u���b�N�̎�ނ��󔒂�
					if (block[i]->GetKind() != None)
					{
						//�u���b�N���t�B���^�[�̒��ɂ��邩
						if (block[i]->GetClearFlag() == false)
						{
							//�v���C���[��Transform����
							CheckTrans1 = player->GetTransform();

							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								//������Ɩ߂�
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));
							}
						}
					}
				}
			}
		}

		//���������Ă�Ƃ��E�ɏC��
		if (sKeys_->IsDown(DIK_A))
		{
			//���͕����蓮���
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 1.0f;
			AW.y_ = 0;

			//���ړ�
			player->PlayerMove(player->GetMovePos());

			//�t�B���^�[�̒��ɂ��邩
			if (player->GetClearFlag() == false)
			{
				//�u���b�N���J��Ԃ�
				for (int i = 0; i < block.size(); i++)
				{
					//�u���b�N�̎�ނ��󔒂�
					if (block[i]->GetKind() != None)
					{
						//�u���b�N���t�B���^�[�̒��ɂ��邩
						if (block[i]->GetClearFlag() == false)
						{
							//�v���C���[��Transform����
							CheckTrans1 = player->GetTransform();

							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							//����O�ɏo��܂ŌJ��Ԃ�
							//while (BoxCollision(CheckTrans1, CheckTrans2, true))
							//{
								//������Ɩ߂�
							//player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

							if (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								player->SetPos(BoxCollision(CheckTrans1, CheckTrans2, DS, AW));
							}
							//�đ��
						//	CheckTrans1 = player->GetTransform();
						//}
						}
					}
				}
			}
		}
	}

	//�ʒu�X�V
	player->Update();

	// �S�[��
	goal_.UpdateMatrix();
	goalDra_.Update();


	// �V���X�V
	skydome_.Update();


	// �p�[�e�B�N���X�V
	particleMan_.Update();


	// �v���C���[���c�Ȃ�
	if (player->GetPlayFlag())
	{
		// �v���C���[�Ǐ]
		followPoint_ = player->GetPos();
	}
	// ����ȊO�Ȃ�
	else
	{
		// �v���C���[�Ǐ]
		followPoint_ = filter->GetTransform(5).pos_;
	}

	// �J�����X�V
	scrollCamera_.Update();

	// �r���[�v���W�F�N�V�����ɃJ�������
	transferVP_ = scrollCamera_.GetViewProjection();

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();

	//�S�[������
	if (BoxCollision(player->GetTransform(), goal_, false))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	// ���̃V�[����
	//if (sKeys_->IsTrigger(DIK_0))
	//{
	//	SceneManager::GetInstance()->Change("SELECT", "INFECTION");
	//	//SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	//}

	//���S����
	if (player->GetPos().y_ < -15)
	{
		SceneManager::GetInstance()->Change("PLAY", "BLACKOUT");
		player->Reset();
		filter->Reset();
	}
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{

}

void PlayScene::DrawModels()
{
	// �V���`��
	skydome_.Draw();

	// ----- Pre ----- // 

	// �v���C���[�O�`��
	player->PreDraw();

	// �u���b�N�O�`��
	for (size_t i = 0; i < block.size(); i++)
	{
		block[i]->Draw();
	}

	// �S�[���`��
	goalDra_.Draw();


	// �p�[�e�B�N��
	particleMan_.Draw();

	// �G�t�F�N�g
	effectMan_.Draw();

	// --------------- //


	// �t�B���^�[�`��
	filter->Draw();


	// ----- Post ----- //

	// �v���C���[��`��
	player->PostDraw();

	// --------------- //
}

void PlayScene::DrawSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// HUD�`��
	hud_.Draw();

	conSpr_->Draw(conObj_.get());
	conSpr2_->Draw(conObj2_.get());
	conSpr3_->Draw(conObj3_.get());
}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion