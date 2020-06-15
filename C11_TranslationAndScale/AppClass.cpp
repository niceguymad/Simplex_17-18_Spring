#include "AppClass.h"
void Application::InitVariables(void)
{
	alienMesh = std::vector<MyMesh*>();
	//init the mesh
	m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	for (int i = 0; i < 46; i++)
	{
		m_pMesh = new MyMesh();
		alienMesh.push_back(m_pMesh);
		alienMesh[i]->GenerateCube(1.0f, C_BLACK);
	}

	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4Model = matrix4(0);
	float xOffset = 0;
	static float value = 0.0f;
	matrix4 m4Translate = matrix4(0);
	

	m4Model = glm::translate(IDENTITY_M4, vector3(value,  2.0f, 3.0f));
	alienMesh[0]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(2 + value, 2.0f, 3.0f));
	alienMesh[1]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(8 + value, 2.0f, 3.0f));
	alienMesh[2]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(10 + value, 2.0f, 3.0f));
	alienMesh[3]->Render(m4Projection, m4View, m4Model);


	m4Model = glm::translate(IDENTITY_M4, vector3(3 + value, 1.0f, 3.0f));
	alienMesh[4]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(4 + value, 1.0f, 3.0f));
	alienMesh[5]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(6 + value, 1.0f, 3.0f));
	alienMesh[6]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(7 + value, 1.0f, 3.0f));
	alienMesh[7]->Render(m4Projection, m4View, m4Model);

	xOffset = 8;
	for (int i = 8; i < 19; i++)
	{
		if (i == 9 || i == 17)
		{

		}
		else
		{
			m4Model = glm::translate(IDENTITY_M4, vector3(i-xOffset + value, 3.0f, 3.0f));
			alienMesh[i]->Render(m4Projection, m4View, m4Model);
		}
	}
	xOffset = 19;
	for (int i = 19; i < 30; i++)
	{
			m4Model = glm::translate(IDENTITY_M4, vector3(i- xOffset + value, 4.0f, 3.0f));
			alienMesh[i]->Render(m4Projection, m4View, m4Model);
	}
	xOffset = 29;
	for (int i = 30; i < 39; i++)
	{
		if (i == 32 || i == 36)
		{

		}
		else
		{
			m4Model = glm::translate(IDENTITY_M4, vector3(i - xOffset + value, 5.0f, 3.0f));
			alienMesh[i]->Render(m4Projection, m4View, m4Model);
		}
	}
	xOffset = 37;
	for (int i = 39; i < 46; i++)
	{
		m4Model = glm::translate(IDENTITY_M4, vector3(i - xOffset + value, 6.0f, 3.0f));
		alienMesh[i]->Render(m4Projection, m4View, m4Model);
	}

	m4Model = glm::translate(IDENTITY_M4, vector3(3 + value, 7.0f, 3.0f));
	alienMesh[4]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(7 + value, 7.0f, 3.0f));
	alienMesh[5]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(2 + value, 8.0f, 3.0f));
	alienMesh[6]->Render(m4Projection, m4View, m4Model);
	m4Model = glm::translate(IDENTITY_M4, vector3(8 + value, 8.0f, 3.0f));
	alienMesh[7]->Render(m4Projection, m4View, m4Model);

	value += 0.01f;
	//matrix4 m4Model = m4Translate * m4Scale;
	m4Model = m4Translate;

	//m_pMesh->Render(m4Projection, m4View, m4Model);
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}