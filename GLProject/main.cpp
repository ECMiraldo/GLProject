#define GLEW_STATIC
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include "Model.h"
#include "Camera.h"
#include "LoadShaders.h"

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#define HEIGHT 800
#define WIDTH 600

//To do: unmake this variables global
#define NumVAOs 1
#define NumBuffers 3 // Vértices, texturas, normais
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6; //Get num of vertices from model.vertices

void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	// Descomentar para ativar o Face Culling
	glEnable(GL_CULL_FACE);
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {

	unsigned int id = glCreateShader(GL_VERTEX_SHADER);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_UNSIGNED_INT, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader  " << (type == GL_VERTEX_SHADER ? "vertex" : "Fragment") << std::endl;
		std::cout << message << std::endl;
		return 0;
	}	

	return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
				

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	return program;
}



int main(void) {
	GLFWwindow* window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(800, 600, "Iron_Man", NULL, NULL);
	


	if (!window) {
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	Init();
	glewExperimental = GL_TRUE;
	glewInit(); 

	//Precisa ser depois do glewInit para funcionar 
	Model model = Model("Iron_Man.obj");
	Camera camera = Camera(60.0f, WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f));
	//glfwSetScrollCallback(window, camera.scrollCallback);



	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model.Display(camera.view, camera.projection);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	

	glfwTerminate();
	return 0;




}

