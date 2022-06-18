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

#define HEIGHT 600
#define WIDTH 800


void Init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	// Descomentar para ativar o Face Culling
	glEnable(GL_CULL_FACE);
}

//permite a chamada do script para movimentar a camera pelo rato
void HandleMouse(GLFWwindow* window, double xpos, double ypos) {
	Camera::GetInstance()->mouseCallback(window, xpos, ypos);
}

//permite a chamada do script para efetuar zoom pelo scroll
void HandleScroll(GLFWwindow* window, double xoffset, double yoffset) {
	Camera::GetInstance()->scrollCallback(window, xoffset, yoffset);
}
//void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
//	// Se faz zoom in
//	if (yoffset == 1) {
//		// Incremento no zoom, varia com a distância da câmara
//		Camera::zoom -= 0.1f;
//	}
//	// Senão, se faz zoom out
//	else if (yoffset == -1) {
//		// Incremento no zoom, varia com a distância da câmara
//		Camera::zoom += 0.1f;
//	}
//	std::cout << "ZOOM = " << Camera::zoom << std::endl;
//}



int main(void) {
	GLFWwindow* window;
	Camera* camera;
	camera = camera->GetInstance();
	camera->InicializeCamera(45.0f, WIDTH, HEIGHT, glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 2.0f, 0.0));

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(800, 600, "Iron_Man", NULL, NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!window) {
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	Init();
	glewExperimental = GL_TRUE;
	glfwSetCursorPosCallback(window, HandleMouse);
	glfwSetScrollCallback(window, HandleScroll);
	glewInit(); 



	//Precisa ser depois do glewInit para funcionar 
	
	
	
	Model model = Model("Iron_Man.obj");
	GLuint shaderProgram = model.sendModelData();
	
	
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

   
	
	
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model.Display(glm::vec3(0,0,0),glm::vec3(0,0,0));
		model.Display(glm::vec3(-2,-1,-5),glm::vec3(0,0,0));
		model.Display(glm::vec3(2,-1, -5), glm::vec3(0,0,0));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	

	glfwTerminate();
	return 0;
}
