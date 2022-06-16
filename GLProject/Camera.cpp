#pragma once
#include "Camera.h"

float Camera::zoom = 0.0f;
float Camera::angle = 0.0f;

Camera::Camera(float fovDegrees, float WindowWidth, float WindowHeight, glm::vec3 pos, glm::vec3 target) {

	this->position = pos;
	this->target = target;
	projection = glm::perspective(glm::radians(fovDegrees), WindowWidth / WindowHeight, 0.1f, 100.f);
	view = glm::lookAt(pos, target, glm::vec3(0.0f, 1.0f, 0.0f));

}


void Camera::Update(GLuint shaderProgram) {

	view = glm::lookAt(glm::vec3(position.x, position.y, Camera::zoom), target, glm::vec3(0.0f, 1.0f, 0.0f));
	
	GLint viewID = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "View");
	GLint projectionId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "Projection");

	glProgramUniformMatrix4fv(shaderProgram, projectionId, 1, GL_FALSE, glm::value_ptr(projection));
	glProgramUniformMatrix4fv(shaderProgram, viewID, 1, GL_FALSE, glm::value_ptr(view));
}