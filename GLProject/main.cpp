#define GLEW_STATIC
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm/ext.hpp>
#include <vector>
#include <gl/GL.h>
#include <iostream>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#define HEIGHT 800
#define WIDTH 600


void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	// Descomentar para ativar o Face Culling
	//glEnable(GL_CULL_FACE);
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

	window = glfwCreateWindow(800, 600, "My 1st P3D Project", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	Init();
	glewInit();


	GLfloat positions[] = {
		-0.5f, 0.5f //1 //6
		- 0.5f, -0.8f, //2
		0.5f, -0.8f, //3, 4
		0.5f, 0.5f, //5
	};

	//get buffer names
	unsigned int  buffer;
	glGenBuffers(1, &buffer);
	//bindBuffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//9 vertices necessarios
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(GLfloat), positions, GL_STATIC_DRAW);

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0

	};

	//get buffer names
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	//bindBuffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//9 vertices necessarios
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(ebo);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


	unsigned int Shader = CreateShader()

	while (!glfwWindowShouldClose(window)) {
		
		glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	

	glfwTerminate();
	return 0;




}