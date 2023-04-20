#pragma once
#include "Sprite2D.h"
#include <array>

// ���d��`���p
namespace YInput { class Keys; }

class InputDrawerCommon
{
protected:
	// �L�[
	static YInput::Keys* sKeys_;

	// WASD
	static YGame::Sprite2D* spKeyWASDSpr_;
	// WASD_PUSH
	static YGame::Sprite2D* spKeyWPushSpr_;
	static YGame::Sprite2D* spKeyAPushSpr_;
	static YGame::Sprite2D* spKeySPushSpr_;
	static YGame::Sprite2D* spKeyDPushSpr_;
	// S_DEAD
	static YGame::Sprite2D* spKeySDeadSpr_;
	// SPACE
	static std::array<YGame::Sprite2D*, 2> spKeySpaceSpr_;
	// ESC
	static std::array<YGame::Sprite2D*, 2> spKeyEscSpr_;
public:
	// �ÓI������
	static void StaticInitialize();
public:
	virtual ~InputDrawerCommon() = default;
};

class InputDrawer : private InputDrawerCommon
{
private:
	// ----- Object ----- //

	// WASD
	std::unique_ptr<YGame::Sprite2DObject> keyWASDObj_;
	// WASD_PUSH
	std::unique_ptr<YGame::Sprite2DObject> keyWObj_;
	std::unique_ptr<YGame::Sprite2DObject> keyAObj_;
	std::unique_ptr<YGame::Sprite2DObject> keySObj_;
	std::unique_ptr<YGame::Sprite2DObject> keyDObj_;
	// SPACE
	std::unique_ptr<YGame::Sprite2DObject> keySpaceObj_;
	// ESC
	std::unique_ptr<YGame::Sprite2DObject> keyEscObj_;

	// ----- �t���O ----- //

	// WASD
	bool isPushW_ = false;
	bool isPushA_ = false;
	bool isPushS_ = false;
	bool isPushD_ = false;
	// SPACE
	bool isPushSpace_ = false;
	// ESC
	bool isPushEsc_ = false;
public:
	// �������p�V�[��
	enum class SceneType
	{
		Title, // �^�C�g��
		Select, // �X�e�[�W�Z���N�g
		Play, // �Q�[��
	};
public:
	// ������
	void Initalize(const SceneType& sceneType);
	// ���Z�b�g
	void Reset(const SceneType& sceneType);
	// �X�V
	void Update();
	// �`��
	void Draw(const bool isPlayer);
private:
	// �t���O�X�V
	void UpdatePushFlags();
	// Object�X�V
	void UpdateObjects();
};

