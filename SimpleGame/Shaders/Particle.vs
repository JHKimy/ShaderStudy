#version 330

in vec3 a_Position;

// 시간 (외부)
uniform float u_Time = 0;

// (외부에서 조작)
uniform float u_Period = 2.0f;


// 시작 위치, 속도
const vec3 c_StartPos = vec3(-2, 0, 0);
const vec3 c_Velocity = vec3(2.0, 0, 0);	// 1초
const vec3 c_ParaVelocity = vec3(2.0, 2.0, 0);
const vec2 c_2DGravity = vec2(0.0,-4.9);
const float c_PI = 3.141592;


void Basic()
{
	vec4 newPosition = vec4(a_Position,1);
	gl_Position = newPosition;

}

void Line()
{
	float newTime = abs(fract(u_Time / u_Period) - 0.5) * 2.0 ;	// 정수가 되는 순간 0 
	// 수학적으로 식 만들어 계산 후 적용
	// 시험에도 나올 수 있음

	vec4 newPosition;

	newPosition.xyz = 
	(c_StartPos + a_Position) + 
	c_Velocity * newTime;

	newPosition.w = 1;
	gl_Position = newPosition;
}

void Circle()
{
	// 원의 각도 왔다 갔다
	// 반시계
	// float newTime = fract(u_Time / u_Period) * c_PI * 2.0;
	// 시계
	//float newTime = c_PI * 2.0 - fract(u_Time / u_Period) * c_PI * 2.0;
	float newTime = - fract(u_Time / u_Period) * c_PI * 2.0;
	
	vec2 trans = vec2(cos(newTime), sin(newTime));
	vec4 newPosition;
	newPosition.xy = a_Position.xy + trans;
	newPosition.zw = vec2(0,1);
	gl_Position = newPosition;
}

void Parabola()
{
	float newTime = fract(u_Time/u_Period);
	
	float t = newTime;
	float tt = t*t;

	vec4 newPosition;

	float transX = (a_Position.x + c_StartPos.x)
	+ c_ParaVelocity.x + newTime
	+ 0.5 * c_2DGravity.x + tt;

	float transY = (a_Position.y + c_StartPos.y)
					+ c_ParaVelocity.y * newTime
					+ 0.5 * c_2DGravity.y * tt;

	newPosition.xy = vec2(transX, transY);
	newPosition.zw = vec2(0,1);
	gl_Position = newPosition;
}

void main()
{
	Basic();
	
	// Parabola();
	// Circle();
	// Line();
}