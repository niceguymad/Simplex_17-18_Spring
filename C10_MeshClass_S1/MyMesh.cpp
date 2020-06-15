#include "MyMesh.h"
MyMesh::MyMesh()
{
	m_uShaderProgramID = LoadShaders("Shaders//Basic.vs", "Shaders//BasicColor.fs");
}

MyMesh::~MyMesh()
{
	glDeleteBuffers(1, &m_uVBO);
	glBindVertexArray(0); // Unbind VAO
	glDeleteVertexArrays(1, &m_uVAO);
}

void MyMesh::AddVertexPosition(vector3 a_v3Value){	m_lPos.push_back(a_v3Value); m_uVertexCount = m_lPos.size();}
void MyMesh::AddVertexColor(vector3 a_v3Value){	m_lCol.push_back(a_v3Value); }

void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; i++)
	{
		m_lCol.push_back(a_v3Color);
	}
}

void MyMesh::CompileMesh(void)
{
	if (m_bInitialized)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		m_lVertex.push_back(m_lPos[i]);
		m_lVertex.push_back(m_lCol[i]);
	}
	
	glGenVertexArrays(1, &m_uVAO);//Generate vertex array object
	glGenBuffers(1, &m_uVBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_uVAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBO);//Bind the VBO

										  //Generate space for the VBO (vertex count times size of vec3)
	glBufferData(GL_ARRAY_BUFFER, m_lVertex.size() * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);

	//count the attributes
	int attributeCount = 2;

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bInitialized = true;

	glBindVertexArray(0);//Bind the VAO
}
void MyMesh::Render(matrix4 a_m4Model, matrix4 a_mView, matrix4 a_mProjection)
{
	if (!m_bInitialized)
		return;

	glUseProgram(m_uShaderProgramID);
	glBindVertexArray(m_uVAO);//Bind the VAO

	//read uniforms and send values
	GLuint MVP = glGetUniformLocation(m_uShaderProgramID, "MVP");//Model View Projection
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(a_mProjection * a_mView * a_m4Model));

	GLuint SolidColor = glGetUniformLocation(m_uShaderProgramID, "SolidColor"); //custom color of the shape
	glUniform3f(SolidColor, -1.0f, -1.0f, -1.0f);

	//draw content					This was 3 but I changed it to VertexCount after I found I could only create 1 triangle
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
}

//Creates Circle with specified radius size, number of sides, and color
void MyMesh::Circle(float radius = 5, float sides = 3, vector3 color = vector3(1, 0, 1))
{	
	//finds the radians for the triangle angles by dividing 360 by the number of sides, and converting to radians
	float radians = (360 / sides) * (PI / 180);

	//Starting values for the vectors used for the triangles 
	 vector3 start = vector3(0, 0, 0);
	 vector3 middle = vector3(radius, 0, 0);
	vector3 end = vector3(cosf(radians) * radius, sinf(radians) * radius, 0);

	//creates the amount of triangles needed for the number of sides wanted
	for (int i = 1; i <= sides; i++)
	{		
		CreateTri(start, middle, end);	
		middle = end;
		end = vector3(cosf(radians * (i + 1)) * radius, sinf(radians * (i + 1)) * radius, 0);
	}


	CompleteMesh(color);
	CompileMesh();
}

void MyMesh::CreateTri(vector3 point1, vector3 point2, vector3 point3)
{

	AddVertexPosition(point1);
	AddVertexPosition(point2);
	AddVertexPosition(point3);

}
