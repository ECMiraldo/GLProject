#pragma once
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include <string>
#include <fstream>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")



class Model
{
	public:
		float position;
		glm::mat4 matrix;
		Model(const char* filename);
		void Display(glm::mat4 mvp);
	private:
		char materialsFilename[50];
		std::vector < glm::vec3 > vertices;
		std::vector < glm::vec2 > uvs;
		std::vector < glm::vec3 > normals;
		bool ReadFiles(const char* filename);
	;
};
	inline Model::Model(const char* filename) {
		ReadFiles(filename);
	}

