#ifndef BOUNDINGBOX_H 
#define BOUNDINGBOX_H 

#include <glm/glm.hpp>
#include "CollisionDetection.h"

struct BoundingBox {
public:
	glm::vec3 maxVert, minVert;
	glm::mat4 transform; 

	inline BoundingBox() {
		maxVert = minVert = glm::vec3(0.0f); 
		transform = glm::mat4();
	}

	inline BoundingBox(glm::vec3 maxVert_, glm::vec3 minVert_, glm::mat4 transform_) {
		maxVert = maxVert_; 
		minVert = minVert_; 
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {
		glm::vec3 minCorner = GetTransformedPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformedPoint(maxVert, transform);

		glm::vec3 otherMinCorner = GetTransformedPoint(box_->minVert, box_->transform); 
		glm::vec3 otherMaxCorner = GetTransformedPoint(box_->maxVert, box_->transform);

		BoundingBox boxOne; 
		boxOne.minVert = minCorner;
		boxOne.maxVert = maxCorner; 

		BoundingBox boxTwo;
		boxTwo.minVert = otherMinCorner;
		boxTwo.maxVert = otherMaxCorner;

		return CollisionDetection::BoxOnBoxCollision(&boxOne, &boxTwo);
		//Update this return true to a Box - Box Collision result with min max Corner along other min and other max
	}

private :
	inline glm::vec3 GetTransformedPoint(glm::vec3 point_, glm::mat4 transform_) {
		return glm::vec3(transform_[3].x, transform_[3].y, transform_[3].z) + point_; 
	}
};

#endif //!BOUNDINGBOX_H