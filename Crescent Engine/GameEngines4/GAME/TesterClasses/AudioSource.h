#ifndef AUDIOSOURCE_H 
#define AUDIOSOURCE_H 

#include <iostream>
#include "../../Engine/Core/Component.h"
#include "../../Engine/Rendering/3D/GameObject.h"
class AudioSource : public Component
{
public: 
	AudioSource(std::string soundName_, bool audioLooped_, bool audio3D_, bool streamType_);
	virtual ~AudioSource();
	virtual bool OnCreate(GameObject* parent_) override;
	virtual void Update(const float deltaTime_) override;

	void PlaySound(); 
	bool isPlaying(); 
private: 
	std::string soundName; 
	int channelID; 
};
#endif
