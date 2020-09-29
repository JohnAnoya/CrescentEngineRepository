#ifndef LIGHTSOURCE_H 
#define LIGHTSOURCE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition() const; 
	glm::vec3 GetLightColour() const; 
	float GetAmbient() const; 
	float GetDiffuse() const; 

	void SetPosition(glm::vec3 position_); 
	void SetLightColour(glm::vec3 colour_);
	void SetAmbient(float ambient_); 
	void SetDiffuse(float diffuse_);

private: 
	glm::vec3 position; 
	glm::vec3 lightColour; 
	float ambient; 
	float diffuse; 

};
#endif

