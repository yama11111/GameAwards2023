#include "ObjectManager.h"
#include <cassert>

void ObjectManager::Initialize()
{
	Clear();
	objCollMan_.Initialize();
}

void ObjectManager::Update()
{
	// �I�u�W�F�N�gnull�Ȃ�폜
	objs_.remove_if([](IObject* obj) { return (obj == nullptr); });

	for (IObject* obj : objs_)
	{
		// ����O�X�V
		obj->PreUpdate();

		// �A�^������}�l�[�W���[�ɐς�
		objCollMan_.PushBack(obj);
	}

	// �A�^������}�l�[�W���[���X�V
	objCollMan_.Update();

	for (IObject* obj : objs_)
	{
		// �����X�V
		obj->PostUpdate();
	}
}

void ObjectManager::Draw()
{
	for (IObject* obj: objs_)
	{
		// �`��
		obj->Draw();
	}
}

void ObjectManager::Clear()
{
	// �I�u�W�F�N�g�S�폜
	if (objs_.empty() == false)
	{
		objs_.clear();
	}
}

void ObjectManager::PushBack(IObject* pObject)
{
	// null�`�F�b�N
	assert(pObject);
	
	// �}��
	objs_.push_back(pObject);
}
