// Pega a informação que vai pra grafica e vai processar os dados na grafica

#version 440 core
layout (location = 0) in vec3 vertexPositions;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normals;

out vec2 uv
out vec3 normal

void main()
{
  gl_Position = vec4(vertexPosition,1.0f);
  normal = normals;
  uv = uvs;
}