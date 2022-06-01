#pragma once
#define GLEW_STATIC
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
		~Model();
	private:
		const char* materialsFilename;
		std::vector < glm::vec3 > vertices;
		std::vector < glm::vec2 > uvs;
		std::vector < glm::vec3 > normals;
		bool ReadFiles(const char* filename);
	;
};
	Model::Model(const char* filename) {
		if (ReadFiles(filename));
	}

	bool Model::ReadFiles(const char* filename) {
		std::ifstream file(filename);

		if (!file.is_open()) {
			throw("Something went wrong opening .obj file");
			return false;
		}

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< glm::vec3 > temp_vertices;
		std::vector< glm::vec2 > temp_uvs;
		std::vector< glm::vec3 > temp_normals;

		char palavra[100];
		

		while (!file.eof()) {
			file >>	palavra;
			if (strcmp(palavra, "mtllib") == 0) { //se a palavra é mtllib
				file >> palavra;  
				materialsFilename = palavra;  //entao guarda a proxima palavra que é materialsFilename
			}
			if (strcmp(palavra, "v") == 0) { 
				glm::vec3 tempVertex;
				file >> tempVertex.x; 
				file >> tempVertex.y;
				file >> tempVertex.z;  
				temp_vertices.push_back(tempVertex);
			}
			if (strcmp(palavra, "vt") == 0) {
				glm::vec3 tempUV;
				file >> tempUV.x;
				file >> tempUV.y;
				temp_uvs.push_back(tempUV);
			}
			if (strcmp(palavra, "vn") == 0) {
				glm::vec3 tempNormal;
				file >> tempNormal.x;
				file >> tempNormal.y;
				file >> tempNormal.z;
				temp_vertices.push_back(tempNormal);
			}
			if (strcmp(palavra, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				file >> vertexIndex[0];
				file >> vertexIndex[1];
				file >> vertexIndex[2];
				file >> uvIndex[0];
				file >> uvIndex[1];
				file >> uvIndex[2];
				file >> normalIndex[0];
				file >> normalIndex[1];
				file >> normalIndex[2];
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		};


		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			glm::vec3 vertex = temp_vertices[vertexIndex - 1];
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = temp_vertices[uvIndex - 1];
			uvs.push_back(uv);
		}
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = temp_vertices[normalIndex - 1];
			normals.push_back(normal);
		}
		file.close();
	}		

