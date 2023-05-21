#pragma once
#include "Sprite2D.h"
#include "SlimeActor.h"
#include "Power.h"
#include <array>

class CardDrawerCommon
{
protected:
	// �ÓI�����X�v���C�g
	static std::array<YGame::Sprite2D*, 10> spNumberSpr_;
	// �ÓI�X�v���C�g
	static std::array<YGame::Sprite2D*,  2> spCardSprs_;
public:
	// �ÓI������
	static void StaticInitialize();
public:
	virtual ~CardDrawerCommon() = default;
};

class CardDrawer : 
	private CardDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �j
	std::unique_ptr<YGame::Transform> core_;
	
	// �����p�I�u�W�F�N�g
	std::array<std::unique_ptr<YGame::Sprite2D::Object>, 3> numObjs_;
	// �X�e�[�W�J�[�h�I�u�W�F�N�g
	std::unique_ptr<YGame::Sprite2D::Object> cardObjs_;
	// �F
	std::unique_ptr<YGame::CBColor> color_;

	// ����
	int number_ = 0;

	// �I������Ă��邩
	bool isSelected_ = false;
	// �I������Ă�����
	bool isElderSelected_ = false;
	// ���肳�ꂽ��
	bool isDetermined_ = false;

	// �ړ��p�C�[�W���O
	YMath::Ease<float> moveEas_;
	// �g��p�C�[�W���O
	YMath::Ease<float> scaleEas_;
	// �I��p�p���[
	YMath::Power selectPow_;

	// �����p�F
	std::unique_ptr<YGame::CBColor> clearCharaColor_;
	// �N���A������
	bool isClear_ = false;
public:
	// ������
	void Initialize(YGame::Transform* pParent, const int number, const bool isClear = false);
	// ���Z�b�g
	void Reset(const bool isClear = false);
	// �X�V
	void Update();
	// �`��
	void Draw();
public:
	// �I��ݒ�
	void SetSelect(const bool isSelect) { isSelected_ = isSelect; }
	// ����
	void Determine();
private:
	// �I���A�j���[�V�����X�V
	void UpdateSelectAnimation();
};

