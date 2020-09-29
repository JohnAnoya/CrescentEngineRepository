#ifndef COMPONENT_H 
#define COMPONENT_H

class GameObject; 

class Component
{
public: 
	Component() { parent = nullptr; }
	virtual ~Component() { parent = 0; }
	virtual bool OnCreate(GameObject* parent_) = 0; 
	virtual void Update(const float deltaTime_) = 0;

protected: 
	GameObject* parent;
};

#endif //!Component_H
