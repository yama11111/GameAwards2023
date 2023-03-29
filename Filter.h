#pragma once
#include "Vector2.h"

class Filter
{
public:
	Filter();
	~Filter();

	void Inilialize();
	void Update();
	void Draw();
private:
	YMath::Vector2 filterPos = { 0,0 };
	YMath::Vector2 filterSize = { 128,64 };
};

