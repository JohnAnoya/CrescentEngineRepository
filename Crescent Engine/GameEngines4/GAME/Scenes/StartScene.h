#ifndef STARTSCENE_H
#define STARTSCEME_H

#include "../../Engine/Core/CoreEngine.h"  

class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

};
#endif

