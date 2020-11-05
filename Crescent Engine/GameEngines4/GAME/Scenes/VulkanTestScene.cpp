#include "VulkanTestScene.h"

VulkanTestScene::VulkanTestScene() : Scene()
{

}

VulkanTestScene::~VulkanTestScene()
{
	
}

bool VulkanTestScene::OnCreate()
{

	return true;
}

void VulkanTestScene::Update(const float deltaTime_)
{

}

void VulkanTestScene::Render()
{
	CoreEngine::GetInstance()->GetRenderer()->Render();
}
