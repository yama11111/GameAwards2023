#pragma once
#include "SlimeActor.h"
#include "Model.h"
#include "Sprite3D.h"

class StageDrawerCommon
{
protected:
	// �ÓI�����X�v���C�g
	static std::array<std::unique_ptr<YGame::Sprite3D>, 10> sNumberSpr_;
	// �ÓI���f��
	static std::unique_ptr<YGame::Model> sBuildingModel_;
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;
public:
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);
};

class StageDrawer : 
	private StageDrawerCommon,
	private YGame::SlimeActor
{
private:
	// �j
	std::unique_ptr<YGame::Transform> core_;
	// �����p�I�u�W�F�N�g
	std::array<std::unique_ptr<YGame::Sprite3DObject>, 3> numObjs_;
	// �I�u�W�F�N�g
	std::vector<std::unique_ptr<YGame::ModelObject>> buildingObjs_;
	// �F
	std::unique_ptr<YGame::Color> color_;

	// ����
	int number_ = 0;
public:
	// ������
	void Initalize(YGame::Transform* pParent, const int number);
	// ���Z�b�g
	void Reset();
	// �X�V
	void Update();
	// �`�� (���f��)
	void DrawModel();
	// �`�� (�X�v���C�g3D)
	void DrawSprite3D();
};
