#version 330

in vec3 a_Position;
out vec4 v_Color;

uniform float u_Time;
const float c_PI= 3.141592;

void Flag(){

		vec4 newPosition = vec4(a_Position , 1);
		float scaledValue = a_Position.x + 0.5;
		float period = 2;
		float sinInput= period * (a_Position.x + 0.5)*c_PI*2;
		float timeScale = 10;
		float width = 0.5 * (1 - scaledValue);

		float sinValue =sin(sinInput - u_Time * timeScale);
		newPosition.y = width * newPosition.y + scaledValue * width * sinValue;
		
		gl_Position = newPosition;
		v_Color = vec4((sinValue+1)/2);

}

void praticeFlag(){

	vec4 newPosition =  vec4(a_Position , 1);
	float scaledValue = a_Position.x + 0.5f;
	float period = 2;
	float sininput = scaledValue * c_PI * 2 *period;
	float timescale = 10;
	float width = 0.5 * (1 - scaledValue);

	float sinvalue  = sin(sininput - u_Time *timescale);
	newPosition.y = width * newPosition.y + scaledValue * width * sinvalue;

	gl_Position = newPosition;
	v_Color = vec4((sinvalue +1)/2);

}

void SphereMapping(){

float r = 0.5;
float scale = 5;
float newX = r * sin(a_Position.y*scale)  * cos(a_Position.x*scale);
float newY = r * sin(a_Position.y*scale) * sin(a_Position.x*scale);
float newZ = r*  cos(a_Position.y*scale);

vec4 newPosition  = vec4(newX,newY ,newZ ,1);
float newTime = fract(u_Time /5);

vec4 interpoREsult = vec4(a_Position,1)* (1-newTime) + newPosition*newTime;
gl_Position = interpoREsult;
v_Color = vec4(1);

}

void Cycle(){

	float circleCount = 3;
	vec2 circleCenter = vec2(0.0,0.0);
	float maxDist = 0.5f;
	//vec4 newPosition = vec4(a_Position , 1);


	float dist = distance(a_Position.xy , circleCenter);
	float input = circleCount * c_PI* 4 * dist - u_Time * 20.0; 
	float sinValue = sin(input);
	gl_Position = vec4(a_Position,1);
	v_Color =vec4(sinValue);

}

void main()
{

	//SphereMapping();
	//Cycle();
	//Flag();
	praticeFlag();
}
