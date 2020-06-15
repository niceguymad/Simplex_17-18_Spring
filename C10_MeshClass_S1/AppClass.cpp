/*
	Jared Baker, E04- Circle Creation
*/
#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Jared Baker - jdb3959@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	m_pMesh = new MyMesh();

	// creates a circle, with a radius of 5, 12 sides, and a purple color
	m_pMesh->Circle(5, 12, vector3(1, 0, 1));
	// I chose 12 becuase that the finale, pic on the assignment, but it should work with all numbers,
	// I've tested a few and after changing the sides variable to a float rather than a int there seems to be no problem with numbers that don't divide well.
	// does not work with decimals in the number of sides
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	m_pMesh->Render(ToMatrix4(m_qArcBall), m_pCameraMngr->GetViewMatrix(), m_pCameraMngr->GetProjectionMatrix());

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	//release GUI
	ShutdownGUI();
}