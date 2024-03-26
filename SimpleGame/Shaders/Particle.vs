#version 330

in vec3 a_Position;

// 시간 (외부)
uniform float u_Time = 0;

// (외부에서 조작)
uniform float u_Period = 2.0f;


// 시작 위치, 속도
const vec3 c_StartPos = vec3(-1, 0, 0);
const vec3 c_Velocity = vec3(2.0, 0, 0);	// 1초

void main()
{
	float newTIme = fract(u_Time / u_Period);	// 정수가 되는 순간 0 
	vec4 newPosition;

	newPosition.xyz = 
	(c_StartPos + a_Position) + 
	c_Velocity * newTIme;

	newPosition.w = 1;
	gl_Position = newPosition;
}