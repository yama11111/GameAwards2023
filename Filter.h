#pragma once
#include "Vector2.h"
#include "FilterDrawer.h"

class Filter
{
public:
	Filter();
	~Filter();

	void Inilialize();
	void Update();
	void Draw();
	void Reset();

	// �t�B���^�[
	YGame::Transform filter_;
	// �t�B���^�[�`��N���X
	FilterDrawer filterDra_;
private:

	//// �t�B���^�[
	//YGame::Transform filter_;
	//// �t�B���^�[�`��N���X
	//FilterDrawer filterDra_;

	/*YMath::Vector2 filterPos = { 0,0 };
	YMath::Vector2 filterSize = { 128,64 };*/
};

