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

bool BoxCollision(YGame::Transform obj1, YGame::Transform obj2)
{
	//�v���C���[�̏㉺���E
	float p_top = obj1.pos_.y_ - obj1.scale_.x_;
	float p_bottom = obj1.pos_.y_ + obj1.scale_.y_;
	float p_right = obj1.pos_.x_ + obj1.scale_.x_;
	float p_left = obj1.pos_.x_ - obj1.scale_.y_;

	//�t�B���^�[�̏㉺���E
	float f_top = obj2.pos_.y_ - obj2.scale_.x_;
	float f_bottom = obj2.pos_.y_ + obj2.scale_.y_;
	float f_right = obj2.pos_.x_ + obj2.scale_.x_;
	float f_left = obj2.pos_.x_ - obj2.scale_.x_;

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

//y����+�����|
YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeF, Vector2 DS, Vector2 AW)
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

YMath::Vector3 BoxCollision(Vector3 posP, Vector2 sizePRL, Vector2 sizePUD, Vector3 posF, Vector2 sizeLR, Vector2 sizeUD, Vector2 DS, Vector2 AW)
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

	// �`��N���X�S��
	DrawerManager::StaticInitialize(&isPlayer_, &transferVP_, &particleMan_);
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �v���C���[���쏉����
	isPlayer_ = true;

	float scaleVal = 1.0f;
	Vector3 scale = { scaleVal,scaleVal,scaleVal };

	// ----- �v���C���[ ----- //

	//// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	//player_.Initialize({ {-50.0f,0.0f,0.0f}, {}, scale * 2.0f });
	//// ����
	//direction_ = { +1.0f,0.0f,0.0f };
	//// �`��p�N���X������ (�e�g�����X�t�H�[���A�����A�����F)
	//playerDra_.Initialize(&player_, &direction_, IDrawer::Mode::Red);
	//
	//
	//// ----- �t�B���^�[ ----- //
	//
	//// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	//filter_.Initialize({ {0.0f,0.0f,0.0f}, {}, {6.0f,4.0f,1.0f} });
	//// �`��p�N���X������ (�e�g�����X�t�H�[��)
	//filterDra_.Initialize(&filter_);

	//
	//// ----- �u���b�N ----- //
	//
	//for (size_t i = 0; i < idx - 1; i++)
	//{
	//	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	//	block_[i].Initialize({{-40.0f + scaleVal * 4.0f * i,-4.0f * scaleVal,0.0f}, {}, scale});
	//	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	//	blockDra_[i].Initialize(&block_[i], IDrawer::Mode::Normal);
	//}

	player.Inilialize();

	// �t�B���^�[
	filter.Inilialize();

	// ----- �Q�[�g ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	gate_.Initialize({ {-20.0f,0.0f,0.0f}, {}, scale });
	// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	gateDra_.Initialize(&gate_, IDrawer::Mode::Red);


	// ----- �S�[�� ----- //

	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	goal_.Initialize({ {+4.0f * scaleVal,0.0f,0.0f}, {}, Vector3{0.5f,0.5f,0.5f} });
	// �`��p�N���X������ (�e�g�����X�t�H�[��)
	goalDra_.Initialize(&goal_);


	//�u���b�N
	for (int i = 0; i < blockCountY; i++)
	{
		for (int j = 0; j < blockCountX; j++)
		{
			Block* newBlock = new Block();

			newBlock->Inilialize();

			newBlock->nowKind = map[i][j];

			newBlock->sukeF = false;

			float size = 2.0f;

			newBlock->block_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
			newBlock->block_.pos_.y_ = ((blockCountY / 2) - i) * size;

			newBlock->block_.scale_.x_ = size / 4.0f;
			newBlock->block_.scale_.y_ = size / 4.0f;

			if (newBlock->nowKind == Start)
			{
				player.player_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				player.player_.pos_.y_ = ((blockCountY / 2) - i) * size;

				player.startPos.x_ = (j - (blockCountX / 3)) * size - 8;
				player.startPos.y_ = ((blockCountY / 2) - i) * size;

				newBlock->nowKind = Normal;
			}

			if (map[i][j] == Gorl)
			{
				goal_.pos_.x_ = (j - (blockCountX / 3)) * size - 8;
				goal_.pos_.y_ = ((blockCountY / 2) - i) * size;

				goal_.scale_.x_ = size / 4.0f;
				goal_.scale_.y_ = size / 4.0f;

				newBlock->nowKind = None;
			}

			if (map[i][j] == Collect)
			{
				//player.player_.pos_.x_ = (j - (blockCountX / 3)) * size - 5;
				//player.player_.pos_.y_ = ((blockCountY / 2) - i) * size;
			}

			//�i�[
			block.push_back(newBlock);
		}
	}

	for (int i = 0; i < block.size(); i++)
	{
		block[i]->SetMode();
	}

	// �u���b�N
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].Inilialize();
		block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 8;
		block[i].block_.pos_.y_ = -10;
		block[i].block_.scale_.x_ = 2;
		block[i].block_.scale_.y_ = 2;
	}*/

	nowMode = true;

	//// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	//block_[idx - 1].Initialize({ {0.0f,0.0f,0.0f}, {}, scale });
	//// �`��p�N���X������ (�e�g�����X�t�H�[���A�����F)
	//blockDra_[idx - 1].Initialize(&block_[idx - 1], IDrawer::Mode::Red);

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
		/*isPlayer_ = !isPlayer_;
		if (isPlayer_) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
		else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }*/
	}

	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
		player.Reset();
		filter.Reset();


		/*for (int i = 0; i < block.size(); i++)
		{
			block[i]->Reset();
		}*/

		/*for (int i = 0; i < blockCount; i++)
		{
			block[i].Reset();

			block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 8;
			block[i].block_.pos_.y_ = -10;
			block[i].block_.scale_.x_ = 2;
			block[i].block_.scale_.y_ = 2;
		}*/
	}

	//player_.UpdateMatrix();

	if (sKeys_->IsTrigger(DIK_K))
	{
		player.playerDra_.ChangeColorAnimation(IDrawer::Mode::Normal);
	}
	if (sKeys_->IsTrigger(DIK_L))
	{
		player.playerDra_.ChangeColorAnimation(IDrawer::Mode::Red);
	}
	//playerDra_.Update();

	// �Փ�
	if (sKeys_->IsTrigger(DIK_N))
	{
		player.playerDra_.SetIsCollFilter(true);
		filter.filterDra_.SetIsCollPlayer(true);
	}
	if (sKeys_->IsTrigger(DIK_M))
	{
		player.playerDra_.SetIsCollFilter(false);
		filter.filterDra_.SetIsCollPlayer(false);
	}

	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		if (player.GetsukeFlag() == false)
		{
			nowMode = !nowMode;

			isPlayer_ = !isPlayer_;
			if (isPlayer_) { hud_.SetPilot(HUDDrawerCommon::Pilot::Player); }
			else { hud_.SetPilot(HUDDrawerCommon::Pilot::Filter); }
		}
	}

	//�d��
	//player.player_.pos_.y_ -= 0.2f;


	if (nowMode)
	{
		//// �v���C���[
		//player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.5f;
		//player.player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 0.5f;
		if (sKeys_->IsTrigger(DIK_W) && player.JumpFlag == false)
		{
			//if (player.player_.pos_.y_ - 0.2f)
			//{
			player.Jump = 10;
			player.JumpPower = 0;

			player.JumpFlag = true;

			player.Gravity = 0;
			player.GravityPower = 0;
			//}
		}
	}
	else {
		// �t�B���^�[
		filter.filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.5f;
		filter.filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 0.5f;
	}

	RL.x_ = player.player_.scale_.x_ * 2;
	RL.y_ = player.player_.scale_.x_ * 2;

	WS.x_ = player.player_.scale_.y_ * 2;
	WS.y_ = player.player_.scale_.y_ * 2;

	filterSize.x_ = filter.filter_.scale_.x_;
	filterSize.y_ = filter.filter_.scale_.y_;

	Vector2 nowFSizeX = { filterSize.x_ * 3,filterSize.x_ * 3 };
	Vector2 nowFSizeY = { filterSize.y_ * 3,filterSize.y_ * 3 };

	// �t�B���^�[
	filter.Update();

	// �v���C���[
	//player.Update(filter.filter_, nowFSizeX, nowFSizeY);

	player.player_.UpdateMatrix();
	player.playerDra_.Update();

	// �u���b�N

	for (int i = 0; i < block.size(); i++)
	{
		block[i]->Update(filter.filter_);
	}

	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].Update(filter.filter_);
	}*/

	//YMath::Vector3 playerPosFold = player.player_.pos_ * 2;
	//YMath::Vector3 filterPosFold = filter.filter_.pos_ * 2;

	//�v���C���[�̏㉺���E
	float p_top = player.player_.pos_.y_ - player.player_.scale_.y_;
	float p_bottom = player.player_.pos_.y_ + player.player_.scale_.y_;
	float p_right = player.player_.pos_.x_ + player.player_.scale_.x_;
	float p_left = player.player_.pos_.x_ - player.player_.scale_.x_;

	//�t�B���^�[�̏㉺���E
	float g_top = goal_.pos_.y_ - goal_.scale_.y_;
	float g_bottom = goal_.pos_.y_ + goal_.scale_.y_;
	float g_right = goal_.pos_.x_ + goal_.scale_.x_;
	float g_left = goal_.pos_.x_ - goal_.scale_.x_;

	//�t�B���^�[�ɓ������Ă��邩
	if (BoxCollision(player.player_, goal_))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}

	if (nowMode)
	{
		if (player.JumpFlag == false)
		{
			if (player.Gravity < 2.0f)
				player.Gravity += player.GravityPower;

			if (player.GravityPower < 0.1f)
				player.GravityPower += 0.02f;
		}
		else if (player.JumpFlag == true)
		{
			//player.Gravity = 0;
			//player.GravityPower = 0;

			player.Jump -= player.JumpPower;

			if (player.JumpPower < 0.1f)
				player.JumpPower += 0.05f;

			//playerPos.y -= Jump;

			if (player.Jump < 9.5f)
			{
				player.JumpFlag = false;
				player.Jump = 0;
			}
		}

		if (!player.JumpFlag)
		{
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 1;

			player.player_.pos_.y_ -= player.Gravity * 0.1f;

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}

			player.player_.UpdateMatrix();
			player.playerDra_.Update();
		}

		if (player.JumpFlag)
		{
			DS.x_ = 0;
			DS.y_ = 1;
			AW.x_ = 0;
			AW.y_ = 0;

			player.player_.pos_.y_ += player.Jump * 0.1f;

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}

			player.player_.UpdateMatrix();
			player.playerDra_.Update();
		}

		if (sKeys_->IsDown(DIK_D))
		{
			DS.x_ = 1;
			DS.y_ = 0;
			AW.x_ = 0;
			AW.y_ = 0;

			if (nowMode)
			{
				player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.2f;
			}

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}
		}

		if (sKeys_->IsDown(DIK_A))
		{
			DS.x_ = 0;
			DS.y_ = 0;
			AW.x_ = 1;
			AW.y_ = 0;

			if (nowMode)
			{
				player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 0.2f;
			}

			if (player.GetsukeFlag() == false)
			{
				for (int i = 0; i < block.size(); i++)
				{
					if (block[i]->nowKind != None)
					{
						if (block[i]->sukeF == false)
						{
							YMath::Vector2 BlockSize;
							BlockSize.x_ = block[i]->block_.scale_.x_;
							BlockSize.y_ = block[i]->block_.scale_.y_;

							player.player_.pos_ =
								BoxCollision(
									player.player_.pos_,
									RL,
									WS,
									block[i]->block_.pos_,
									BlockSize,
									DS,
									AW
								);
						}
					}
				}
			}
		}
	}


	transferVP_.eye_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	transferVP_.target_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 0.1f;
	//}

	// �v���C���[
	player.Update(filter.filter_, nowFSizeX, nowFSizeY);

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


	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT", "BLACKOUT");
	}
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
	//playerDra_.PreDraw();
	//
	//// �u���b�N�O�`��
	//for (size_t i = 0; i < idx; i++)
	//{
	//	blockDra_[i].PreDraw();
	//}


	player.playerDra_.PreDraw();

	// �u���b�N�O�`��
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i]->nowKind == Normal || block[i]->nowKind == ColorB)
		{
			if (!block[i]->sukeF)
			{
				block[i]->blockDra_.PreDraw();
			}
		}
	}
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].blockDra_.PreDraw();
	}*/
	/*for (int i = 0; i < blockCount - (int)player.GetkadoFlag() - (int)player.GetsukeFlag(); i++)
	{
		block[i].blockDra_.PostDraw();
	}*/
	/*for (int i = 1; i < blockCountX - 2; i++)
	{
		block[i].blockDra_.PreDraw();
	}

	if (player.GetkadoFlag())
	{
		block[4].blockDra_.PreDraw();
	}

	if (player.GetsukeFlag())
	{
		block[3].blockDra_.PreDraw();
	}

	if (!player.JumpFlag)
	{
		block[1].blockDra_.PreDraw();
	}*/


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
	filter.Draw();


	// ----- Post ----- //

	//// �v���C���[��`��
	//playerDra_.PostDraw();
	//
	//// �u���b�N��`��
	//for (size_t i = 0; i < idx; i++)
	//{
	//	blockDra_[i].PostDraw();
	//}

	player.playerDra_.PostDraw();

	// �u���b�N��`��
	for (int i = 0; i < block.size(); i++)
	{
		if (block[i]->nowKind == Normal || block[i]->nowKind == ColorB)
		{
			if (!block[i]->sukeF)
			{
				block[i]->blockDra_.PostDraw();
			}
		}
	}
	/*for (int i = 0; i < blockCount; i++)
	{
		block[i].blockDra_.PostDraw();
	}*/

	/*for (int i = 1; i < blockCount - 2; i++)
	{
		block[i].blockDra_.PostDraw();
	}

	if (player.GetkadoFlag())
	{
		block[4].blockDra_.PostDraw();
	}

	if (player.GetsukeFlag())
	{
		block[3].blockDra_.PostDraw();
	}

	if (!player.JumpFlag)
	{
		block[1].blockDra_.PostDraw();
	}*/

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