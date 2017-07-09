#version 330 core

out vec4 color;

in vec2 TexCoord;
uniform vec4 outColor;

uniform sampler2D ourTexture1;
//uniform sampler2D ourTexture2;

void main()
{
	//color = vec4(1.0f,0.0f,1.0f,1.0f);
	//color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2);
	color = texture(ourTexture1, TexCoord);
}