#pragma once
#include <glm/glm.hpp>

#include <vector>
#include <string>

class OBJModel;
class Texture;

class Utilities
{
public:
	static void ResetTimer();
	static float TickTimer();
	static float GetDeltaTime();
	static float GetTotalTime();

	static char* FileToBuffer(const char* a_sPath);

	static void SearchModelDirectories(std::string a_dPath, std::vector<std::string>& a_fPaths, int& count);

	static bool SearchSkyboxDirectories(std::string a_dPath, std::vector<std::string>& a_fPaths, int& count);

	static bool LoadOBJ(OBJModel*& a_objModel, std::string& a_objPath, float& a_objSize, unsigned int& a_objProgram, unsigned int* a_objModelBuffer, unsigned int& a_vaoOBJModel, unsigned int& a_objVertexShader, unsigned int& a_objFragmentShader);

	static void LoadSkybox(std::string& a_skyboxPath, Texture*& a_skyboxTexture, unsigned int& a_skyboxTexID, unsigned int& a_skyboxVBO, unsigned int& a_vaoSkybox, unsigned int& a_skyboxVertexShader, unsigned int& a_skyboxFragmentShader, unsigned int& a_skyboxProgram);

	static void FreeMovement(glm::mat4& a_transform, float a_deltaTime, float a_speed, const glm::vec3& a_up = glm::vec3(0, 1, 0));

	static void ReloadConsoleText(std::string a_objPath, float a_objSize, std::string a_skyboxPath);
};