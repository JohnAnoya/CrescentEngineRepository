#include "LightSource.h"



LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColour_)
{
	position = position_;
	lightColour = lightColour_;
	ambient = ambient_;
	diffuse = diffuse_;
}


LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const {
	return position;
}

glm::vec3 LightSource::GetLightColour() const {
	return lightColour;
}

float LightSource::GetAmbient() const {
	return ambient;
}

float LightSource::GetDiffuse() const {
	return diffuse;
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetLightColour(glm::vec3 colour_) {
	lightColour = colour_; 
}

void LightSource::SetAmbient(float ambient_) {
	ambient = ambient_;
}

void LightSource::SetDiffuse(float diffuse_) {
	diffuse = diffuse_;
}