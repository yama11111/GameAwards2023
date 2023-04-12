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
	YMath::Vector3 nowPosP = posP.pos_;
	YMath::Vector3 nowPosF = posF.pos_;

	//�v���C���[�̏㉺���E
	float p_top = nowPosP.y_ - posP.scale_.x_;
	float p_bottom = nowPosP.y_ + posP.scale_.y_;
	float p_right = nowPosP.x_ + posP.scale_.x_;
	float p_left = nowPosP.x_ - posP.scale_.y_;

	//�t�B���^�[�̏㉺���E
	float f_top = nowPosF.y_ - posF.scale_.y_;
	float f_bottom = nowPosF.y_ + posF.scale_.y_;
	float f_right = nowPosF.x_ + posF.scale_.x_;
	float f_left = nowPosF.x_ - posF.scale_.x_;

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
			p_top = nowPosP.y_ - posP.scale_.x_;
			p_bottom = nowPosP.y_ + posP.scale_.y_;
			p_right = nowPosP.x_ + posP.scale_.x_;
			p_left = nowPosP.x_ - posP.scale_.y_;
		}
	}

	return nowPosP;
}

#pragma region �ǂݍ���
void PlayScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

	// �p�[�e�B�N��
	ParticleManager::StaticInitialize(&transferVP_);

	// �G�t�F�N�g
	EffectManager::StaticInitialize(&particleMan_);

	bool IsplayF = player->GetClearFlag();

	// �`��N���X�S��
	DrawerManager::StaticInitialize(&IsplayF, &transferVP_, &particleMan_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �v���C���[���쏉����
	//isPlayer_ = true;
	//player_->SetClearFlag(true);
	//filter_->SetNowMove(player_->GetClearFlag());

	float scaleVal = harfScale;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- �v���C���[ ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	player->Initialize({ -50.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f }, scale * 2.0f);

	//�f�B���N�V����(����)
	player->SetDirection(YMath::Vector3{ +1.0f, 0.0f, 0.0f });

	//
	//player_->SetClearFlag(true);

	// ----- �t�B���^�[ ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	filter->Initialize({ 0.0f, 0.0f, 3.0f }, {}, { 1.5f,1.5f,1.5f });

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
			Block* newBlock = new Block();

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
			block.push_back(newBlock);
		}
	}

	//��ނɂ���ău���b�N��ύX
	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	// ----- �Q�[�g ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);


	// �V��������
	skydome_.Initialize();

	// HUD������
	hud_.Initalize();

	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({ {0,0,-50} });
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
	}

	//�f�o�b�O�p�̃��Z�b�g�{�^��
	if (sKeys_->IsTrigger(DIK_R))
	{
		player->Reset();
		filter->Reset();
	}

	//�i�[�pVector
	YMath::Vector3 result(0.0f, 0.0f, 0.0f);

	//�l��0��
	player->SetMovePos(result);
	filter->SetMovePos(result);

	//���͏�Ԃ����
	result.x_ = sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.5f;
	result.y_ = sKeys_->Vertical(Keys::MoveStandard::WASD) * 0.5f;
	result.z_ = 0.0f;

	//���̃A�N�e�B�u���
	if (player->GetPlayFlag())
	{
		//�v���C���[��y���̓W�����v�̂�
		result.y_ = 0.0f;

		//�v���C���[�̈ړ��ʊi�[
		player->SetMovePos(result);
	}
	else
	{
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
		block[i]->Update(filter->GetTransform());
	}

	//�i�[
	YGame::Transform CheckTrans1 = player->GetTransform();

	//�i�[
	YGame::Transform CheckTrans2;

	//�v���C���[���샂�[�h��n�̎�
	if (player->GetPlayFlag())
	{
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
		/*if (player->GetJumpFlag())
		{*/
		//�d�́A���͂����Z
		//player->AddGravity();
		//}


		////���͕����蓮���
		//DS.x_ = 0;
		//DS.y_ = 0;
		//AW.x_ = 0;
		//AW.y_ = 0.1f;

		////�t�B���^�[�̒��ɂ��邩
		//if (player->GetClearFlag() == false)
		//{
		//	//�u���b�N���J��Ԃ�
		//	for (int i = 0; i < block.size(); i++)
		//	{
		//		//�u���b�N�̎�ނ��󔒂�
		//		if (block[i]->GetKind() != None)
		//		{
		//			//�u���b�N���t�B���^�[�̒��ɂ��邩
		//			if (block[i]->GetClearFlag() == false)
		//			{
		//				//�u���b�N��Transform����
		//				CheckTrans2 = block[i]->GetTransform();

		//				//����O�ɏo��܂ŌJ��Ԃ�
		//				while (BoxCollision(CheckTrans1, CheckTrans2, true))
		//				{
		//					//������Ɩ߂�
		//					player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

		//					//�đ��
		//					CheckTrans1 = player->GetTransform();

		//					//���ɖ��܂����u�ԃW�����v�t���O��false��
		//					player->SetJumpFlag(false);
		//				}
		//			}
		//		}
		//	}
		//}

		////�W�����v��false�Ȃ��ɏC��
		////�W�����v��true�Ȃ牺�ɏC��
		//if (player->GetJumpFlag())
		//{
		//	//���͕����蓮���
		//	DS.x_ = 0;
		//	DS.y_ = 0.1f;
		//	AW.x_ = 0;
		//	AW.y_ = 0;

		//	//�t�B���^�[�̒��ɂ��邩
		//	if (player->GetClearFlag() == false)
		//	{
		//		//�u���b�N���J��Ԃ�
		//		for (int i = 0; i < block.size(); i++)
		//		{
		//			//�u���b�N�̎�ނ��󔒂�
		//			if (block[i]->GetKind() != None)
		//			{
		//				//�u���b�N���t�B���^�[�̒��ɂ��邩
		//				if (block[i]->GetClearFlag() == false)
		//				{
		//					//�u���b�N��Transform����
		//					CheckTrans2 = block[i]->GetTransform();

		//					//����O�ɏo��܂ŌJ��Ԃ�
		//					while (BoxCollision(CheckTrans1, CheckTrans2, true))
		//					{
		//						//������Ɩ߂�
		//						player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

		//						//�đ��
		//						CheckTrans1 = player->GetTransform();
		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		//���ړ�
		player->PlayerMove(player->GetMovePos());

		//�E�������Ă�Ƃ����ɏC��
		if (sKeys_->IsDown(DIK_D))
		{
			//���͕����蓮���
			DS.x_ = 0.01f;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 0;

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
							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							//����O�ɏo��܂ŌJ��Ԃ�
							while (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								//������Ɩ߂�
								player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

								//�đ��
								CheckTrans1 = player->GetTransform();
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
			AW.x_ = 0.01f;
			AW.y_ = 0;

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
							//�u���b�N��Transform����
							CheckTrans2 = block[i]->GetTransform();

							//����O�ɏo��܂ŌJ��Ԃ�
							while (BoxCollision(CheckTrans1, CheckTrans2, true))
							{
								//������Ɩ߂�
								player->PlayerMove(Vector3((AW.x_ - DS.x_), (AW.y_ - DS.y_), 0.0f));

								//�đ��
								CheckTrans1 = player->GetTransform();
							}
						}
					}
				}
			}
		}
	}


	// �Q�[�g
	gate_.UpdateMatrix();
	gateDra_.Update();


	// �S�[��
	goal_.UpdateMatrix();
	goalDra_.Update();


	// �V���X�V
	skydome_.Update();


	// �p�[�e�B�N���X�V
	particleMan_.Update();


	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();

	//�S�[������
	if (BoxCollision(player->GetTransform(), goal_, false))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "INFECTION");
	}

	/*bool check = BoxCollision(player->GetTransform(), filter->GetTransform(), true);

	ImGui::Begin("F");
	ImGui::Checkbox("F", &check);
	ImGui::End();*/

	//rightleft�ŉ��ړ�
	transferVP_.eye_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	transferVP_.target_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;

	//updown�ŉ��s���m�F
	transferVP_.eye_.z_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 0.1f;
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{

}

void PlayScene::DrawBackSprite3Ds()
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
		block[i]->PreDraw();
	}

	// �Q�[�g�O�`��
	//gateDra_.PreDraw();

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

	// �u���b�N��`��
	for (size_t i = 0; i < block.size(); i++)
	{
		block[i]->PostDraw();
	}

	// �Q�[�g��`��
	//gateDra_.PostDraw();

	// --------------- //
}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// HUD�`��
	hud_.Draw();
}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g2D----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawBackSprite3Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g2D ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion