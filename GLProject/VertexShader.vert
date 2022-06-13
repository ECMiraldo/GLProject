// Pega a informa��o que vai pra grafica e vai processar os dados na grafica
#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 Projection;
layout (location = 0) in vec3 vertexPositions;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;


in vec3 vPosition;			// Coordenadas locais do v�rtice
in vec3 vNormal;			// Normal do v�rtice


out vec2 uv;
out vec3 normal;
out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;
out vec3 textureVector;

void main()
{ 
	mat4 ModelView = View * Model;
	mat4 NormalMatrix = glm::inverseTranspose(glm::mat3(ModelView));

	gl_Position = mvp* vec4(vertexPositions,1.0f);
	normal = normals;
	uv = uvs;


	// Posi��o do v�rtice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vPosition, 1.0)).xyz;

	// Transformar a normal do v�rtice.
	vNormalEyeSpace = normalize(NormalMatrix * vNormal);

	// Coordenada de textura para o CubeMap
	textureVector = vPosition;

	// Posi��o final do v�rtice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(vPosition, 1.0f);
}