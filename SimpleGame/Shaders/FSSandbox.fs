#version 330

layout(location=0) out vec4 FragColor;

uniform float u_Time;

in vec4 v_Color;

const float c_PI = 3.14;

void FilledCircle()
{
	vec4 newColor = vec4(1,1,1,1);
	float r = 0.5;
	vec2 center = vec2 (0.5,0.5);
	// �� 2�� ���� �Ÿ�	
	float dist = distance(v_Color.rg, center);

	if(dist<r)
	{
	newColor = vec4 (1,1,1,1);
	}

	else 
	{
	newColor = vec4(0,0,0,0);
	//discard; �� ����� ������ ��õX
	}

	FragColor = newColor;
}

void Circle()
{
	vec4 newColor = vec4(1,1,1,1);
	float r = 0.5;
	float width = 0.05;
	vec2 center = vec2 (0.5,0.5);
	float dist = distance(v_Color.rg, center);

	if(dist > r - width && dist < r)
	{
		newColor = vec4(1,1,1,1);
	}

	else
	{
		newColor = vec4(0,0,0,0);
	}

	FragColor = newColor;

}

void Circles()
{
	float circleCount = 10;

	vec2 circleCenter = vec2(0.5, 0.5);

	// ���� ������ ǥ������� �Ÿ�
	float dist = distance(v_Color.rg, circleCenter);
	
	//	��  * ���� ũ�� * ���� ũ�� -> ���κп��� ��/2
	// �� ���� * �� * 4 * r
	float input = circleCount * c_PI * 4 * dist + -u_Time * 10;

	// 1�� ������ �����
	float sinValue = pow(sin(input),16);

	FragColor = vec4(sinValue);

}

void main()
{
	Circles();
}

