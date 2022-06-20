
#include <glew.h>
#include "LoadShaders.h"
#include "Model.h"
#include "Camera.h"

using namespace biblioteca;

namespace lights {
	bool light[] = { true, true, true, true };
	void Lights(Model* model);
	void OnkeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
	 glm::vec3 off = glm::vec3(0.0, 0.0, 0.0);
}



void lights::Lights(Model* model) {

	//Model model = Model("Iron_Man.obj");
	GLuint shaderProgram = model->sendModelData();
	
	//GLint shaderProgra;
	//glGetIntegerv(GL_CURRENT_PROGRAM, &shaderProgra);

	// Fonte de luz ambiente global
	if (light[0])
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	}
	else
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "ambientLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	}

	if (light[1])
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.2, 0.2, 0.2)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
	}
	else 
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.direction"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "directionalLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	}

	// Fonte de luz direcional
	if (light[2])
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 5.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.ambient"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.diffuse"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.specular"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.constant"), 1.0f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.linear"), 0.06f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.quadratic"), 0.02f);
	}
	else
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.position"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.constant"), 1.0f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.linear"), 0.06f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "pointLight.quadratic"), 0.02f);

	}
	//
	if (light[3])
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.position"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(1.0, 1.0, 1.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(5.0, 10.0, 10.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(5.0, 10.0, 10.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.direction"), 1, glm::value_ptr(glm::vec3(0.0, 2.0, 0.0)));

		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.angle"), 0.00005f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.constant"), 1.0f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.linear"), 0.06f);
		glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.quadratic"), 0.02f);
	}
	else
	{
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.position"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.ambient"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.diffuse"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.specular"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
		glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "spotLight.direction"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 0.0)));
	}
		


	//Propriedades do material
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.emissive"), 1, glm::value_ptr(glm::vec3(0.1, 0.1, 0.1)));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.ambient"), 1, glm::value_ptr(model->ka));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.diffuse"), 1, glm::value_ptr(model->kd));
	glProgramUniform3fv(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.specular"), 1, glm::value_ptr(model->ks));
	glProgramUniform1f(shaderProgram, glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "material.shininess"), model->ns);
}

// funcao da tecla pressionada
void lights::OnkeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		if (light[0])
		{
			light[0] = false;
		}
		else light[0] = true;
		// luz ambiente

	}

	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		// direcional
		if (light[1])
		{
			light[1] = false;
		}
		else light[1] = true;
	}

	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		// luz pointlight
		if (light[2])
		{
			light[2] = false;
		}
		else light[2] = true;
	}

	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		// spotlight
		if (light[3])
		{
			light[3] = false;
		}
		else light[3] = true;
	}

}