#version 330

layout(location = 0) out vec4 FragColor;


uniform sampler2D u_Texture;
uniform sampler2D u_NumberTexture[10];
uniform sampler2D u_NumbersTexture;
uniform float u_Time;

in vec2 v_TexPos;

// 시험 문제
void P1()
{
	vec2 newTexPos;
	float tx = v_TexPos.x;
	float ty = fract(v_TexPos.y * 2);
	newTexPos = vec2(tx,ty);
	FragColor = texture(u_Texture,newTexPos);
}

void P2()
{
	vec2 newTexPos;
	float tx = v_TexPos.x;
	float ty = 1- abs(v_TexPos.y * 2 - 1);

	newTexPos = vec2(tx,ty);
	FragColor = texture(u_Texture, newTexPos);
}

void P3()
{
	vec2 newTexPos;

	// 주어진 실수 값에서 정수 부분을 제거하고 소수 부분만을 반환
	// (0 ~ 1) * 3  ->  0 ~ 3  ->  fract  -> 0~0.9999, 0~0.9999, 0~0.9999
	float tx = fract(v_TexPos.x * 3);

	// floor : 실수 값을 가장 가까운 작은 정수로 내림
	// (0~1)/3 + 2/3, (0~1)/3 + 1/3, (0~1)/3 +  0/3
	float ty = v_TexPos.y/3 + (2 - floor(v_TexPos.x * 3))/3;
	newTexPos = vec2(tx,ty);

	FragColor = texture(u_Texture, newTexPos);
	// FragColor = vec4 (ty);
}

void P4()
{
	vec2 newTexPos;

	// 주어진 실수 값에서 정수 부분을 제거하고 소수 부분만을 반환
	// (0 ~ 1) * 3  ->  0 ~ 3  ->  fract  -> 0~0.9999, 0~0.9999, 0~0.9999
	float tx = fract(v_TexPos.x * 3);

	// floor : 실수 값을 가장 가까운 작은 정수로 내림
	// (0~1)/3 + 2/3, (0~1)/3 + 1/3, (0~1)/3 +  0/3
	float ty = v_TexPos.y/3 + floor(v_TexPos.x * 3)/3;
	newTexPos = vec2(tx,ty);

	FragColor = texture(u_Texture, newTexPos);
	// FragColor = vec4 (ty);
}

void P5()
{
	vec2 newTexPos;

	float padding = 0.5 + u_Time;
	float countX = 5;
	float countY = 5;

	float tx = fract(padding* floor(v_TexPos.y * countY) ) + v_TexPos.x * countX;
	float ty = fract(v_TexPos.y * countY);
	newTexPos = vec2(tx,ty);

	FragColor = texture(u_Texture, newTexPos);
}

void P6()
{
	vec2 newTexPos;

	float tx = v_TexPos.x ;
	float ty = v_TexPos.y;
	newTexPos = vec2(tx,ty);

	int texID = int(u_Time)%10;

	FragColor = texture(u_NumberTexture[texID], newTexPos);
}

void P7()
{
	vec2 newTexPos;
	float xResol = 5;
	float yResol = 2;
	float id = 5;
	float indexX = float(int(id)%int(xResol));
	float indexY = floor(id/xResol);	// 0 ~ 5 : 0 / 5 ~ : 1
	float tx = v_TexPos.x/xResol + indexX * (1/xResol);	
	float ty = v_TexPos.y/yResol + indexY * (1/yResol);	
	newTexPos = vec2(tx,ty);

	FragColor = texture(u_NumbersTexture, newTexPos);
}

void main()
{
	
	P7();
	
}

