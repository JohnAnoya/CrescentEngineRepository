#ifndef TESTAISCENE_H
#define TESTAISCENE_H

#include "../TesterClasses/ComponentA.h"
#include "../TesterClasses/ComponentB.h"
#include "../TesterClasses/AIComponent.h"
#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>

class TestAIScene : public Scene
{
public:
	TestAIScene();
	virtual ~TestAIScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	LightSource* lightSource;
	std::string selectedObject;
	bool propertiesWindowOpen;
	bool hasObjects;
};
#endif
