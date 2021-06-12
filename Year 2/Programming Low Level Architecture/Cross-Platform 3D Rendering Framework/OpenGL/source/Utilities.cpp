//Includes - In-App > External > Windows
#include "Utilities.h"
#include "ShaderUtilities.h"
#include "TextureManager.h"
#include "Texture.h"
#include <OBJLoader.h>

#include <Windows.h>
#include <CommCtrl.h>
#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <experimental/filesystem>

#define nline std::cout << std::endl;

//Variables
static double s_prevTime = 0;
static float s_totalTime = 0;
static float s_deltaTime = 0;

//Resets the On-going Timer
void Utilities::ResetTimer()
{
	s_prevTime = glfwGetTime();
	s_totalTime = 0;
	s_deltaTime = 0;
}

//Tick the On-Going Timer
float Utilities::TickTimer()
{
	double currentTime = glfwGetTime();
	s_deltaTime = (float)(currentTime - s_prevTime);
	s_totalTime += s_deltaTime;
	s_prevTime = currentTime;
	return s_deltaTime;
}

//Returns the Delta Time
float Utilities::GetDeltaTime() { return s_deltaTime; }

//Returns the Total Time
float Utilities::GetTotalTime() { return s_totalTime; }

//Takes File and Puts into a Buffer
char* Utilities::FileToBuffer(const char* a_sPath)
{
	std::fstream file;
	file.open(a_sPath, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileSize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);

		if (fileSize == 0)
		{
			file.close();
			return nullptr;
		}

		char* dataBuffer = new char[fileSize + 1];
		memset(dataBuffer, 0, fileSize + 1);
		file.read(dataBuffer, fileSize);

		file.close();
		return dataBuffer;
	}

	return nullptr;
}

//Searches for all OBJ Files in this Directory and Sub-Directories (via Recursive)
void Utilities::SearchModelDirectories(std::string a_dPath, std::vector<std::string> &a_fPaths, int &count)
{
	for (const auto& entry : std::experimental::filesystem::directory_iterator(a_dPath))
	{
		if (entry.path().extension() != ".obj")
		{
			if (entry.path().extension() != ".mtl" || entry.path().extension() != ".tga")
			{
				SearchModelDirectories(entry.path().u8string(), a_fPaths, count);
			}
		}
		else
		{
			std::cout << count << ": " << entry.path() << std::endl;
			a_fPaths.push_back(entry.path().u8string());
			count++;
		}
	}
}

//Searches for all Directories and Sub-Directories for Possible Skyboxes in JPG Format (via Recursive)
bool Utilities::SearchSkyboxDirectories(std::string a_dPath, std::vector<std::string>& a_fPaths, int& count)
{
	for (const auto& entry : std::experimental::filesystem::directory_iterator(a_dPath))
	{
		if (entry.path().extension() != ".jpg")
		{
			if (SearchSkyboxDirectories(entry.path().u8string(), a_fPaths, count))
			{
				std::cout << count << ": " << entry.path() << std::endl;
				a_fPaths.push_back(entry.path().u8string());
				count++;
			}
		}
		else
		{
			return true;
		}
	}

	return true;
}

//Loads/Reloads the Skybox
void Utilities::LoadSkybox(std::string &a_skyboxPath, Texture* &a_skyboxTexture, unsigned int &a_skyboxTexID, unsigned int &a_skyboxVBO, unsigned int &a_vaoSkybox, unsigned int &a_skyboxVertexShader, unsigned int &a_skyboxFragmentShader, unsigned int &a_skyboxProgram)
{
	if (a_skyboxProgram)
	{
		ShaderUtilities::DeleteShader(a_skyboxFragmentShader);
		a_skyboxFragmentShader = 0;

		ShaderUtilities::DeleteShader(a_skyboxVertexShader);
		a_skyboxVertexShader = 0;

		ShaderUtilities::DeleteProgram(a_skyboxProgram);
		a_skyboxProgram = 0;

		glClear(a_skyboxVBO);
		glClear(a_vaoSkybox);
		delete a_skyboxTexture;
		a_skyboxTexture = nullptr;
	}

	std::string dirPath = "../resource/skybox/";
	std::vector<std::string> filePaths;
	filePaths.push_back("0: No Skybox");

	int choice;
	int skyboxCount = 1;

	std::cout << "Select a Skybox from this list:" << std::endl;
	std::cout << filePaths[0] << std::endl;
	SearchSkyboxDirectories(dirPath, filePaths, skyboxCount);

	std::cout << "Skybox Select: ";
	bool validChoice = false;

	do
	{
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
		}

		if (choice < 0 || choice > skyboxCount)
		{
			std::cout << "Invalid input.  Try again: ";
		}
		else
		{
			validChoice = true;
		}
	} while (validChoice == false);

	a_skyboxPath = filePaths[choice];

	if (choice != 0)
	{
		//Path to Skybox
		std::vector<std::string> skyboxFaces
		{
			a_skyboxPath + "/right.jpg",
			a_skyboxPath + "/left.jpg",
			a_skyboxPath + "/top.jpg",
			a_skyboxPath + "/bottom.jpg",
			a_skyboxPath + "/front.jpg",
			a_skyboxPath + "/back.jpg"
		};

		//Skybox Tags
		unsigned int cubemapImageTags[6] =
		{
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		//New Texture
		a_skyboxTexture = new Texture();
		a_skyboxTexID = a_skyboxTexture->LoadSkyboxFaces(skyboxFaces, cubemapImageTags);

		//Shader and Program Compliation
		a_skyboxVertexShader = ShaderUtilities::LoadShader("../resource/shaders/skybox_vertex.glsl", GL_VERTEX_SHADER);
		a_skyboxFragmentShader = ShaderUtilities::LoadShader("../resource/shaders/skybox_fragment.glsl", GL_FRAGMENT_SHADER);
		a_skyboxProgram = ShaderUtilities::CreateProgram(a_skyboxVertexShader, a_skyboxFragmentShader);

		//Skybox Vertices
		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		//Set Up VAO and VBO
		glGenBuffers(1, &a_skyboxVBO);
		glBindBuffer(GL_ARRAY_BUFFER, a_skyboxVBO);

		glBufferStorage(GL_ARRAY_BUFFER, sizeof(float) * 108, skyboxVertices, 0);

		glGenVertexArrays(1, &a_vaoSkybox);
		glBindVertexArray(a_vaoSkybox);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
		glBindBuffer(GL_ARRAY_BUFFER, a_skyboxVBO);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

//Loads/Reloads the Skybox
bool Utilities::LoadOBJ(OBJModel* &a_objModel, std::string& a_objPath, float &a_objSize, unsigned int &a_objProgram, unsigned int* a_objModelBuffer, unsigned int &a_vaoOBJModel, unsigned int &a_objVertexShader, unsigned int &a_objFragmentShader)
{
	if (a_objProgram)
	{
		std::cout << "Please Wait. Clearing out Previous Model...." << std::endl;
		nline;

		TextureManager* pTM = TextureManager::GetInstance();

		for (int i = 0; i < a_objModel->GetMaterialCount(); ++i)
		{
			OBJMaterial* mat = a_objModel->GetMaterialByIndex(i);

			for (int n = 0; n < OBJMaterial::TextureTypes::TextureTypes_Count; ++n)
			{
				if (mat->textureFileNames[n].size() > 0)
				{
					unsigned int textureID = pTM->GetTexture(mat->textureFileNames[n].c_str());
					pTM->ReleaseTexture(textureID);
				}
			}
		}

		delete a_objModel;
		a_objModel = nullptr;

		glDeleteBuffers(2, a_objModelBuffer);
		glDeleteVertexArrays(1, &a_vaoOBJModel);

		ShaderUtilities::DeleteProgram(a_objProgram);
		ShaderUtilities::DeleteShader(a_objFragmentShader);
		ShaderUtilities::DeleteShader(a_objVertexShader);
	}

	a_objModel = new OBJModel();

	std::string dirPath = "../resource/models/";
	std::vector<std::string> filePaths;

	int choice;
	int objCount = 0;

	std::cout << "Select a Model from this list:" << std::endl;
	SearchModelDirectories(dirPath, filePaths, objCount);

	std::cout << "Model Select: ";
	bool validChoice = false;

	do
	{
		while (!(std::cin >> choice))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.  Try again: ";
		}

		if (choice < 0 || choice > objCount)
		{
			std::cout << "Invalid input.  Try again: ";
		}
		else
		{
			validChoice = true;
		}
	} while (validChoice == false);

	a_objPath = filePaths[choice];

	nline;
	std::cout << "Enter a Float for OBJ Size (between 0.01 and 10): ";
	validChoice = false;

	do
	{
		std::cin >> a_objSize;

		if (a_objSize < 0.01 || a_objSize > 10)
		{
			std::cout << "Invalid input.  Try again: ";
		}
		else
		{
			validChoice = true;
		}
	} while (validChoice == false);

	nline;

	if (a_objModel->Load(a_objPath.c_str(), a_objSize))
	{
		TextureManager* pTM = TextureManager::GetInstance();

		for (int i = 0; i < a_objModel->GetMaterialCount(); ++i)
		{
			OBJMaterial* mat = a_objModel->GetMaterialByIndex(i);

			for (int n = 0; n < OBJMaterial::TextureTypes::TextureTypes_Count; ++n)
			{
				if (mat->textureFileNames[n].size() > 0)
				{
					unsigned int textureID = pTM->LoadTexture(mat->textureFileNames[n].c_str());
					mat->textureIDs[n] = textureID;
				}
			}
		}

		a_objVertexShader = ShaderUtilities::LoadShader("../resource/shaders/obj_vertex.glsl", GL_VERTEX_SHADER);
		a_objFragmentShader = ShaderUtilities::LoadShader("../resource/shaders/obj_fragment.glsl", GL_FRAGMENT_SHADER);

		a_objProgram = ShaderUtilities::CreateProgram(a_objVertexShader, a_objFragmentShader);

		glGenBuffers(2, a_objModelBuffer);

		glGenVertexArrays(1, &a_vaoOBJModel);
		glBindVertexArray(a_vaoOBJModel);

		glBindBuffer(GL_ARRAY_BUFFER, a_objModelBuffer[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_objModelBuffer[1]);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(OBJVertex), ((char*)0) + OBJVertex::PositionOffset);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), ((char*)0) + OBJVertex::NormalOffset);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(OBJVertex), ((char*)0) + OBJVertex::UVCoordOffset);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		nline;
		
		return true;
	}
	else
	{
		std::cout << "Failed to Load Model" << std::endl;
		return false;
	}
}

//Allows for 3D Movement in World Space within App
void Utilities::FreeMovement(glm::mat4& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up)
{
	GLFWwindow* window = glfwGetCurrentContext();

	glm::vec4 vTranslation = a_transform[3];
	glm::vec4 vForward = a_transform[2];
	glm::vec4 vUp = a_transform[1];
	glm::vec4 vRight = a_transform[0];

	float frameSpeed = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? a_deltaTime * a_speed * 2 : a_deltaTime * a_speed;

	if (glfwGetKey(window, 'W') == GLFW_PRESS)
	{
		vTranslation -= vForward * frameSpeed;
	}
	if (glfwGetKey(window, 'S') == GLFW_PRESS)
	{
		vTranslation += vForward * frameSpeed;
	}
	if (glfwGetKey(window, 'D') == GLFW_PRESS)
	{
		vTranslation += vRight * frameSpeed;
	}
	if (glfwGetKey(window, 'A') == GLFW_PRESS)
	{
		vTranslation -= vRight * frameSpeed;
	}
	if (glfwGetKey(window, 'Q') == GLFW_PRESS)
	{
		vTranslation += vUp * frameSpeed;
	}
	if (glfwGetKey(window, 'E') == GLFW_PRESS)
	{
		vTranslation -= vUp * frameSpeed;
	}

	a_transform[3] = vTranslation;

	static bool sbMouseButtonDown = false;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		static double siPrevMouseX = 0;
		static double siPrevMouseY = 0;

		if (sbMouseButtonDown == false)
		{
			sbMouseButtonDown = true;
			glfwGetCursorPos(window, &siPrevMouseX, &siPrevMouseY);
		}

		double mouseX = 0, mouseY = 0;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		double iDeltaX = mouseX - siPrevMouseX;
		double iDeltaY = mouseY - siPrevMouseY;

		siPrevMouseX = mouseX;
		siPrevMouseY = mouseY;

		glm::mat4 mMat;

		if (iDeltaY != 0)
		{
			mMat = glm::axisAngleMatrix(vRight.xyz(), (float)-iDeltaY / 150.0f);
			vRight = mMat * vRight;
			vUp = mMat * vUp;
			vForward = mMat * vForward;
		}

		if (iDeltaX != 0)
		{
			mMat = glm::axisAngleMatrix(a_up, (float)-iDeltaX / 150.0f);
			vRight = mMat * vRight;
			vUp = mMat * vUp;
			vForward = mMat * vForward;
		}

		a_transform[0] = vRight;
		a_transform[1] = vUp;
		a_transform[2] = vForward;
	}
	else
	{
		sbMouseButtonDown = false;
	}
}

//Reloads the Console Text
void Utilities::ReloadConsoleText(std::string a_objPath, float a_objSize, std::string a_skyboxPath)
{
	//Console Read Out
	system("cls");

	std::cout << "Current OBJ Model: " << a_objPath << " - Size: *" << a_objSize << std::endl;
	std::cout << "Current Skybox: " << a_skyboxPath <<  std::endl;

	nline;

	std::cout << "To change the current OBJ Model, press O..." << std::endl;
	std::cout << "To chnage the current Skybox, press P..." << std::endl;

	nline;
}