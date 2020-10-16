#include "CohesionSteering.h"

CohesionSteering::CohesionSteering(glm::vec3 targetPosition_) {
	result = new SteeringOutput();
	targetPosition = targetPosition_;
	maxAcceleration = 10.0f;
	Threshold = 1.0f;
}

CohesionSteering::~CohesionSteering() {
	delete result;
	result = nullptr;
}

SteeringOutput* CohesionSteering::getSteering(GameObject* gameObject_) {
	sceneGameObjects = SceneGraph::GetInstance()->GetSceneGameObjects();

	for (it = sceneGameObjects.begin(); it != sceneGameObjects.end(); it++) {
		if (it->second != gameObject_) {
			result->SetLinear(it->second->GetPosition() - gameObject_->GetPosition());

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