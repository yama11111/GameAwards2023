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
	//transform������
	pises_.Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

	//�u���b�N������
	block->Initialize();
}

void Pises::Update()
{

}

void Pises::Draw()
{
	block->Draw();
}
