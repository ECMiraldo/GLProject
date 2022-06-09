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
		static float zoom;
		static float angle;
		Camera(float fovDegrees, float WindowWidth, float WindowHeight, glm::vec3 pos, glm::vec3 target);
		void Update();
	private:
		

};





