#version 330

// �ܺ� �Է�
in vec3 a_Position;
in float a_StartTime;
in vec3 a_Velocity;
in float a_LifeTime;
in float a_Amp;
in float a_Period;
in float a_Value;

// �ð� (�ܺ�)
uniform float u_Time = 0;

// (�ܺο��� ����)
uniform float u_Period = 2.0f;


// ���� ��ġ, �ӵ�
const vec3 c_StartPos = vec3(-2, 0, 0);
const vec3 c_Velocity = vec3(2.0, 0, 0);	// 1��
const vec3 c_ParaVelocity = vec3(2.0, 2.0, 0);
const vec2 c_2DGravity = vec2(0.0,-5.9);
const float c_PI = 3.141592;


void Basic()
{
	vec4 newPosition = vec4(a_Position.xy * a_StartTime ,0 ,1);
	gl_Position = newPosition;
}

void Velocity()
{
	// float newTime = 2.0 * fract(u_Time / u_Period);

	float t = u_Time - a_StartTime;
	vec4 newPosition = vec4(a_Position, 1);

	if(t>0)
	{	
		t = a_LifeTime * fract(t/a_LifeTime);

		newPosition.xy = newPosition.xy + a_Velocity.xy * t;
	}
	else
	{
		newPosition.x = -1000000;
	}

	gl_Position = newPosition;

}



void Line()
{
	float newTime = abs(fract(u_Time / u_Period) - 0.5) * 2.0 ;	// ������ �Ǵ� ���� 0 
	// ���������� �� ����� ��� �� ����
	// ���迡�� ���� �� ����

	vec4 newPosition;

	newPosition.xyz = 
	(c_StartPos + a_Position) + 
	c_Velocity * newTime;

	newPosition.w = 1;
	gl_Position = newPosition;
}

void Circle()
{
	// ���� ���� �Դ� ����
	// �ݽð�
	// float newTime = fract(u_Time / u_Period) * c_PI * 2.0;
	// �ð�
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

// sin �׷������ �����̱�
void SinShape()
{
	vec4 newPosition = vec4(a_Position, 1);
	float t = u_Time - a_StartTime;


	// ��
	float amp = a_Amp;
	// �ֱ�
	float period = a_Period;

	if(t>0)
	{	
		t = a_LifeTime * fract(t/a_LifeTime);
		float tt = t*t;

		float value = a_Value * 2.0 * c_PI;
		float x = cos(value);
		float y = sin(value);
		newPosition.xy = newPosition.xy + vec2(x,y);

		vec2 newVel = a_Velocity.xy + c_2DGravity *t;

		// ������⿡ ������ ���� ���ϱ�
		vec2 newDir = vec2 (-newVel.y, newVel.x);
		newDir = normalize(newDir);

		newPosition.xy = newPosition.xy + a_Velocity.xy * t + 0.5 * c_2DGravity * tt;
		newPosition.xy = newPosition.xy + newDir * 0.5*t  * amp * sin (t * c_PI * period );
	}

	else
	{
		newPosition.x = -1000000;
	}

	gl_Position = newPosition;
}



void SinShapeCycle()
{
	vec4 newPosition = vec4(a_Position, 1);
	float t = u_Time - a_StartTime;


	// ��
	float amp = a_Amp;
	// �ֱ�
	float period = a_Period;

	if(t>0)
	{	
		t = a_LifeTime * fract(t/a_LifeTime);
		float tt = t*t;

		float value = a_StartTime * 2.0 * c_PI;
		float x = cos(value);
		float y = sin(value);
		newPosition.xy = newPosition.xy + vec2(x,y);

		vec2 newVel = a_Velocity.xy + c_2DGravity *t;

		// ������⿡ ������ ���� ���ϱ�
		vec2 newDir = vec2 (-newVel.y, newVel.x);
		newDir = normalize(newDir);

		newPosition.xy = newPosition.xy + a_Velocity.xy * t + 0.5 * c_2DGravity * tt;
		newPosition.xy = newPosition.xy + newDir * 0.5*t  * amp * sin (t * c_PI * period );
	}

	else
	{
		newPosition.x = -1000000;
	}

	gl_Position = newPosition;
}


void main()
{
	// Basic();
	// Parabola();
	// Circle();
	// Line();
	// Velocity();
	//SinShape();
	SinShapeCycle();

}

// vs���� ���� �� �ִ� �ܺ� �Է� �ΰ���
// Attrib / Uniform
// -> ��ƼŬ���� �ٸ��� �� �� ����