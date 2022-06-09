#pragma once
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS
#define GLFW_USE_DWM_SWAP_INTERVAL
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")



class Model
{
	public:
		float position;
		glm::mat4 matrix;
		Model(const char* filename);
		void Display(glm::mat4 view, glm:: mat4 projection);
	private:
		//VAO
		GLuint vertexArrayObject;
		GLuint bufferArrayObjects[3]; // 3 vertex, coord de textura e normais
		GLuint shaderProgram;
		GLuint num_vertices;
		char materialsFilename[50];
		std::vector < glm::vec3 > vertices;
		std::vector < glm::vec2 > uvs;
		std::vector < glm::vec3 > normals;
		bool ReadFiles(const char* filename);
		void sendModelData();
		
	;
};
	inline Model::Model(const char* filename) {
		matrix = glm::mat4(1.0f);
		ReadFiles(filename);
		sendModelData();
	}

