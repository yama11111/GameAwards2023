#include "Filter.h"

Filter::Filter()
{
	// フィルター
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_.m_);

}

Filter::~Filter()
{
}

void Filter::Inilialize()
{
	// フィルター
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_.m_);

	filter_.pos_.x_ = 20.0f;
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
	// フィルター
	filter_.Initialize({ {}, {}, {5.0f,5.0f,5.0f} });
	filterDra_.Initialize(&filter_.m_);
}
