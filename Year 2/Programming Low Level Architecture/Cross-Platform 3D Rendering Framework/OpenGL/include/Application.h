#pragma once
//Includes - In-App > External > Windows
#include "Framework.h"

#include <glm/glm.hpp>

#include <string>

class OBJModel;
class Texture;

class Application : public Framework
{
public:
	Application();
	virtual ~Application();

protected:
	virtual bool OnCreate();
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Destroy();

private:
	typedef struct Vertex
	{
		glm::vec4 position;
		glm::vec4 colour;
	}Vertex;

	typedef struct Line
	{
		Vertex v0;
		Vertex v1;
	}Line;

	glm::mat4 m_cameraMatrix;
	glm::mat4 m_projectionMatrix;

	unsigned int m_lineProgram;
	unsigned int m_lineVertexShader;
	unsigned int m_lineFragmentShader;
	unsigned int m_lineVBO;
	unsigned int m_vaoLines;

	unsigned int m_objProgram;
	unsigned int m_objVertexShader;
	unsigned int m_objFragmentShader;
	unsigned int m_objModelBuffer[2];
	unsigned int m_vaoOBJModel;
	std::string m_objPath;
	float m_objSize = 0.0f;

	unsigned int m_skyboxProgram;
	unsigned int m_skyboxVertexShader;
	unsigned int m_skyboxFragmentShader;
	unsigned int m_skyboxVBO;
	unsigned int m_vaoSkybox;
	Texture* m_skyboxTexture;
	unsigned int m_skyboxTexID;
	std::string m_skyboxPath;

	glm::vec4 m_lightPos;
	glm::vec3 m_lightAmbient;
	glm::vec3 m_lightDiffuse;
	glm::vec3 m_lightSpecular;

	OBJModel* m_objModel;
	Line* lines;
};

