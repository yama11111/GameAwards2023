#include "ObjectManager.h"
#include <cassert>

void ObjectManager::Initialize()
{
	Clear();
	objCollMan_.Initialize();
}

void ObjectManager::Update()
{
	// オブジェクトnullなら削除
	objs_.remove_if([](IObject* obj) { return (obj == nullptr); });

	for (IObject* obj : objs_)
	{
		// 判定前更新
		obj->PreUpdate();

		// アタリ判定マネージャーに積む
		objCollMan_.PushBack(obj);
	}

	// アタリ判定マネージャーを更新
	objCollMan_.Update();

	for (IObject* obj : objs_)
	{
		// 判定後更新
		obj->PostUpdate();
	}
}

void ObjectManager::Draw()
{
	for (IObject* obj: objs_)
	{
		// 描画
		obj->Draw();
	}
}

void ObjectManager::Clear()
{
	// オブジェクト全削除
	if (objs_.empty() == false)
	{
		objs_.clear();
	}
}

void ObjectManager::PushBack(IObject* pObject)
{
	// nullチェック
	assert(pObject);
	
	// 挿入
	objs_.push_back(pObject);
}
