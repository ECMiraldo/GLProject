// Busca o resultado do programa vertexShader e com essa informação ele gera um fragmento (Um candidato a pixel)

#version 440 core
layout (location = 0) out vec4 FragColor;

in vec2 uv;
uniform sampler2D textura;


void main()
{
  FragColor = texture(textura,uv);
}