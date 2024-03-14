#version 330

in vec3 a_Position;
// ; 확인 잘하기 /  테스트

void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	gl_Position = newPosition;
}
