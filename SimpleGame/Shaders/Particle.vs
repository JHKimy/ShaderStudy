#version 330

in vec3 a_Position;

// �ð� (�ܺ�)
uniform float u_Time = 0;

// (�ܺο��� ����)
uniform float u_Period = 2.0f;


// ���� ��ġ, �ӵ�
const vec3 c_StartPos = vec3(-1, 0, 0);
const vec3 c_Velocity = vec3(2.0, 0, 0);	// 1��

void main()
{
	float newTIme = fract(u_Time / u_Period);	// ������ �Ǵ� ���� 0 
	vec4 newPosition;

	newPosition.xyz = 
	(c_StartPos + a_Position) + 
	c_Velocity * newTIme;

	newPosition.w = 1;
	gl_Position = newPosition;
}