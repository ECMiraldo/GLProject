// Pega a informa��o que vai pra grafica e vai processar os dados na grafica
#version 440 core

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 vNormal;


out vec2 uv;
out vec3 normal;
out vec3 vPositionEyeSpace;
out vec3 vNormalEyeSpace;

void main()
{ 
	gl_Position = (Model * View * Projection) * vec4(vPosition,1.0f);
	normal = vNormal;
	uv = uvs;


	// Posi��o do v�rtice em coordenadas do olho.
	vPositionEyeSpace = (ModelView * vec4(vPosition, 1.0)).xyz;

	// Transformar a normal do v�rtice.
	vNormalEyeSpace = normalize(NormalMatrix * vNormal);

	// Posi��o final do v�rtice (em coordenadas de clip)
	gl_Position = Projection * ModelView * vec4(vPosition, 1.0f);
}