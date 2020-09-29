#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "../Rendering/3D/GameObject.h"

class Frustum
{
public:
	Frustum(const Frustum&) = delete;
	Frustum(Frustum&&) = delete;
	Frustum& operator=(const Frustum&) = delete;
	Frustum& operator=(Frustum&&) = delete;

	static Frustum* GetInstance();

	void ExtractFrustumResults(); 
	bool isWithinFrustum(glm::vec3 Position_); 
    
	float ProjectionMatrix[16]; 
	float ModelMatrix[16]; 
	float ClippingPlane[16];
	float frustumResult[6][4];
private:
	Frustum();
	~Frustum();

    static std::unique_ptr<Frustum> frustumInstance; //Also wasn't entirely sure if I wanted to make the class fully static, so I made it retrievable through an Instance
	friend std::default_delete<Frustum>;
};
#endif