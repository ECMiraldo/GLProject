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



void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	// Descomentar para ativar o Face Culling
	glEnable(GL_CULL_FACE);
}



void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	// Se faz zoom in
	if (yoffset == 1) {
		// Incremento no zoom, varia com a distância da câmara
		Camera::zoom += fabs(Camera::zoom) + 0.1f;
	}
	
	// Senão, se faz zoom out
	else if (yoffset == -1) {
		// Incremento no zoom, varia com a distância da câmara
		Camera::zoom -= fabs(Camera::zoom) + 0.1f;
	}
	std::cout << "ZOOM = " << Camera::zoom << std::endl;
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
	
	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER,"VertexShader.vert"},
		{GL_FRAGMENT_SHADER,"FragmentShader.frag"},
		{GL_NONE,NULL},
	};

	//Shader
	GLuint shaderProgram = LoadShaders(shaders);
	glUseProgram(shaderProgram);
	model.sendModelData(shaderProgram);
	GLint modelViewId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "ModelView");
	GLint normalMatrixId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "NormalMatrix");
	
	// Fonte de luz ambiente global
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));

	// Fonte de luz direcional
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));

	// Fonte de luz pontual #1
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].constant"), 1.0f);
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].linear"), 0.06f);
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[0].quadratic"), 0.02f);

	// Fonte de luz pontual #2
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].position"), 1, glm::value_ptr(glm::vec3(-2.0, 2.0, 5.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].constant"), 1.0f);
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].linear"), 0.06f);
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight[1].quadratic"), 0.02f);

	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.shininess"), 12.0f);


	glfwSetScrollCallback(window, scrollCallback);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera.Update(shaderProgram);

		glm::mat4 ModelView = camera.view * model.model;
		glm::mat4 NormalMatrix = glm::inverseTranspose(glm::mat3(ModelView));
		glProgramUniformMatrix4fv(shaderProgram, modelViewId, 1, GL_FALSE, glm::value_ptr(ModelView));
		glProgramUniformMatrix4fv(shaderProgram, normalMatrixId, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

		model.Display(glm::vec3(0,0,0),glm::vec3(0,0,0));
		model.Display(glm::vec3(-2,-1,-5),glm::vec3(0,0,0));
		model.Display(glm::vec3(2,-1,-5),glm::vec3(0,0,0));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	

	glfwTerminate();
	return 0;
}

//glm::mat4 ModelView = View * Model;
//NormalMatrix = glm::inverseTranspose(glm::mat3(ModelView));
//
//// ****************************************************
//// Uniforms
//// ****************************************************
//
//// Atribui valor ao uniform Model
//GLint modelId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Model");
//glProgramUniformMatrix4fv(programa, modelId, 1, GL_FALSE, glm::value_ptr(Model));
//// Atribui valor ao uniform View
//GLint viewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "View");
//glProgramUniformMatrix4fv(programa, viewId, 1, GL_FALSE, glm::value_ptr(View));
//// Atribui valor ao uniform ModelView
//GLint modelViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "ModelView");
//glProgramUniformMatrix4fv(programa, modelViewId, 1, GL_FALSE, glm::value_ptr(ModelView));
//// Atribui valor ao uniform Projection
//GLint projectionId = glGetProgramResourceLocation(programa, GL_UNIFORM, "Projection");
//glProgramUniformMatrix4fv(programa, projectionId, 1, GL_FALSE, glm::value_ptr(Projection));
//// Atribui valor ao uniform NormalMatrix
//GLint normalViewId = glGetProgramResourceLocation(programa, GL_UNIFORM, "NormalMatrix");
//glProgramUniformMatrix3fv(programa, normalViewId, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
//
//// Fonte de luz ambiente global
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
//
//// Fonte de luz direcional
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//
//// Fonte de luz pontual #1
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].constant"), 1.0f);
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].linear"), 0.06f);
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[0].quadratic"), 0.02f);
//
//// Fonte de luz pontual #2
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].position"), 1, glm::value_ptr(glm::vec3(-2.0, 2.0, 5.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].constant"), 1.0f);
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].linear"), 0.06f);
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "pointLight[1].quadratic"), 0.02f);
//
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform3fv(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
//glProgramUniform1f(programa, glGetProgramResourceLocation(programa, GL_UNIFORM, "material.shininess"), 12.0f);