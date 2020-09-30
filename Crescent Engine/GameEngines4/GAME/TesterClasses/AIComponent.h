#ifndef AICOMPONENT_H 
#define AICOMPONENT_H

#include <iostream>
#include "../../Engine/Core/Component.h"
#include "../../Engine/Math/KinematicSteeringOutput.h"
#include "../../Engine/Math/KinematicSeek.h"
#include "../../Engine/Math/KinematicArrive.h"

class AIComponent : public Component
{
public:
	AIComponent();
	virtual ~AIComponent();

	bool OnCreate(GameObject* parent_) override;
	void Update(const float deltaTime_) override;
private: 
	glm::vec3 desiredPosition; 
	KinematicArrive* kinematicArrive; 
	KinematicSeek* kinematicSeek; 
};
#endif 
