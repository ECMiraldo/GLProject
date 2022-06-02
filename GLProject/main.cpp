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
#define NumBuffers 3 // V�rtices, texturas, normais
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
	Model model = Model("Iron_Man.obj");
	Camera camera = Camera(60.0f, WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f));


	if (!window) {
		glfwTerminate();
		return -1;
	}


	glfwMakeContextCurrent(window);
	Init();
	glewInit();

	//glfwSetScrollCallback(window, camera.scrollCallback);



	while (!glfwWindowShouldClose(window)) {
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	

	glfwTerminate();
	return 0;




}

void InitVBOsForSingleModel(std::vector < glm::vec3 > vertices, std::vector < glm::vec2 > textures, std::vector < glm::vec3 > normals) {
// ****************************************************
	// Criar arrays de dados na RAM
	// ****************************************************

//GLfloat vertices[NumVertices][2 /*xy*/] = {
//	{ -0.90f, -0.90f }, { 0.85f, -0.90f }, { -0.90f,  0.85f }, // Tri�ngulo 1
//	{  0.90f, -0.85f }, { 0.90f,  0.90f }, { -0.85f,  0.90f }  // Tri�ngulo 2
//};
//
//GLfloat cores[NumVertices][3 /*rgb*/] = {
//	{ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, // Tri�ngulo 1
//	{ 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }  // Tri�ngulo 2
//};

// ****************************************************
// VAOs - Vertex Array Objects
// ****************************************************

// Gerar 'NumVAOs' nomes para VAOs. 
//NumVaos = 1
glGenVertexArrays(NumVAOs, VAOs);
// Faz bind do VAO, cujo nome est� definido em 'VAOs[0]', com o contexto do OpenGL.
// Um VAO � criado no primero bind que lhe seja feito.
// Este VAO passa a estar ativo at� que seja feito o bind a outro VAO, ou seja feito o bind com valor 0.
glBindVertexArray(VAOs[0]);

// ****************************************************
// VBOs - Vertex Buffer Objects
// ****************************************************

// Gera 'NumBuffers' nomes para VBOs.
// Neste caso, como NumBuffers = 3, gera 2 nomes
// Esta fun��o pode ser chamada antes da cria��o de VAOs.
glGenBuffers(NumBuffers, Buffers);
// Para cada nome de VBO
for (int i = 0; i < NumBuffers; i++) {
	// Faz bind do VBO ao buffer GL_ARRAY_BUFFER.
	// GL_ARRAY_BUFFER � utilizado para dados de atributos de v�rtices.
	// Um VBO � criado no primeiro bind que lhe seja feito.
	// Este VBO passa a estar ativo at� que seja feito o bind a outro VBO ou seja feito o bind com valor 0.
	// Para alocar a mem�ria para os BO, n�o � necess�rio que j� esteja vinculado um VAO.
	// EDU: Neste caso utilizamos VBOs com tamanho imutavel pois ja teremos a informacao do modelo
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[i]);
	if (i == 0) {
		// Inicializa o VBO (que est� ativo) com mem�ria de tamanho imut�vel.
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, 0);
	}
	else if (i == 1) {
		// Inicializa o VBO (que est� ativo) com mem�ria de tamanho imut�vel.
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(textures), &textures, 0);
	}
	else if (i == 2) {
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(normals), &normals, 0);
	}
}

// ****************************************************
// Shaders
// ****************************************************

ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER,   "triangles.vert" },
	{ GL_FRAGMENT_SHADER, "triangles.frag" },
	{ GL_NONE, NULL }
};

GLuint programa = LoadShaders(shaders);
if (!programa) exit(EXIT_FAILURE);
glUseProgram(programa);

// ****************************************************
// Ligar Atributos aos Shaders
// ****************************************************

// As localiza��es de atributos fazem parte do programa shader, e s�o completamente independentes do VAO.
// Podemos, assim, obter as localiza��es de atributos sem que antes se tenha criado qualquer VAO.
// ------------------------------------------------------------------------------------------------------
// Obt�m a localiza��o do atributo 'vPosition' no 'programa'.
//GLint coordsId = glGetAttribLocation(programa, "vPosition"); // Para vers�es anteriores � 4.3
GLint coordsId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vPosition"); // Para vers�es >= 4.3
// Obt�m a localiza��o do atributo 'vColors' no 'programa'.
//GLint coresId = glGetAttribLocation(programa, "vColors"); // Para vers�es anteriores � 4.3
GLint coresId = glGetProgramResourceLocation(programa, GL_PROGRAM_INPUT, "vColors"); // Para vers�es >= 4.3

//glBindVertexArray(VAOs[0]); // N�o � necess�rio fazer o bind do VAO, pois ele j� � o que est� ativo no contexto do OpenGL.

// Ativa o VBO 'Buffers[0]'.
glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
// Liga a localiza��o do atributo 'vPosition' dos shaders do 'programa', ao VBO e VAO (ativos).
// Aqui j� � necess�rio ter o VAO e o VBO vinculados ao contexto do OpenGL.
// � neste ponto que o VBO fica associado ao VAO.
// Especifica tamb�m como � que a informa��o do atributo 'coordsId' deve ser interpretada.
// Neste caso, o atributo ir� receber, por v�rtice, 2 elementos do tipo float.
glVertexAttribPointer(coordsId, 2 /*2 elementos por v�rtice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

// Ativa o VBO 'Buffers[1]'.
glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
// Liga a localiza��o do atributo 'vColors' dos shaders do 'programa', ao VBO e VAO (ativos).
// Aqui j� � necess�rio ter o VAO e o VBO vinculados ao contexto do OpenGL.
// � neste ponto que o VBO fica associado ao VAO.
// Especifica tamb�m como � que a informa��o do atributo 'coordsId' deve ser interpretada.
// Neste caso, o atributo ir� receber, por v�rtice, 3 elementos do tipo float.
glVertexAttribPointer(coresId, 3 /*3 elementos por v�rtice*/, GL_FLOAT/*do tipo float*/, GL_FALSE, 0, nullptr);

// Habitita o atributo com localiza��o 'coresId' para o VAO ativo.
// Os atributos de um VAO est�o desativados por defeito.
glEnableVertexAttribArray(coordsId);
// Habitita o atributo com localiza��o 'coresId' para o VAO ativo.
// Os atributos de um VAO est�o desativados por defeito.
glEnableVertexAttribArray(coresId);
}