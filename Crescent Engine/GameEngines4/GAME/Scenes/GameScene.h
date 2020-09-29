#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../TesterClasses/ComponentA.h"
#include "../../Engine/Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	LightSource* lightSource; 
};
#endif

