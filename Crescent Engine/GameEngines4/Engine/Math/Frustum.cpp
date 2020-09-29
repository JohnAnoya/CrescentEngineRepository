#include "Frustum.h"
#include "../Core/CoreEngine.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

std::unique_ptr<Frustum> Frustum::frustumInstance;

Frustum::Frustum() {

}

Frustum::~Frustum() {

}

Frustum* Frustum::GetInstance() {
	if (frustumInstance.get() == nullptr) {
		frustumInstance.reset(new Frustum);
	}

	return frustumInstance.get();
}

void Frustum::ExtractFrustumResults() {
	glGetFloatv(GL_PROJECTION_MATRIX, ProjectionMatrix); //Retrieving the projection matrix
	glGetFloatv(GL_MODELVIEW_MATRIX, ModelMatrix); //Retrieving the model matrix 
	
	{
		//MULTIPLYING THE TWO MATRICES AND THEN SETTING CLIPPING PLANE EQUAL TO THE RESULTS
		ClippingPlane[0] = ModelMatrix[0] * ProjectionMatrix[0] + ModelMatrix[1] * ProjectionMatrix[4] + ModelMatrix[2] * ProjectionMatrix[8] + ModelMatrix[3] * ProjectionMatrix[12];
		ClippingPlane[1] = ModelMatrix[0] * ProjectionMatrix[1] + ModelMatrix[1] * ProjectionMatrix[5] + ModelMatrix[2] * ProjectionMatrix[9] + ModelMatrix[3] * ProjectionMatrix[13];
		ClippingPlane[2] = ModelMatrix[0] * ProjectionMatrix[2] + ModelMatrix[1] * ProjectionMatrix[6] + ModelMatrix[2] * ProjectionMatrix[10] + ModelMatrix[3] * ProjectionMatrix[14];
		ClippingPlane[3] = ModelMatrix[0] * ProjectionMatrix[3] + ModelMatrix[1] * ProjectionMatrix[7] + ModelMatrix[2] * ProjectionMatrix[11] + ModelMatrix[3] * ProjectionMatrix[15];
		ClippingPlane[4] = ModelMatrix[4] * ProjectionMatrix[0] + ModelMatrix[5] * ProjectionMatrix[4] + ModelMatrix[6] * ProjectionMatrix[8] + ModelMatrix[7] * ProjectionMatrix[12];
		ClippingPlane[5] = ModelMatrix[4] * ProjectionMatrix[1] + ModelMatrix[5] * ProjectionMatrix[5] + ModelMatrix[6] * ProjectionMatrix[9] + ModelMatrix[7] * ProjectionMatrix[13];
		ClippingPlane[6] = ModelMatrix[4] * ProjectionMatrix[2] + ModelMatrix[5] * ProjectionMatrix[6] + ModelMatrix[6] * ProjectionMatrix[10] + ModelMatrix[7] * ProjectionMatrix[14];
		ClippingPlane[7] = ModelMatrix[4] * ProjectionMatrix[3] + ModelMatrix[5] * ProjectionMatrix[7] + ModelMatrix[6] * ProjectionMatrix[11] + ModelMatrix[7] * ProjectionMatrix[15];
		ClippingPlane[8] = ModelMatrix[8] * ProjectionMatrix[0] + ModelMatrix[9] * ProjectionMatrix[4] + ModelMatrix[10] * ProjectionMatrix[8] + ModelMatrix[11] * ProjectionMatrix[12];
		ClippingPlane[9] = ModelMatrix[8] * ProjectionMatrix[1] + ModelMatrix[9] * ProjectionMatrix[5] + ModelMatrix[10] * ProjectionMatrix[9] + ModelMatrix[11] * ProjectionMatrix[13];
		ClippingPlane[10] = ModelMatrix[8] * ProjectionMatrix[2] + ModelMatrix[9] * ProjectionMatrix[6] + ModelMatrix[10] * ProjectionMatrix[10] + ModelMatrix[11] * ProjectionMatrix[14];
		ClippingPlane[11] = ModelMatrix[8] * ProjectionMatrix[3] + ModelMatrix[9] * ProjectionMatrix[7] + ModelMatrix[10] * ProjectionMatrix[11] + ModelMatrix[11] * ProjectionMatrix[15];
		ClippingPlane[12] = ModelMatrix[12] * ProjectionMatrix[0] + ModelMatrix[13] * ProjectionMatrix[4] + ModelMatrix[14] * ProjectionMatrix[8] + ModelMatrix[15] * ProjectionMatrix[12];
		ClippingPlane[13] = ModelMatrix[12] * ProjectionMatrix[1] + ModelMatrix[13] * ProjectionMatrix[5] + ModelMatrix[14] * ProjectionMatrix[9] + ModelMatrix[15] * ProjectionMatrix[13];
		ClippingPlane[14] = ModelMatrix[12] * ProjectionMatrix[2] + ModelMatrix[13] * ProjectionMatrix[6] + ModelMatrix[14] * ProjectionMatrix[10] + ModelMatrix[15] * ProjectionMatrix[14];
		ClippingPlane[15] = ModelMatrix[12] * ProjectionMatrix[3] + ModelMatrix[13] * ProjectionMatrix[7] + ModelMatrix[14] * ProjectionMatrix[11] + ModelMatrix[15] * ProjectionMatrix[15];
	}

	//EXTRACTING RIGHT PLANE
	frustumResult[0][0] = ClippingPlane[3] - ClippingPlane[0]; 
	frustumResult[0][1] = ClippingPlane[7] - ClippingPlane[4];
	frustumResult[0][2] = ClippingPlane[11] - ClippingPlane[8];
	frustumResult[0][3] = ClippingPlane[15] - ClippingPlane[12];

	//NORMALIZED THE RESULTS
	frustumResult[0][0] /= glm::normalize(frustumResult[0][0]);
	frustumResult[0][1] = glm::normalize(frustumResult[0][1]);
	frustumResult[0][2] = glm::normalize(frustumResult[0][2]);
	frustumResult[0][3] = glm::normalize(frustumResult[0][3]);

	//EXTRACTING LEFT PLANE 
	frustumResult[1][0] = ClippingPlane[3] + ClippingPlane[0];
	frustumResult[1][1] = ClippingPlane[7] + ClippingPlane[4]; 
	frustumResult[1][2] = ClippingPlane[11] + ClippingPlane[8];
	frustumResult[1][3] = ClippingPlane[15] + ClippingPlane[12];

	//NORMALIZED THE RESULTS
	frustumResult[1][0] = glm::normalize(frustumResult[1][0]);
	frustumResult[1][1] = glm::normalize(frustumResult[1][1]);
	frustumResult[1][2] = glm::normalize(frustumResult[1][2]);
	frustumResult[1][3] = glm::normalize(frustumResult[1][3]);

	//EXTRACTING BOTTOM PLANE 
	frustumResult[2][0] = ClippingPlane[3] + ClippingPlane[1];
	frustumResult[2][1] = ClippingPlane[7] + ClippingPlane[5];
	frustumResult[2][2] = ClippingPlane[11] + ClippingPlane[9];
	frustumResult[2][3] = ClippingPlane[15] + ClippingPlane[13];

	//NORMALIZED THE RESULTS
	frustumResult[2][0] = glm::normalize(frustumResult[2][0]);
	frustumResult[2][1] = glm::normalize(frustumResult[2][1]);
	frustumResult[2][2] = glm::normalize(frustumResult[2][2]);
	frustumResult[2][3] = glm::normalize(frustumResult[2][3]);

	//EXTRACTING TOP PLANE
	frustumResult[3][0] = ClippingPlane[3] - ClippingPlane[1];
	frustumResult[3][1] = ClippingPlane[7] - ClippingPlane[5];
	frustumResult[3][2] = ClippingPlane[11] - ClippingPlane[9];
	frustumResult[3][3] = ClippingPlane[15] - ClippingPlane[13];
	
	//NORMALIZED THE RESULTS
	frustumResult[3][0] = glm::normalize(frustumResult[3][0]);
	frustumResult[3][1] = glm::normalize(frustumResult[3][1]);
	frustumResult[3][2] = glm::normalize(frustumResult[3][2]);
	frustumResult[3][3] = glm::normalize(frustumResult[3][3]);

	//EXTRACTING FAR PLANE 
	frustumResult[4][0] = ClippingPlane[3] - ClippingPlane[2];
	frustumResult[4][1] = ClippingPlane[7] - ClippingPlane[6];
	frustumResult[4][2] = ClippingPlane[11] - ClippingPlane[10];
	frustumResult[4][3] = ClippingPlane[15] - ClippingPlane[14];

	//NORMALIZED THE RESULTS
	frustumResult[4][0] = glm::normalize(frustumResult[4][0]);
	frustumResult[4][1] = glm::normalize(frustumResult[4][1]);
	frustumResult[4][2] = glm::normalize(frustumResult[4][2]);
	frustumResult[4][3] = glm::normalize(frustumResult[4][3]);

	//Last but not least... EXTRACTING NEAR PLANE 
	frustumResult[5][0] = ClippingPlane[3] + ClippingPlane[2];
	frustumResult[5][1] = ClippingPlane[7] + ClippingPlane[6];
	frustumResult[5][2] = ClippingPlane[11] + ClippingPlane[10];
	frustumResult[5][3] = ClippingPlane[15] + ClippingPlane[14];

	//NORMALIZED THE RESULTS
	frustumResult[5][0] = glm::normalize(frustumResult[5][0]);
	frustumResult[5][1] = glm::normalize(frustumResult[5][1]);
	frustumResult[5][2] = glm::normalize(frustumResult[5][2]);
	frustumResult[5][3] = glm::normalize(frustumResult[5][3]);
}

bool Frustum::isWithinFrustum(glm::vec3 Position_) {
	for (int planeIndex_ = 0; planeIndex_ < 6; planeIndex_++) {
		if (frustumResult[planeIndex_][0] * Position_.x + frustumResult[planeIndex_][1] * Position_.y + frustumResult[planeIndex_][2] * Position_.z + frustumResult[planeIndex_][3] <= 0.0f) {
			std::cout << "Object not in frustum, DO NOT RENDER." << std::endl; 
			return false; 
		}
	}

	return true; 
}
