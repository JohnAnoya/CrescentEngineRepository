#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

CollisionDetection::~CollisionDetection() {

}

Ray CollisionDetection::ScreenPositionToWorldRay(glm::vec2 mouseCoords_, glm::vec2 screenSize_, Camera* camera_) {
	glm::vec4 rayStart_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEnd_NDC((mouseCoords_.x / screenSize_.x - 0.5f) * 2.0f, (mouseCoords_.y / screenSize_.y - 0.5f) * 2.0f, 0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView()); //ScreenPosition to WorldRay in 3D

	glm::vec4 rayStart_World = inverse * rayStart_NDC; 
	rayStart_World /= rayStart_World.w; 

	glm::vec4 rayEnd_World = inverse * rayEnd_NDC; 
	rayEnd_World /= rayEnd_World.w; 

	glm::vec3 rayDir_World(rayEnd_World - rayStart_World);
	rayDir_World = glm::normalize(rayDir_World);

	return Ray(glm::vec3(rayStart_World), rayDir_World);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_) {
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().x; 
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetClippingPlanes().y; 

	glm::vec3 obbPosition_World(box_->transform[3].x, box_->transform[3].y, box_->transform[3].z);
	glm::vec3 delta = obbPosition_World - ray_->origin;

	//x axis 
	glm::vec3 xAxis(box_->transform[0].x, box_->transform[0].y, box_->transform[0].z);
	float e1 = glm::dot(xAxis, delta);
	float f1 = glm::dot(ray_->direction, xAxis);

	if (fabs(f1) > 0.001f) {
		float t1 = (e1 + box_->minVert.x) / f1; 
		float t2 = (e1 + box_->maxVert.x) / f1; 

		if (t1 > t2) {
			float w = t1; 
			t1 = t2; 
			t2 = w; 
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false; 
		}
	}

	else {
		if (-e1 + box_->minVert.x > 0.0f || -e1 + box_->maxVert.x < 0.0f) {
			return false; 
		}
	}

	//Y axis 
	glm::vec3 yAxis(box_->transform[1].x, box_->transform[1].y, box_->transform[1].z);
	float e2 = glm::dot(yAxis, delta);
	float f2 = glm::dot(ray_->direction, yAxis);
	if (fabs(f2) > 0.001f) {
		float t1 = (e2 + box_->minVert.y) / f2;
		float t2 = (e2 + box_->maxVert.y) / f2;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}

	else {
		if (-e2 + box_->minVert.y > 0.0f || -e2 + box_->maxVert.y < 0.0f) {
			return false;
		}
	}

	//Z axis 
	glm::vec3 zAxis(box_->transform[2].x, box_->transform[2].y, box_->transform[2].z);
	float e3 = glm::dot(zAxis, delta);
	float f3 = glm::dot(ray_->direction, zAxis);
	if (fabs(f3) > 0.001f) {
		float t1 = (e3 + box_->minVert.z) / f3;
		float t2 = (e3 + box_->maxVert.z) / f3;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}

	else {
		if (-e3 + box_->minVert.z > 0.0f || -e3 + box_->maxVert.z < 0.0f) {
			return false;
		}
	}

	ray_->intersectionDistance = tMin; 
	return true; 
}


bool CollisionDetection::BoxOnBoxCollision(BoundingBox* boxOne_, BoundingBox* boxTwo_) {
	return((boxOne_->minVert.x <= boxTwo_->maxVert.x && boxOne_->maxVert.x >= boxTwo_->minVert.x) && (boxOne_->minVert.y <= boxTwo_->maxVert.y && boxOne_->maxVert.y >= boxTwo_->minVert.y) && (boxOne_->minVert.z <= boxTwo_->maxVert.z && boxOne_->maxVert.z >= boxTwo_->minVert.z));
}