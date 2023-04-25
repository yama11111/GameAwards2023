#pragma once
#include "SlimeActor.h"
#include "TowerDrawer.h"
#include "Sprite3D.h"

class StageDrawerCommon
{

protected:
	
	// �ÓI�����X�v���C�g
	static std::array<YGame::Sprite3D*, 10> spNumberSpr_;
	
	// �r���[�v���W�F�N�V�����|�C���^
	static YGame::ViewProjection* spVP_;

public:
	
	// �ÓI������
	static void StaticInitialize(YGame::ViewProjection* pVP);

public:
	
	virtual ~StageDrawerCommon() = default;

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
	
	// �^���[�`��N���X
	TowerDrawer towerDra_;

	// �F
	std::unique_ptr<YGame::Color> color_;

	
	// ����
	int number_ = 0;

public:
	
	// ������
	void Initialize(YGame::Transform* pParent, const int number);
	
	// ���Z�b�g
	void Reset();
	
	// �X�V
	void Update();

	// �`�� (���f��)
	void DrawModel();

	// �`�� (�X�v���C�g3D)
	void DrawSprite3D();

};

