#version 330

in vec3 a_Position;

out vec2 TexPos;

uniform vec2 u_ScreenResol;
uniform vec2 u_Position;
uniform vec2 u_Size;

void main()
{
	vec4 newPos = a_Position * (u_Size / u_ScreenResol) + u_Position;
	vec4 newPosition = vec4(newPos,0,1);

	gl_Position = newPosition;
	v_TexPos = vec2(a.Position.x, 1 - a_Position.y);
}
