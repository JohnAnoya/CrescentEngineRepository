#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../FX/LightSource.h"
#include <vector>


class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRoatation(float yaw_, float pitch_);
	void AddLightSource(LightSource* lightSource_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec2 GetClippingPlanes() const; 

	glm::vec3 GetPosition() const;
	std::vector<LightSource*> GetLightSources() const; 
	
	void ProcessMouseMovement(glm::vec2 offset_); 
	void ProcessMouseZoom(int y_);
	
private: 

	void UpdateCameraVector();
	void OnDestroy(); 

	glm::vec3 position;
	glm::mat4 perspective, orthographic;
	float fov, yaw, pitch, nearplane, farplane;
	glm::vec3 forward, up, right, worldUp;
	std::vector<LightSource*> lightsList;
};
#endif


