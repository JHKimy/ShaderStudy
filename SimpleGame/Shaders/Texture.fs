#version 330

layout(location=0) out vec4 FragColor0;
layout(location=1) out vec4 FragColor1;

in vec2 v_Color;

uniform sampler2D u_Texture;

void main()
{
	FragColor0 = texture(v_TexPos, u_Texture);
	FragColor1 = texture(1,0,0,1);
}