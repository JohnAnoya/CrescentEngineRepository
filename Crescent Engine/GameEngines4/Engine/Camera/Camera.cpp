#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera()
{
	position = glm::vec3(0.0f);
	fov = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearplane = 2.0f;
	farplane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;
	
	perspective = glm::perspective(fov, CoreEngine::GetInstance()->GetWindowSize().x / 
		CoreEngine::GetInstance()->GetWindowSize().y, nearplane, farplane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x,
		0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVector();
}

Camera::~Camera()
{
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVector();
}

void Camera::SetRoatation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVector();
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const {
	return glm::vec2(nearplane, farplane);
}


void Camera::AddLightSource(LightSource* lightSource_) {
	lightsList.push_back(lightSource_);
}

std::vector<LightSource*> Camera::GetLightSources() const {
	return lightsList;
}

void Camera::ProcessMouseMovement(glm::vec2 offset_) {
	offset_ *= 0.05f; 

	yaw += offset_.x; 
	pitch += offset_.y; 

	if (pitch > 89.0f) {
		pitch = 89.0f; 
	}

	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw < 0.0f) {
		yaw += 360.0f; 
	}

	if (yaw > 360.0f) {
		yaw -= 360.0f; 
	}

	UpdateCameraVector();
}

void Camera::ProcessMouseZoom(int y_) {
	if (y_ < 0 || y_ > 0) {
		position += static_cast<float>(y_) * (forward * 2.0f);
	}
	UpdateCameraVector();
}

void Camera::UpdateCameraVector()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

void Camera::OnDestroy() {
	if (lightsList.size() > 0)
	{
		for (auto lights : lightsList)
		{
			delete lights;
			lights = nullptr; 
		}
	}	
}
