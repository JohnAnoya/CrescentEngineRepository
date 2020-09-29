#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr; 
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr; 

CollisionHandler::CollisionHandler() {
	previousCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance() {
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler); 
	}

	return collisionInstance.get(); 
}

void CollisionHandler::OnCreate(float worldSize_) {
	previousCollisions.clear(); 
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* gameObject_) {
	scenePartition->AddObject(gameObject_);
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_) {
	Ray mouseRay = CollisionDetection::ScreenPositionToWorldRay(mousePosition_, CoreEngine::GetInstance()->GetWindowSize(), CoreEngine::GetInstance()->GetCamera());
	if (scenePartition != nullptr) {
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : previousCollisions) {
			if (c != hitResult && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
			c = nullptr;
		}
		previousCollisions.clear();

		if (hitResult) {
			previousCollisions.push_back(hitResult);
		}
	}
}

void CollisionHandler::OnDestroy() {
	delete scenePartition; 
	scenePartition = nullptr; 

	for (auto entry : previousCollisions) {
		entry = nullptr; 
	}
	previousCollisions.clear();
}
