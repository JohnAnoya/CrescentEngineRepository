#include "SeparationSteering.h"

SeparationSteering::SeparationSteering(glm::vec3 targetPosition_) {
	result = new SteeringOutput();
	targetPosition = targetPosition_;
	maxAcceleration = 1.0f; 
	Threshold = 1.0f; 
}

SeparationSteering::~SeparationSteering() {
	delete result;
	result = nullptr;
}

SteeringOutput* SeparationSteering::getSteering(GameObject* gameObject_) {
	sceneGameObjects = SceneGraph::GetInstance()->GetSceneGameObjects();

	for (it = sceneGameObjects.begin(); it != sceneGameObjects.end(); it++) {
		if (it->second != gameObject_) {
			result->SetLinear(gameObject_->GetPosition() - it->second->GetPosition());

			if (result->GetLinear().length() < Threshold) {
				float strength;

				if (result->GetLinear().length() < maxAcceleration) {
					strength = result->GetLinear().length();
				}

				else {
					strength = maxAcceleration;
				}

				result->SetLinear(glm::normalize(result->GetLinear()));
				result->SetLinear(result->GetLinear() * strength);
			}
		}
	}

	return result;
}