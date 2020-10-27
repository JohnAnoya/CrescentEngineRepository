#include "AudioSource.h"
#include "../../Engine/Graphics/AudioHandler.h"

AudioSource::AudioSource(std::string soundName_, bool audioLooped_, bool audio3D_, bool streamType_) : Component() {
	channelID = -1; 
	soundName = soundName_;
	AudioHandler::GetInstance()->LoadSound(soundName, audioLooped_, audio3D_, streamType_);
}

AudioSource::~AudioSource() {

}

bool AudioSource::OnCreate(GameObject* parent_) {
	parent = parent_; 
	PlaySound(); 
	return true; 
}

void AudioSource::Update(const float deltaTime_) {
	if (parent != nullptr) {
		AudioHandler::GetInstance()->UpdateChannelPositionVelocity(channelID, parent->GetPosition()); 
	}
}

void AudioSource::PlaySound() {
	channelID = AudioHandler::GetInstance()->PlaySound(soundName, parent->GetPosition());
}

bool AudioSource::isPlaying() {
	return AudioHandler::GetInstance()->isPlaying(channelID);
}