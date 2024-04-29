// 1. ������ ���̴�
// 2. ���ؽ������Ϳ� VBO �غ�
// 3. VBO�� �۾� ���̺� �ø���
// 4. �۾� ���̺� ������ �ø��� (VBO��)
// 5. �׸���


#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}

Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", "./Shaders/Particle.fs");

	m_ParticleCloudShader = CompileShaders("./Shaders/ParticleCloud.vs", "./Shaders/ParticleCloud.fs");
	// ���̴� 2�� ���� �� ������
	// ��� ���̴� �ٲٱ�
 
	//m_FSSandBoxShader = CompileShaders("./Shaders/FSSandbox.vs", "./Shaders/FSSandbox.fs");
	//m_GridMeshShader = CompileShaders("./Shaders/GridMesh.vs", "./Shaders/GridMesh.fs");





	m_TextureSandboxShader = CompileShaders("./Shaders/TextureBox.vs", "./Shaders/TextureBox.fs");






	// 2��
	// CreateParticleCloud(10000);

	//Create VBOs
	CreateVertexBufferObjects();

	CreateGridMesh(32, 32);







	m_RGBTexture = CreatePngTexture("./rgb.png", GL_NEAREST);






	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

//�ʱ�ȭ ����
bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);



	float vertices[] = { 
			-1.f / 2, -1.f / 2, 0.f, -1.f / 2, 1.f / 2, 0.f, 1.f / 2, 1.f / 2, 0.f, //Triangle1
		-1.f / 2, -1.f / 2, 0.f,  1.f / 2, 1.f / 2, 0.f, 1.f / 2, -1.f / 2, 0.f, //Triangle2

	};

	// �׸� �������� ��ǥ��

	//glGenBuffers(1, &m_TestVBO);
	//// VBO�� ID ����
	//glBindBuffer(GL_ARRAY_BUFFER, m_TestVBO);
	//// GL_ARRAY_BUFFER�� �۾��뿡 m_TestVBO�� �ø�
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//// GL_ARRAY_BUFFER�� �ö� �ִ� ���� vertices ũ�� ��ŭ vertices �����ͷ� �ܾ GL_STATIC_DRAW �������� �����͸� �÷���

	float size = 0.05f;

	// �ݽð�������� �׸�
	float Particlevertices[] = 
	{
		-size, -size, 0,
		 size,  size, 0,
		-size,  size, 0,

		 size,  size, 0,
		 size, -size, 0,
		-size, -size, 0
	};

	// VBO�� ID�� �����
	glGenBuffers(1, &m_ParticleVBO);
	
	// VBO�� ID�� ���ε��� �������� ���ľ˷��ֱ�
	// VBO�� �۾��� ���� �ø���
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);

	// �۾��� ���� �÷��� �Ϳ� ������ ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particlevertices), Particlevertices, GL_STATIC_DRAW);




	size = 0.5f;
	float FSSandboxVerts[] =
	{
		-size, -size, 0,
		 size,  size, 0,
		-size,  size, 0,

		 size,  size, 0,
		 size, -size, 0,
		-size, -size, 0
	};

	glGenBuffers(1, &m_FSSandboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FSSandboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(FSSandboxVerts), FSSandboxVerts, GL_STATIC_DRAW);
}



void Renderer::CreateGridMesh(int x, int y)
{
	float basePosX = - 0.5f;
	float basePosY = - 0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = x;
	int pointCountY = y;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX * pointCountY * 2];
	float* vertices = new float[(pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3];
	m_GridMeshVertexCount = (pointCountX - 1) * (pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y * pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y * pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_GridMeshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}


// ���̴� ���α׷��� ���̴� �߰�
void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);

	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

// file �о target�� �־��ֱ�
bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

// ���̴� �����
GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	//�� ���̴� ���α׷� ����
	GLuint ShaderProgram = glCreateProgram(); 

	//���̴� ���α׷��� ����������� Ȯ��
	if (ShaderProgram == 0) { 
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	//���̴� ���α׷��� ���� OpenGL ���¿� ȣȯ �Ǵ��� ����
	glValidateProgram(ShaderProgram);
	// ������ �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	// ���� ���ϸ�
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	// �� ���̴��� ����ϰڴ�
	// ������ �� ���̴� ���α׷����� ������ ����
	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done." << std::endl;

	return ShaderProgram;
}

// ȭ�� ��ǥ (x,y)�� OpenGL ��ǥ��(newX, newY)�� �ٲ���
void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::CreateParticleCloud(int numParticles)
{
	float centerX, centerY;
	centerX = 0.f;
	centerY = 0.f;
	float size = 0.005f;
	int particleCount = numParticles;
	int vertexCount = particleCount * 6;

	int floatCount = vertexCount * (3 + 1 + 3 + 1 + 1 + 1 + 1 + 4);
	// x, y, z, startTime, vx, vy, vz, lifeTime, amp, period, value, r, g, b, a


	float* vertices = NULL;
	vertices = new float[floatCount];

	float vx, vy, vz;
	float startTime;
	float lifeTime;
	float r, g, b, a;


	float amp, period;
	// �߰�
	float value;

	int index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float velocityScale = 0.2f;
		// centerX = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		// centerY = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		//vx = (((float)rand() / (float)RAND_MAX) * 2.f - 1.f ) * velocityScale;
		vx = 0.f;
		//vy = (((float)rand() / (float)RAND_MAX) * 2.f - 1.f) * velocityScale;
		vy = -0.01f;
		vz = (((float)rand() / (float)RAND_MAX) * 2.f - 1.f) * velocityScale;

		// attribute �ϳ� �� �߰� (�ð�)
		//float startTime = 6.f * ((float)rand() / (float)RAND_MAX);
		centerX = 0.f;
		centerY = 0.f;
		//vx = 0.f;
		//vy = 1.f;
		//vz = 0.f;

		startTime = 10.f * ((float)rand() / (float)RAND_MAX);
		lifeTime = 0.5f  * ((float)rand() / (float)RAND_MAX) + 1.f;
		amp = (((float)rand() / (float)RAND_MAX) - 0.5f) *2.f;
		period = ((float)rand() / (float)RAND_MAX);
		value = ((float)rand() / (float)RAND_MAX);
		r = ((float)rand() / (float)RAND_MAX);
		g = ((float)rand() / (float)RAND_MAX);
		b = ((float)rand() / (float)RAND_MAX);
		a = ((float)rand() / (float)RAND_MAX);
		 
		vertices[index] = centerX - size;	index++;
		vertices[index] = centerY - size;	index++;
		vertices[index] = 0.f;				index++;
		vertices[index] = startTime;		index++;
		vertices[index] = vx;				index++;
		vertices[index] = vy;				index++;
		vertices[index] = vz;				index++;
		vertices[index] = lifeTime;			index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;



		vertices[index] = centerX + size;	index++;
		vertices[index] = centerY + size;	index++;
		vertices[index] = 0.f;				index++;
		vertices[index] = startTime;		index++;
		vertices[index] = vx;				index++;
		vertices[index] = vy;				index++;
		vertices[index] = vz;				index++;
		vertices[index] = lifeTime;			index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;



		vertices[index] = centerX - size;	index++;
		vertices[index] = centerY + size;	index++;
		vertices[index] = 0.f;	index++;
		vertices[index] = startTime;	index++;	
		vertices[index] = vx;	index++;
		vertices[index] = vy;	index++;
		vertices[index] = vz;	index++;
		vertices[index] = lifeTime;	index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;

		// triangle1




		vertices[index] = centerX - size;	index++;
		vertices[index] = centerY - size;	index++;
		vertices[index] = 0.f;	index++;
		vertices[index] = startTime;	index++;
		vertices[index] = vx;	index++;
		vertices[index] = vy;	index++;
		vertices[index] = vz;	index++;
		vertices[index] = lifeTime;	index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;


		vertices[index] = centerX + size;	index++;
		vertices[index] = centerY - size;	index++;
		vertices[index] = 0.f;	index++;
		vertices[index] = startTime;	index++;
		vertices[index] = vx;	index++;
		vertices[index] = vy;	index++;
		vertices[index] = vz;	index++;
		vertices[index] = lifeTime;	index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;


		vertices[index] = centerX + size;	index++;
		vertices[index] = centerY + size;	index++;
		vertices[index] = 0.f;	index++;
		vertices[index] = startTime;	index++;	
		vertices[index] = vx;	index++;
		vertices[index] = vy;	index++;
		vertices[index] = vz;	index++;
		vertices[index] = lifeTime;	index++;
		vertices[index] = amp;				index++;
		vertices[index] = period;			index++;
		vertices[index] = value;			index++;
		vertices[index] = r;				index++;
		vertices[index] = g;				index++;
		vertices[index] = b;				index++;
		vertices[index] = a;				index++;

		// triangle2
	}
	
	glGenBuffers(1, &m_ParticleCloudVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* floatCount, vertices, GL_STATIC_DRAW);
	m_ParticleCloudVertexCount = vertexCount;
	delete[] vertices;
}

GLuint Renderer::CreatePngTexture(char* filePath, GLuint samplingMethod)
{
	float size = 0.5f;

	float TextureBox[] =
	{
		-size,	size,0,		0,0,
		 -size, -size,0,	0,1,
		size,	size, 0,	1,0,

		 size,  size, 0,	1,0,
		 -size, -size,0,	0,1,
		 size, -size, 0,	1,1
	};

	glGenBuffers(1, &m_TextureSandboxVBO);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TextureBox), TextureBox, GL_STATIC_DRAW);


	//Load Png

	std::vector<unsigned char> image;

	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filePath);

	if (error != 0)

	{

		std::cout << "PNG image loading failed:" << filePath << std::endl;

		//assert(0);

	}



	GLuint temp;

	glGenTextures(1, &temp);

	glBindTexture(GL_TEXTURE_2D, temp);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,

	GL_UNSIGNED_BYTE, &image[0]);



	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingMethod);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplingMethod);



	return temp;


}



void Renderer::DrawTest()
{
	//Program select
	glUseProgram(m_SolidRectShader);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_TestVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawParticle()
{
	// ���̴� ����
	GLuint shader = m_ParticleShader;
	
	// ȣ��� ���ķδ� �� ��ƼŬ���̴� ���
	glUseProgram(shader);

	// ����������� 0 ���;��� �����ȵ�
	int ulTime = glGetUniformLocation(shader, "u_Time");
	glUniform1f(ulTime, m_ParticleTime);
	m_ParticleTime += 0.016f;	// ������ Ÿ�� : ��Ȯ���� ����



	int ulPeriod = glGetUniformLocation(shader, "u_Period");
	glUniform1f(ulPeriod, 2.0);
	


	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	//���ؽ� ��
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawParticleCloud()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���̴� ����
	GLuint shader = m_ParticleCloudShader;

	// ȣ��� ���ķδ� �� ��ƼŬ���̴� ���
	glUseProgram(shader);

	GLuint stride = sizeof(float) * 15;


	// ����������� 0 ���;��� �����ȵ�
	int ulTime = glGetUniformLocation(shader, "u_Time");
	glUniform1f(ulTime, m_ParticleTime);
	m_ParticleTime += 0.016f;	// ������ Ÿ�� : ��Ȯ���� ����

	int ulPeriod = glGetUniformLocation(shader, "u_Period");
	glUniform1f(ulPeriod, 2.0);

	int ulAcc = glGetUniformLocation(shader, "u_Acc");
	// 2�� ��
	//glUniform2f(ulAcc, -3.0, 0.0);
	//glUniform2f(ulAcc, sin(m_ParticleTime), 0.0);
	glUniform2f(ulAcc, cos(m_ParticleTime/10.f), sin(m_ParticleTime / 10.f));



	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribPosition, 
		3, 
		GL_FLOAT, 
		GL_FALSE, 
		stride, 0);
	

	int attribStartTime = glGetAttribLocation(shader, "a_StartTime");
	glEnableVertexAttribArray(attribStartTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);	
	// Ȥ���� �𸣴� �̻��� �����ϹǷ� �ѹ� �� ȣ��
	// �� �Լ��� ó���ð� ������ ª���Ƿ� �Ƴ� �ʿ� ����
	// ���������� ���ؽ�Ʈ ����Ī

	glVertexAttribPointer(attribStartTime,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(GLvoid*)(sizeof(float)*3));
		// �����°���� ����
		
	// ���ؽ��� attrib �� �ٿ� �־ ���� / �ʹ� ������ ũ����



	int attribVelocity = glGetAttribLocation(shader, "a_Velocity");
	glEnableVertexAttribArray(attribVelocity);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);

	glVertexAttribPointer(attribVelocity,
		3,
		GL_FLOAT,
		GL_FALSE,
		stride,
		(GLvoid*)(sizeof(float) * 4));


	int attribLifeTime = glGetAttribLocation(shader, "a_LifeTime");
	glEnableVertexAttribArray(attribLifeTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribLifeTime,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 7));


	int attribLAmp = glGetAttribLocation(shader, "a_Amp");
	glEnableVertexAttribArray(attribLAmp);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribLAmp,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 8));

	int attribPeriod = glGetAttribLocation(shader, "a_Period");
	glEnableVertexAttribArray(attribPeriod);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribPeriod,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 9));

	int attribValue = glGetAttribLocation(shader, "a_Value");
	glEnableVertexAttribArray(attribValue);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribValue,
		1,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 10));

	int attribColor = glGetAttribLocation(shader, "a_Color");
	glEnableVertexAttribArray(attribColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleCloudVBO);
	glVertexAttribPointer(attribColor,
		4,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 11));

	//���ؽ� ��
	glDrawArrays(GL_TRIANGLES, 0, m_ParticleCloudVertexCount);

	glDisableVertexAttribArray(attribPosition);

	glDisable(GL_BLEND);
}

void Renderer::DrawFSSandbox()
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint shader = m_FSSandBoxShader;

	glUseProgram(shader);

	GLuint stride = sizeof(float) * 3;


	int ulTime = glGetUniformLocation(shader, "u_Time");
	glUniform1f(ulTime, m_FSSandboxTime);
	m_FSSandboxTime += 0.016f;	// ������ Ÿ�� : ��Ȯ���� ����



	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_FSSandboxVBO);
	glVertexAttribPointer(attribPosition,
		3,
		GL_FLOAT,
		GL_FALSE,
		stride, 0);


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(attribPosition);
	//glDisable(GL_BLEND);
}

void Renderer::DrawGridMesh()
{
	// Program select
	GLuint shader = m_GridMeshShader;
	glUseProgram(shader);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	GLuint ul_Time = glGetUniformLocation(shader, "u_Time");
	glUniform1f(ul_Time, m_GridMeshTime);
	m_GridMeshTime += 0.016;

	glDrawArrays(GL_LINE_STRIP, 0, m_GridMeshVertexCount);

	glDisableVertexAttribArray(attribPosition);
}

void Renderer::DrawTextureSandbox()
{
	GLuint shader = m_TextureSandboxShader;

	glUseProgram(shader);

	GLuint stride = sizeof(float) * 5;


	int ulTime = glGetUniformLocation(shader, "u_Time");
	glUniform1f(ulTime, m_TextureSandboxTime);
	m_TextureSandboxTime += 0.016f;	// ������ Ÿ�� : ��Ȯ���� ����

	int ulSampler = glGetUniformLocation(shader, "u_Texture");
	glUniform1f(ulSampler, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);


	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glVertexAttribPointer(attribPosition,
		3,
		GL_FLOAT,
		GL_FALSE,
		stride, 0);

	int attribTexture = glGetAttribLocation(shader, "a_Texture");
	glEnableVertexAttribArray(attribTexture);
	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glVertexAttribPointer(attribTexture,
		2,
		GL_FLOAT,
		GL_FALSE,
		stride, (GLvoid*)(sizeof(float) * 3));


	glDrawArrays(GL_TRIANGLES, 0, 6);
}




