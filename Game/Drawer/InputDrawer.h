#pragma once
#include "UIButtonDrawer.h"

// ���d��`���p
namespace YInput { class Keys; }

class InputDrawerCommon
{

protected:
	
	// �L�[
	static YInput::Keys* sKeys_;
	
	// ----- Button ----- //

	// WASD
	static YGame::UIButtonDrawer spKeyW_;
	static YGame::UIButtonDrawer spKeyA_;
	static YGame::UIButtonDrawer spKeyS_;
	static YGame::UIButtonDrawer spKeyD_;
	
	// SPACE
	static YGame::UIButtonDrawer spKeySpace_;
	
	// ESC
	static YGame::UIButtonDrawer spKeyEsc_;

public: 
	
	/// <summary>
	/// �ÓI������
	/// </summary>
	static void StaticInitialize();

	/// <summary>
	/// �ÓI�X�V
	/// </summary>
	static void StaticUpdate();

public:
	
	virtual ~InputDrawerCommon() = default;

};

class InputDrawer : private InputDrawerCommon
{

private:

	// WASD
	std::unique_ptr<YGame::Sprite2D::Object> keyWObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keyAObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keySObj_;
	std::unique_ptr<YGame::Sprite2D::Object> keyDObj_;
	
	// SPACE
	std::unique_ptr<YGame::Sprite2D::Object> keySpaceObj_;
	
	// ESC
	std::unique_ptr<YGame::Sprite2D::Object> keyEscObj_;

public:
	
	/// <summary> 
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void Reset();
	
	/// <summary> 
	/// �X�V
	/// </summary>
	void Update();
	
	/// <summary> 
	/// �`��
	/// </summary>
	void Draw();

};

