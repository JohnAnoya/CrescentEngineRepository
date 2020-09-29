#ifndef COMPONENTA_H
#define COMPONENTA_H

#include <iostream>
#include "../../Engine/Core/Component.h"

class ComponentA : public Component
{
public: 
	ComponentA();
	virtual ~ComponentA();
	bool OnCreate(GameObject* parent_) override;
	void Update(const float deltaTime_) override; 
};
#endif 

