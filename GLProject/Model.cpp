#pragma once
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include "Model.h"
#include <math.h>
#include "LoadShaders.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

using namespace glm;

void Model::Display(vec3 position, vec3 orientacao) {
	mat4 projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	mat4 view = glm::lookAt(vec3(0.0f, 2.0f, 5.0f), vec3(0.0f, 2.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	mat4 mvp = matrix * projection * view;

	glBindVertexArray(vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() * 3);
	//float* vertex_stream = static_cast<float*>(glm::value_ptr(obj.front()));
	//	glm::vec4 vertex = glm::vec4(vertex_stream[nv], vertex_stream[nv + 1], vertex_stream[nv + 2], 1.0f);
	//	// Cálculo das coordenadas de recorte
	//	glm::vec4 transformed_vertex = mvp * vertex;
	//	// Divisão de Perspetiva
	//	glm::vec4 normalized_vertex = transformed_vertex / transformed_vertex.w;
	//	// Desenho do vértice
	//	glVertex3f(normalized_vertex.x, normalized_vertex.y, normalized_vertex.z);
}




bool Model::ReadFiles(const char* filename) {
	FILE* file;
	errno_t err;
	err = fopen_s(&file, filename, "r");
	if (file == NULL) {
		throw("Impossible to open the file !\n");
		return false;
	}

	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	while (1) {
		char lineHeader[128];
		int res = fscanf_s(file, "%s", lineHeader, (unsigned int)_countof(lineHeader));
		if (res == EOF)
			break;
		if (strcmp(lineHeader, "mtllib") == 0) {
			fscanf_s(file, "%s\n", materialsFilename, (unsigned int)_countof(materialsFilename));
		}

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}

		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}

		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				throw("Failed to read face information\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		};
	}
	//prints


	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_vertices[uvIndex - 1];
		uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_vertices[normalIndex - 1];
		normals.push_back(normal);
	}
	//
	//for (unsigned int i = 0; i < vertexIndices.size(); i++) {
	//	std::cout << vertices[i].x << "\t" << vertices[i].y << "\t" <<  vertices[i].z << std::endl;
	//}
	//for (unsigned int i = 0; i < uvIndices.size(); i++) {
	//	std::cout  << uvs[i].x << "\t" << uvs[i].y << std::endl;
	//}
	//for (unsigned int i = 0; i < normalIndices.size(); i++) {
	//	std::cout  << normals[i].x << "\t" << normals[i].y << "\t" << normals[i].z << std::endl;
	//}



	fclose(file);
	return true;

}


void Model::sendModelData() {

	GLfloat vertex[9264 * 3];
	GLfloat uvsArray[9264 * 2];
	GLfloat normais[9264 * 3];
	for (int i = 0; i < vertices.size(); i++) {
		// at = vertices[i]
		vertex[i * 3] = vertices.at(i).x;
		vertex[i * 3 + 1] = vertices.at(i).y;
		vertex[i * 3 + 2] = vertices.at(i).z;
		// normais
		normais[i * 3] = normals.at(i).x;
		normais[i * 3 + 1] = normals.at(i).y;
		normais[i * 3 + 2] = normals.at(i).z;

		// Uvs
		uvsArray[i * 2] = uvs.at(i).x;
		uvsArray[i * 2 + 1] = uvs.at(i).y;
	}

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	
	glGenBuffers(3, bufferArrayObjects);

	// Send datas to buffers
	for (int i = 0; i < 3; i++) {
		glBindBuffer(GL_ARRAY_BUFFER, bufferArrayObjects[i]);

		if (i == 0) glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 4, vertex, GL_STATIC_DRAW);
		if (i == 1) glBufferData(GL_ARRAY_BUFFER, sizeof(uvsArray) * 4, uvsArray, GL_STATIC_DRAW);
		if (i == 2) glBufferData(GL_ARRAY_BUFFER, sizeof(normais) * 4, normais, GL_STATIC_DRAW);
	}													   
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"VertexShader.vert"},
		{GL_FRAGMENT_SHADER,"FragmentShader.frag"},
		{GL_NONE,NULL},
	};

	//Shader
	shaderProgram = LoadShaders(shaders);
	glUseProgram(shaderProgram);

	//Posição no shader (ponteiro da variavel do shader)
	GLint vertexPositionS = glGetProgramResourceLocation(shaderProgram, GL_PROGRAM_INPUT, "vertexPositionS");
	glVertexAttribPointer(vertexPositionS, 3, GL_FLOAT, GL_FALSE, 0, 0);

}