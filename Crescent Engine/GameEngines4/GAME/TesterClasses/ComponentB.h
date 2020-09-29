#ifndef COMPONENTB_H
#define COMPONENTB_H

#include <iostream>
#include "../../Engine/Core/Component.h"

class ComponentB : public Component
{
public:
	ComponentB();
	virtual ~ComponentB();
	bool OnCreate(GameObject* parent_) override;
	void Update(const float deltaTime_) override;
};
#endif

