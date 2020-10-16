#ifndef AICOMPONENT_H 
#define AICOMPONENT_H

#include <iostream>
#include "../../Engine/Core/Component.h"
#include "../../Engine/Math/KinematicSteeringOutput.h"
#include "../../Engine/Math/KinematicSeek.h"
#include "../../Engine/Math/KinematicArrive.h"
#include "../../Engine/Math/BlendedSteering.h"

class AIComponent : public Component
{
public:
	AIComponent(glm::vec3 targetPosition_);
	virtual ~AIComponent();

	bool OnCreate(GameObject* parent_) override;
	void Update(const float deltaTime_) override;
	void SetTargetPosition(glm::vec3 targetPosition_); 
private: 
	glm::vec3 targetPosition;
	glm::vec3 desiredPosition; 
	KinematicArrive* kinematicArrive; 
	KinematicSeek* kinematicSeek; 
	BlendedSteering* blendedSteering; 
};
#endif 
