#version 330

in vec3 a_Position;
// ; Ȯ�� ���ϱ� /  �׽�Ʈ

void main()
{
	vec4 newPosition = vec4(a_Position, 1);
	gl_Position = newPosition;
}
