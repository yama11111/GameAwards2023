#include "Pises.h"
#include "imgui.h"

Pises::Pises()
{
	
}

Pises::~Pises()
{

}

void Pises::Initialize()
{
	//transform‰Šú‰»
	pises_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });
}

void Pises::Update()
{

}

void Pises::Draw()
{
	block->Draw();
}
