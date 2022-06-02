#pragma once
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include <math.h>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")


class Camera
{
	public: 
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 position;
		glm::vec3 target;
		Camera(float fovDegrees, float WindowWidth, float WindowHeight, glm::vec3 pos, glm::vec3 target);
		void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	private:
		float zoom = 1.0f;
		GLfloat ZOOM = 10.0f;
		GLfloat ANGLE = 0.0f;



};

inline Camera::Camera(float fovDegrees, float WindowWidth, float WindowHeight, glm::vec3 pos, glm::vec3 target) {
	this->position = pos;
	this->target = target;

	projection = glm::perspective(glm::radians(fovDegrees), WindowWidth * WindowHeight, 0.1f, 100.f);

	view = glm::lookAt(pos,target,glm::vec3(0.0f, 1.0f, 0.0f));
	

}


inline void Camera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM += fabs(ZOOM) * 0.1f;
	}
	// Senão, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a distância da câmara
		ZOOM -= fabs(ZOOM) * 0.1f;
	}
	view = glm::lookAt(glm::vec3(position.x, position.y, zoom),
		target,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}