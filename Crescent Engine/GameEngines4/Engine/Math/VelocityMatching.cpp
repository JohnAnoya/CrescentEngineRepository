#include "VelocityMatching.h"

VelocityMatching::VelocityMatching(glm::vec3 targetPosition_) {
	result = new SteeringOutput(); 
	targetPosition = targetPosition_;
	maxAcceleration = 1.0f; 
	timeToTarget = 5.5f; 
}

VelocityMatching::~VelocityMatching() {
	delete result; 
	result = nullptr; 
}

SteeringOutput* VelocityMatching::getSteering(GameObject* gameObject_) {
	sceneGameObjects = SceneGraph::GetInstance()->GetSceneGameObjects();

	for (it = sceneGameObjects.begin(); it != sceneGameObjects.end(); it++) {
		if (it->second != gameObject_) {
			result->SetLinear(it->second->GetPosition() - gameObject_->GetPosition()); //Get direction vector 
			result->SetLinear(result->GetLinear() / timeToTarget); //divide direction vector by timeToTarget

			//Clipping max acceleration 
			if (result->GetLinear().length() > maxAcceleration) {
				result->SetLinear(glm::normalize(result->GetLinear()));
				result->SetLinear(result->GetLinear() * maxAcceleration);
			}
		}
	}

	result->SetAngular(0.0f); //Defaulting angular to 0 because we aren't using it 
	return result;
}