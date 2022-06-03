// Pega a informação que vai pra grafica e vai processar os dados na grafica

#version 440 core
layout (location = 0) in vec3 vertexPositionS;
void main()
{
  gl_Position = vec4(vertexPositionS,1.0f);
}