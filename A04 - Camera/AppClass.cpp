/*
	Jared Baker, A03 Camera, got the movements right but wasn't able to correclty implement the mouse movements to control the camera
*/
#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Jared Baker - jdb3959@rit.edu";

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUp(
			vector3(0.0f, 3.0f, 20.0f), //Where my eyes are
			vector3(0.0f, 3.0f, 19.0f), //where what I'm looking at is
			AXIS_Y);					//what is up

	//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Add objects to the Manager
	for (int j = -50; j < 50; j += 2)
	{
		for (int i = -50; i < 50; i += 2)
		{
			m_pMyMeshMngr->AddConeToRenderList(glm::translate(vector3(i, 0.0f, j)));
		}
	}
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	static float xPos = 0;
	static vector3 target = vector3(0.0f, 3.0f, 19.0f);
	static vector3 position = vector3(0.0f, 3.0f, 20.0f);
	static vector3 k = vector3(0, 1, 0);
	static vector3 j = vector3(0, 0, 1);
	//static vector3 target = m_pCamera->GetTarget();

	//gets the vector between the trget and cmera position and trys to maintain the lenght between them
	vector3 change = target - position;
	change /= change.length();
	vector3 rotated = change * cosf(PI / 2) + glm::cross(k, change) * sinf(PI / 2) + k * glm::dot(k, change) * (1 - cosf(PI / 2));
	rotated /= rotated.length();
	static float angleX = 0; 
	static float angleY = 0;

	// moves the position of the camera in relation to the location of the target.
	if (control == 1)
	{
		position = position + change;
		target = target + change;
	}
	else if (control == 2)
	{	
		position = position + rotated;
		target = target + rotated;
	}
	else if (control == 3)
	{
		position = position - change;
		target = target - change;
	}
	else if (control == 4)
	{
		position = position - rotated;
		target = target - rotated;
	}

	//my attempt at getting the mouse movements and rotation.  the Camera does still move in the right directions when rotated, but the 
	// the speed increas as it rotates more due to the target getting farther away.
	if (gui.m_bMousePressed[2] == true)
	{
		if (gui.io.MousePos.x >= 10)
		{
			angleX += 1;
		}
		if (gui.io.MousePos.x <= -10)
		{
			angleX -= 1;
		}
		if (gui.io.MousePos.y >= 10)
		{
			angleY += 1;
		}
		if (gui.io.MousePos.y <= -10)
		{
			angleY -= 1;
		}
		if (angleY >= 90)
		{
			angleY = 89;
		}
		else if (angleY <= -90)
		{
			angleY = 89;
		}

		// changes the degrees to radians and rotaes the change meant for the camera
		angleX = glm::radians(angleX);
		angleY = glm::radians(angleY);
		change = change * cosf(angleX) + glm::cross(k, change) * sinf(angleX) + k * glm::dot(k, change) * (1 - cosf(angleX));
		change = change * cosf(angleY) + glm::cross(j, change) * sinf(angleY) + j * glm::dot(j, change) * (1 - cosf(angleY));
		change /= change.length();
		target = change;
	}

	m_pCamera->SetPosition(position);
	m_pCamera->SetTarget(target);
	m_pCamera->SetUp(AXIS_Y);

	//control = 0;
	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the singleton
	MyMeshManager::ReleaseInstance();

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
