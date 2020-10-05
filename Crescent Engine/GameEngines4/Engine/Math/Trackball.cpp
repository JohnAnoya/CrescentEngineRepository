#include <glew.h>
#include <SDL.h>
#include "Trackball.h"
#include "../Core/CoreEngine.h"

Trackball::Trackball() {
	setWindowDimensions();
	mouseDown = false;
}

Trackball::~Trackball() {}

void Trackball::setWindowDimensions() {
	invNDC = glm::inverse(CoreEngine::GetInstance()->GetCamera()->GetView());
}

void Trackball::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		onLeftMouseDown(sdlEvent.button.x, sdlEvent.button.y);
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP) {
		onLeftMouseUp(sdlEvent.button.x, sdlEvent.button.y);
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		onMouseMove(sdlEvent.button.x, sdlEvent.button.y);
	}
	else if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
		setWindowDimensions();
	}
}

void Trackball::onLeftMouseDown(int x, int y) {
	beginV = glm::vec3(getMouseVector(x, y));
	mouseDown = true;
}

void Trackball::onLeftMouseUp(int x, int y) {
	mouseDown = false;
}

void Trackball::onMouseMove(int x, int y) {
	if (mouseDown == false) return;
	endV = glm::vec3(getMouseVector(x, y));
	float cosAngle = glm::dot(beginV, endV);
	float angle = acos(cosAngle) * 180.0f / M_PI; /// acos() returns radians must convert to degrees
	glm::vec3 rotAxis = glm::cross(beginV, endV);

	mouseRotationMatrix = glm::rotate(mouseRotationMatrix, angle, rotAxis) * mouseRotationMatrix;
	/// reset for the next mousemove
	beginV = endV;
}


const glm::vec4 Trackball::getMouseVector(int x, int y) {
	glm::vec4 mousePosition(static_cast<float>(x), static_cast<float>(y), 0.0f, 0.0f);

	glm::vec4 v = invNDC * mousePosition;
	float xSquared = v.x * v.x;
	float ySquared = v.y * v.y;
	if (xSquared + ySquared <= 0.5f) {
		v.z = sqrt(1.0f - (xSquared + ySquared));
	}
	else {
		v.z = 0.5f / sqrt(xSquared + ySquared);
		v = glm::normalize(v);
	}
	return v;
}
