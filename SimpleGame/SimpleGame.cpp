/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

Renderer *g_Renderer = NULL;

// 새로 추가
void RenderSceneTimer(int value)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	//g_Renderer->DrawTest();
	//g_Renderer->DrawParticle();
	//g_Renderer->DrawParticleCloud();
	//g_Renderer->DrawFSSandbox();
	//g_Renderer->DrawGridMesh();
	g_Renderer->DrawTextureSandbox();

	// 더블 버퍼 스왑
	glutSwapBuffers();
	glutTimerFunc(16, RenderSceneTimer, 1);
}

void RenderScene(void)
{
	g_Renderer->DrawTotal();

	glutSwapBuffers();
	glutTimerFunc(16, RenderSceneTimer, 1);
}



void Idle(void)
{
	// RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	// 혹시 모르니 빼주자
	//RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	//RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	//RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(16, RenderSceneTimer, 1);


	glutMainLoop();

	delete g_Renderer;

    return 0;
}