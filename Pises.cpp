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
	//transform初期化
	pises_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

	//ブロック初期化
	block->Initialize();
}

void Pises::Update()
{

}

void Pises::Draw()
{
	block->Draw();
}
