#ifndef TRACKBALL_H
#define	TRACKBALL_H
#include <glm/glm.hpp>
union SDL_Event;

class Trackball {
private:
	bool mouseDown;
	glm::mat4 mouseRotationMatrix;	/// This the final rotation matrix
	glm::mat4 invNDC;			/// the inverse of the viewportNDC matrix
	glm::vec3 beginV, endV;		/// Begin and end points after being transformed by invNDC

public:
	Trackball();
	~Trackball();
	Trackball(const Trackball&) = delete;
	Trackball(Trackball&&) = delete;
	Trackball& operator=(const Trackball&) = delete;
	Trackball& operator=(Trackball&&) = delete;

	/// Return the 4x4 rotational matrix
	const glm::mat4 getMatrix4() const { return mouseRotationMatrix; }

	/// Return the 3x3 rotational matrix, after all a rotational matrix is a 3x3!
	const glm::mat3 getMatrix3() const { return glm::mat3(mouseRotationMatrix); }
	void HandleEvents(const SDL_Event& sdlEvent);
private:
	/// Just some functions for internal use only thus private
	const glm::vec4 getMouseVector(int x, int y);
	///Any time the window dimensions change like stretching it we will
	/// need to rebuild the invNDC matrix
	void setWindowDimensions();
	void onLeftMouseDown(int x, int y);
	void onLeftMouseUp(int x, int y);
	void onMouseMove(int x, int y);
};


#endif

