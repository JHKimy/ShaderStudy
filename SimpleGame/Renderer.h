#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized(); 
	//void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
	
	void DrawTest();
	
	//새로운 함수
	void DrawParticle();

	void DrawParticleCloud();

	void DrawFSSandbox();

	void DrawGridMesh();

	void DrawTextureSandbox();



private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	
	void CreateVertexBufferObjects();

	
	void GetGLPosition(float x, float y, float *newX, float *newY);

	// 파티클 생성
	void CreateParticleCloud(int numParticles);
	
	void CreateGridMesh(int x, int y);



	GLuint CreatePngTexture(char* filePath, GLuint samplingMethod);



	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 512;
	unsigned int m_WindowSizeY = 512;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;
	GLuint m_TestVBO = 0;
	// 새로운 셰이더 생성
	GLuint m_ParticleShader = 0;
	GLuint m_ParticleVBO = 0;



	GLuint m_ParticleCloudShader = 0;
	GLuint m_ParticleCloudVBO = 0;
	GLuint m_ParticleCloudVertexCount = 0;
	float m_ParticleTime = 0.f;



	GLuint m_FSSandBoxShader = 0;
	GLuint m_FSSandboxVBO = 0;
	float m_FSSandboxTime = 0;

	GLuint m_GridMeshShader = 0;
	GLuint m_GridMeshVBO = 0;
	GLuint m_GridMeshVertexCount = 0;
	float m_GridMeshTime = 0;





	GLuint m_TextureSandboxShader = 0;
	GLuint m_TextureSandboxVBO = 0;
	float m_TextureSandboxTime = 0;
	GLuint m_RGBTexture = 0;

	GLuint m_NumberTexture[10];
	GLuint m_NumbersTexture;





	void CreateFBO();
	GLuint m_A_FBOTexture0;
	GLuint m_A_FBOTexture1;
	
	GLuint m_A_FBO;

	GLuint m_TextureShader;
	GLuint m_TextureVBO;


	GLuint m_FullRectVBO;
	GLuint m_AlphaClearShader;
	void DrawAlphaClear(float r, float g, float b, float a);

	GLuint m_HDRFBO;
	GLuint m_HDRHighTexture;
	GLuint m_HDRLowTexture;

	GLuint m_ParticleTexture;


public:
	void DrawTotal();
	void DrawTexture(float x, float y, float sizeX, float sizeY, GLuint texID);
};