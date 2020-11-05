#ifndef VULKANTESTSCENE_H 
#define VULKANTESTSCENE_H 

#include "../../Engine/Core/CoreEngine.h"
class VulkanTestScene : public Scene
{
public:
	VulkanTestScene();
	virtual ~VulkanTestScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

};
#endif 