#version 330

layout(location=0) out vec4 FragColor0; // HDR Low
layout(location=1) out vec4 FragColor1; // HDR High

uniform sampler2D u_Texture;

in vec4 v_Color;
in vec2 v_TexPos;

void main()
{
    vec4 newColor = texture(u_Texture, v_TexPos);
    // ���ϴ� �� ���� ���� ��� ���� 
    vec4 result = vec4(newColor.rgb*v_Color.rgb * 1, newColor.a);
    float brightness = dot(result.rgb, vec3(0.2126, 0.7152, 0.0722));

	FragColor0 = result;

    if(brightness > 1.0)
    {
        FragColor1 = result;
    }
    else
        FragColor1 = vec4(0);
}
