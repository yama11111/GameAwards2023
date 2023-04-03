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
			nowPosP.x_ -= DS.x_;
			nowPosP.y_ -= DS.y_;

			nowPosP.x_ += AW.x_;
			nowPosP.y_ += AW.y_;

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
			nowPosP.x_ -= Ds.x_;
			nowPosP.y_ -= Ds.y_;
			nowPosP.x_ += Aw.x_;
			nowPosP.y_ += Aw.y_;

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

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- �X�v���C�g (3D) ----- //


	// ------- ���f�� ------- //

	cubeMod_.reset(Model::Create());

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
	// �v���C���[
	player.Inilialize();

	// �t�B���^�[
	filter.Inilialize();

	// �u���b�N
	for (int i = 0; i < blockCount; i++)
	{
		block[i].Inilialize();
		block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 24;
		block[i].block_.pos_.y_ = -18;
		block[i].block_.scale_.x_ = 2;
		block[i].block_.scale_.y_ = 2;
	}

	// �V��������
	skydome_.Initialize();

	// �p�[�e�B�N��������
	particleMan_.Initialize();

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize({ {0,0,-100} });

	nowMode = true;
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
	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
		player.Reset();
		filter.Reset();

		for (int i = 0; i < blockCount; i++)
		{
			block[i].Reset();

			block[i].block_.pos_.x_ = (i - (blockCount / 2)) * 24;
			block[i].block_.pos_.y_ = -18;
			block[i].block_.scale_.x_ = 2;
			block[i].block_.scale_.y_ = 2;
		}
	}

	// ���̃V�[����s
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	if (sKeys_->IsTrigger(DIK_Z))
	{
		for (int i = 0; i < blockCount; i++)
		{
			block[i].block_.pos_.y_ -= 1;
		}
	}

	if (sKeys_->IsTrigger(DIK_SPACE))
	{
		nowMode = !nowMode;
	}

	if (nowMode)
	{
		// �v���C���[
		player.player_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::WASD) * 2.0f;
		player.player_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::WASD) * 2.0f;
	}
	else {
		// �t�B���^�[
		filter.filter_.pos_.x_ += sKeys_->Horizontal(Keys::MoveStandard::Arrow) * 2.0f;
		filter.filter_.pos_.y_ += sKeys_->Vertical(Keys::MoveStandard::Arrow) * 2.0f;
	}

	RL.x_ = player.player_.scale_.x_ * 2.0f;
	RL.y_ = player.player_.scale_.x_ * 2.0f;

	WS.x_ = player.player_.scale_.y_ * 2.0f;
	WS.y_ = player.player_.scale_.y_ * 2.0f;

	filterSize.x_ = filter.filter_.scale_.x_ * 4.0f;
	filterSize.y_ = filter.filter_.scale_.y_ * 4.0f;

	DS.x_ = (float)sKeys_->IsRight(Keys::MoveStandard::WASD);
	DS.y_ = (float)sKeys_->IsUp(Keys::MoveStandard::WASD);
	AW.x_ = (float)sKeys_->IsLeft(Keys::MoveStandard::WASD);
	AW.y_ = (float)sKeys_->IsUnder(Keys::MoveStandard::WASD);

	Vector2 nowFSizeX = { filterSize.x_,filterSize.x_ };
	Vector2 nowFSizeY = { filterSize.y_,filterSize.y_ };

	// �t�B���^�[
	filter.Update();

	// �v���C���[
	player.Update(filter.filter_, nowFSizeX, nowFSizeY);

	// �u���b�N
	for (int i = 0; i < blockCount; i++)
	{
		block[i].Update();
	}

	//YMath::Vector3 playerPosFold = player.player_.pos_ * 2;
	//YMath::Vector3 filterPosFold = filter.filter_.pos_ * 2;

	if (nowMode)
	{
		//Transform posP, Vector2 sizePRL, Vector2 sizePUD, Transform posF, Vector2 sizeF, Vector2 DS, Vector2 AW
		/*player.player_.pos_ =
			BoxCollision(
				player.player_.pos_,
				RL,
				WS,
				filter.filter_.pos_,
				filterSize,
				DS,
				AW
			);*/

		for (int i = 0; i < blockCount; i++)
		{
			YMath::Vector2 BlockSize;
			BlockSize.x_ = block[i].block_.scale_.x_;
			BlockSize.y_ = block[i].block_.scale_.y_;

			player.player_.pos_ =
				BoxCollision(
					player.player_.pos_,
					RL,
					WS,
					block[i].block_.pos_,
					BlockSize,
					DS,
					AW

				);
		}
	}

	// �V���X�V
	skydome_.Update();

	// �p�[�e�B�N���X�V
	particleMan_.Update();

	// �r���[�v���W�F�N�V����
	transferVP_.UpdateMatrix();
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
	player.playerDra_.PreDraw();

	// �u���b�N�O�`��
	/*for (int i = 0; i < blockCount - (int)player.GetkadoFlag() - (int)player.GetsukeFlag(); i++)
	{
		block[i].blockDra_.PostDraw();
	}*/
	for (int i = 0; i < blockCount - 2; i++)
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
	
	// �p�[�e�B�N��
	particleMan_.Draw();

	// �G�t�F�N�g
	effectMan_.Draw();

	// --------------- //

	// �t�B���^�[�`��
	filter.filterDra_.Draw();

	// ----- Post ----- //

	// �v���C���[��`��
	player.playerDra_.PostDraw();

	// �u���b�N��`��
	for (int i = 0; i < blockCount - 2; i++)
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

	// --------------- //
}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{

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