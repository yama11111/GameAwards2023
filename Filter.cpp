#include "Filter.h"

Filter::Filter()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_);

}

Filter::~Filter()
{
}

void Filter::Inilialize()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });
	filterDra_.Initialize(&filter_);

	filter_.pos_.x_ = 0.0f;
}

void Filter::Update()
{
	filter_.UpdateMatrix();
	filterDra_.Update();
}

void Filter::Draw()
{
	filterDra_.Draw();
}

void Filter::Reset()
{
	// �t�B���^�[
	filter_.Initialize({ {}, {}, {2.0f,2.0f,2.0f} });
	filterDra_.Reset();
}
