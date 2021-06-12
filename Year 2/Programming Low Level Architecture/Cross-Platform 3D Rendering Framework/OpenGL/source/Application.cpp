//Includes - In-App > External > Windows
#include "Application.h"
#include "ShaderUtilities.h"
#include "Utilities.h"
#include "TextureManager.h"
#include "Texture.h"
#include <OBJLoader.h>

#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <string>
#include <Windows.h>

//Constructor and Destructor
Application::Application() : m_cameraMatrix(0), m_projectionMatrix(0), m_lineProgram(0), m_objProgram(0), m_skyboxProgram(0),m_lineVBO(0), m_objModelBuffer{ 0,0 }, m_objModel(nullptr), lines(0), m_lightAmbient(0), m_lightDiffuse(0), m_lightPos(0), m_lightSpecular(0), m_lineFragmentShader(0), m_lineVertexShader(0),m_objFragmentShader(0), m_objVertexShader(0),m_skyboxFragmentShader(0), m_skyboxVertexShader(0),m_skyboxTexID(0), m_skyboxTexture(nullptr), m_skyboxVBO(0),m_vaoSkybox(0), m_vaoLines(0), m_vaoOBJModel(0){}
Application::~Application(){}

//On Creation of App
bool Application::OnCreate()
{
	SetForegroundWindow(m_consoleWindow);

	glClearColor(0.25f, 0.45f, 0.75f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

#pragma region Line Loading
	m_lineVertexShader = ShaderUtilities::LoadShader("../resource/shaders/vertex.glsl", GL_VERTEX_SHADER);
	m_lineFragmentShader = ShaderUtilities::LoadShader("../resource/shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	m_lineProgram = ShaderUtilities::CreateProgram(m_lineVertexShader, m_lineFragmentShader);

	lines = new Line[42];

	for (int i = 0, j = 0; i < 21; ++i, j += 2)
	{
		lines[j].v0.position = glm::vec4(-10 + i, 0.0f, 10.0f, 1.0f);
		lines[j].v0.colour = (i == 10) ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		lines[j].v1.position = glm::vec4(-10 + i, 0.0f, -10.0f, 1.0f);
		lines[j].v1.colour = (i == 10) ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		lines[j + 1].v0.position = glm::vec4(10, 0.0f, -10.0f + i, 1.0f);
		lines[j + 1].v0.colour = (i == 10) ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		lines[j + 1].v1.position = glm::vec4(-10, 0.0f, -10.0f + i, 1.0f);
		lines[j + 1].v1.colour = (i == 10) ? glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) : glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	glGenBuffers(1, &m_lineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);

	glBufferStorage(GL_ARRAY_BUFFER, sizeof(Line) * 42, lines, 0);

	glGenVertexArrays(1, &m_vaoLines);
	glBindVertexArray(m_vaoLines);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), ((char*)0 + 16));
	glBindBuffer(GL_ARRAY_BUFFER, m_lineVBO);

	glBindVertexArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_cameraMatrix = glm::inverse(glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, m_windowWidth / (float)m_windowHeight, 0.1f, 1000.0f);
#pragma endregion

#pragma region OBJ Loading
	Utilities::LoadOBJ(m_objModel, m_objPath, m_objSize, m_objProgram, m_objModelBuffer, m_vaoOBJModel, m_objVertexShader, m_objFragmentShader);
#pragma endregion

#pragma region Skybox Loading
	Utilities::LoadSkybox(m_skyboxPath, m_skyboxTexture, m_skyboxTexID, m_skyboxVBO, m_vaoSkybox, m_skyboxVertexShader, m_skyboxFragmentShader, m_skyboxProgram);
#pragma endregion

	//Light Settings
	m_lightPos = glm::vec4(20.f, 15.f, 0.f, 1.f);
	m_lightAmbient = glm::vec3(.3f, .3f, .3f);
	m_lightDiffuse = glm::vec3(1.f, 1.f, 1.f);
	m_lightSpecular = glm::vec3(1.f, 1.f, 1.f);

	Utilities::ReloadConsoleText(m_objPath, m_objSize, m_skyboxPath);

	SetWindowPos(m_consoleWindow, HWND_TOP, 0, 0, 800, 600, SWP_SHOWWINDOW);

	glfwFocusWindow(m_window);

	int width, height;
	glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &width, &height);
	glfwSetWindowPos(m_window, width / 2, height / 2);

	return true;
}

//Update Method of App
void Application::Update(float deltaTime)
{
	//OBJ Change
	if (glfwGetKey(m_window, 'O') == GLFW_PRESS)
	{
		SetForegroundWindow(m_consoleWindow);

		Utilities::LoadOBJ(m_objModel, m_objPath, m_objSize, m_objProgram, m_objModelBuffer, m_vaoOBJModel, m_objVertexShader, m_objFragmentShader);
		Utilities::ReloadConsoleText(m_objPath, m_objSize, m_skyboxPath);
		
		glfwFocusWindow(m_window);
	}
	
	//Skybox Change
	if (glfwGetKey(m_window, 'P') == GLFW_PRESS)
	{
		SetForegroundWindow(m_consoleWindow);

		Utilities::LoadSkybox(m_skyboxPath, m_skyboxTexture, m_skyboxTexID, m_skyboxVBO, m_vaoSkybox, m_skyboxVertexShader, m_skyboxFragmentShader, m_skyboxProgram);
		Utilities::ReloadConsoleText(m_objPath, m_objSize, m_skyboxPath);

		glfwFocusWindow(m_window);
	}

	//Movement
	Utilities::FreeMovement(m_cameraMatrix, 0.016f, 2.0f);

	//Lighting Calculations
	float s = sinf(deltaTime * .2f);
	float c = cosf(deltaTime * .2f);
	glm::vec4 tempVec = m_lightPos;
	m_lightPos.x = tempVec.x * c - tempVec.z * s;
	m_lightPos.z = tempVec.x * s + tempVec.z * c;
}

//Draw Method of App
void Application::Draw()
{
	glDepthFunc(GL_LESS);
	//Clear Back Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewMatrix = glm::inverse(m_cameraMatrix);
	glm::mat4 projectionViewMatrix = m_projectionMatrix * viewMatrix;

#pragma region Line Draw
	glUseProgram(m_lineProgram);

	glBindVertexArray(m_vaoLines);

	unsigned int projectionViewUniformLocation = glGetUniformLocation(m_lineProgram, "ProjectionViewMatrix");
	glUniformMatrix4fv(projectionViewUniformLocation, 1, false, glm::value_ptr(projectionViewMatrix));
	
	glDrawArrays(GL_LINES, 0, 42 * 2);

	glBindVertexArray(0);
	glUseProgram(0);
#pragma endregion

#pragma region OBJ Draw
	if (m_objProgram)
	{
		glUseProgram(m_objProgram);
		glBindVertexArray(m_vaoOBJModel);

		projectionViewUniformLocation = glGetUniformLocation(m_objProgram, "ProjectionViewMatrix");
		glUniformMatrix4fv(projectionViewUniformLocation, 1, false, glm::value_ptr(projectionViewMatrix));

		glm::vec4 lightDir = glm::normalize(glm::vec4(.0f, .0f, .0f, 1.f) - m_lightPos);
		int lightDirectionLocation = glGetUniformLocation(m_objProgram, "lightDirection");
		glUniform4fv(lightDirectionLocation, 1, glm::value_ptr(lightDir));

		int lightAmbientLocation = glGetUniformLocation(m_objProgram, "lightAmbient");
		glUniform3fv(lightAmbientLocation, 1, glm::value_ptr(m_lightAmbient));

		int lightDiffuseLocation = glGetUniformLocation(m_objProgram, "lightDiffuse");
		glUniform3fv(lightDiffuseLocation, 1, glm::value_ptr(m_lightDiffuse));

		int lightSpecularLocation = glGetUniformLocation(m_objProgram, "lightSpecular");
		glUniform3fv(lightSpecularLocation, 1, glm::value_ptr(m_lightSpecular));

		for (int i = 0; i < m_objModel->GetMeshCount(); ++i)
		{
			int modelMatrixUniformLocation = glGetUniformLocation(m_objProgram, "ModelMatrix");
			glUniformMatrix4fv(modelMatrixUniformLocation, 1, false, glm::value_ptr(m_objModel->GetWorldMatrix()));

			int cameraPositionUniformLocation = glGetUniformLocation(m_objProgram, "CameraPos");
			glUniform4fv(cameraPositionUniformLocation, 1, glm::value_ptr(m_cameraMatrix[3]));

			OBJMesh* pMesh = m_objModel->GetMeshByIndex(i);

			int kALocation = glGetUniformLocation(m_objProgram, "kA");
			int kDLocation = glGetUniformLocation(m_objProgram, "kD");
			int kSLocation = glGetUniformLocation(m_objProgram, "kS");

			OBJMaterial* pMaterial = pMesh->m_material;

			if (pMaterial != nullptr)
			{
				int useTexturesLocation = glGetUniformLocation(m_objProgram, "useTextures");
				glUniform1i(useTexturesLocation, 1);

				glUniform4fv(kALocation, 1, glm::value_ptr(pMaterial->kA));
				glUniform4fv(kDLocation, 1, glm::value_ptr(pMaterial->kD));
				glUniform4fv(kSLocation, 1, glm::value_ptr(pMaterial->kS));

				int texUniformLocation = glGetUniformLocation(m_objProgram, "DiffuseTexture");
				glUniform1i(texUniformLocation, 0);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, pMaterial->textureIDs[OBJMaterial::TextureTypes::DiffuseTexture]);

				texUniformLocation = glGetUniformLocation(m_objProgram, "SpecularTexture");
				glUniform1i(texUniformLocation, 1);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, pMaterial->textureIDs[OBJMaterial::TextureTypes::SpecularTexture]);

				texUniformLocation = glGetUniformLocation(m_objProgram, "NormalTexture");
				glUniform1i(texUniformLocation, 2);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, pMaterial->textureIDs[OBJMaterial::TextureTypes::NormalTexture]);
			}
			else
			{
				glUniform4fv(kALocation, 1, glm::value_ptr(glm::vec4(0.25f, 0.25f, 0.25f, 1.0f)));
				glUniform4fv(kDLocation, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
				glUniform4fv(kSLocation, 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 64.0f)));
			}

			glBindBuffer(GL_ARRAY_BUFFER, m_objModelBuffer[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_objModelBuffer[1]);

			glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(OBJVertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, pMesh->m_indices.size(), GL_UNSIGNED_INT, 0);
		}

		glBindVertexArray(0);
		glUseProgram(0);
	}	
#pragma endregion

#pragma region Skybox Draw
	if (m_skyboxProgram)
	{
		glDepthFunc(GL_LEQUAL);
		glUseProgram(m_skyboxProgram);
		glDepthMask(GL_FALSE);

		projectionViewUniformLocation = glGetUniformLocation(m_skyboxProgram, "ProjectionViewMatrix");
		glUniformMatrix4fv(projectionViewUniformLocation, 1, false, glm::value_ptr(projectionViewMatrix));

		glBindVertexArray(m_vaoSkybox);

		glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxTexID);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);

		glUseProgram(0);
	}
#pragma endregion
}

//Destroys the Application
void Application::Destroy()
{
	glDeleteBuffers(1, &m_skyboxVBO);
	glDeleteVertexArrays(1, &m_vaoSkybox);

	delete m_objModel;
	glDeleteBuffers(2, m_objModelBuffer);
	glDeleteVertexArrays(1, &m_vaoOBJModel);

	delete[] lines;
	glDeleteBuffers(1, &m_lineVBO);
	glDeleteVertexArrays(1, &m_vaoLines);

	ShaderUtilities::DeleteProgram(m_skyboxProgram);
	ShaderUtilities::DeleteShader(m_skyboxFragmentShader);
	ShaderUtilities::DeleteShader(m_skyboxVertexShader);

	ShaderUtilities::DeleteProgram(m_objProgram);
	ShaderUtilities::DeleteShader(m_objFragmentShader);
	ShaderUtilities::DeleteShader(m_objVertexShader);

	ShaderUtilities::DeleteProgram(m_lineProgram);
	ShaderUtilities::DeleteShader(m_lineFragmentShader);
	ShaderUtilities::DeleteShader(m_lineVertexShader);

	ShaderUtilities::DestroyInstance();

	TextureManager::DestoryInstance();
}