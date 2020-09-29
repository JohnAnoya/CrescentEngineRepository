#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include "BoundingBox.h"
#include "CollisionDetection.h"

struct Ray {
	glm::vec3 origin; 
	glm::vec3 direction; 
	float intersectionDistance; 

	inline Ray() {
		origin = glm::vec3(0.0f);
		direction = glm::vec3(0.0f); 
		intersectionDistance = 0.0f; 
	}

	inline Ray(glm::vec3 origin_, glm::vec3 direction_) {
		origin = origin_; 
		direction = direction_;
		intersectionDistance = 0.0f; 
	}

	inline Ray& operator =(const Ray& ray_) {
		origin = ray_.origin; 
		direction = ray_.direction; 
		intersectionDistance = 0.0f; 
	}

	inline bool IsColliding(BoundingBox* box_) {
		intersectionDistance = -1.0f; 
		return CollisionDetection::RayObbIntersection(this, box_); 
	}
};

#endif 