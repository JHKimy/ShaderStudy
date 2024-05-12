#version 330

layout(location=0) out vec4 FragColor0;
layout(location=1) out vec4 FragColor1;

in vec4 v_Color;
in vec4 v_TexPos;

void main()
{
    vec4 newColor = texture(u_Texture, v_TexPos);
    FragColor0 = texture(u_Texture, v_TexPos).b * v_Color;
    FragColor0 = texture(u_Texture, v_TexPos).b * v_Color;
  	FragColor1 = vec4(v_TexPos,0,1);
}
