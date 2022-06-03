// Busca o resultado do programa vertexShader e com essa informação ele gera um fragmento (Um candidato a pixel)

#version 440 core
layout (location = 0) out vec4 FragColor;
void main()
{
  FragColor = vec4(0,1,0,1);
}