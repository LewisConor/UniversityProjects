//Includes - In-App > External > Windows
#include "ShaderUtilities.h"
#include "Utilities.h"

#include <glad/glad.h>

#include <iostream>

//Constructor
ShaderUtilities::ShaderUtilities() {}

//Destructor
ShaderUtilities::~ShaderUtilities()
{
	//Delete any Shaders
	for (auto iter = mShaders.begin(); iter != mShaders.end(); ++iter)
	{
		glDeleteShader(*iter);
	}

	//Delete any Programs
	for (auto iter = mPrograms.begin(); iter != mPrograms.end(); ++iter)
	{
		glDeleteProgram(*iter);
	}
}

//Instance
ShaderUtilities* ShaderUtilities::mInstance = nullptr;

//Get Current Instance
ShaderUtilities* ShaderUtilities::GetInstance()
{
	if (mInstance == nullptr)
	{
		return ShaderUtilities::CreateInstance();
	}

	return mInstance;
}

//Create new Instance
ShaderUtilities* ShaderUtilities::CreateInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new ShaderUtilities();
	}
	else
	{
		std::cout << "Instance Creation Failed: Shader Utilities already exists..." << std::endl;
	}

	return mInstance;
}

//Destroy Current Instance
void ShaderUtilities::DestroyInstance()
{
	if (mInstance != nullptr)
	{
		delete mInstance;
		mInstance = nullptr;
	}
	else
	{
		std::cout << "Instance Destruction Failed: Shader Utilities Instance does not exist..." << std::endl;
	}
}

//Public Load Shader
unsigned int ShaderUtilities::LoadShader(const char* a_filename, unsigned int a_type)
{
	ShaderUtilities* instance = GetInstance();
	return instance->LoadShaderInternal(a_filename, a_type);
}

//Private Load Shader
unsigned int ShaderUtilities::LoadShaderInternal(const char* a_filename, unsigned int a_type)
{
	int success = GL_FALSE;

	char* source = Utilities::FileToBuffer(a_filename);
	unsigned int shader = glCreateShader(a_type);
	glShaderSource(shader, 1, (const char**)&source, 0);
	glCompileShader(shader);
	delete[] source;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (GL_FALSE == success)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, 0, infoLog);

		std::cout << "Unable to Complile:" << a_filename << std::endl;
		std::cout << infoLog << std::endl;

		delete[] infoLog;
		return 0;
	}

	mShaders.push_back(shader);
	return shader;
}

//Public Delete Shader
void ShaderUtilities::DeleteShader(unsigned int a_shaderID)
{
	ShaderUtilities* instance = GetInstance();
	instance->DeleteProgramInternal(a_shaderID);
}

//Private Delete Shader
void ShaderUtilities::DeleteShaderInternal(unsigned int a_shaderID)
{
	for (auto iter = mShaders.begin(); iter != mShaders.end(); ++iter)
	{
		if (*iter == a_shaderID)
		{
			glDeleteShader(*iter);
			mShaders.erase(iter);
			break;
		}
	}
}

//Public Create Program
unsigned int ShaderUtilities::CreateProgram(const int& a_vertexShader, const int& a_fragmentShader)
{
	ShaderUtilities* instance = GetInstance();
	return instance->CreateProgramInternal(a_vertexShader, a_fragmentShader);
}

//Private Create Program
unsigned int ShaderUtilities::CreateProgramInternal(const int& a_vertexShader, const int& a_fragmentShader)
{
	int success = GL_FALSE;

	unsigned int handle = glCreateProgram();

	glAttachShader(handle, a_vertexShader);
	glAttachShader(handle, a_fragmentShader);

	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, &success);
	if (GL_FALSE == success)
	{
		int infoLogLength = 0;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);

		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(handle, infoLogLength, 0, infoLog);

		std::cout << "Shader Linker Error" << std::endl;
		std::cout << infoLog << std::endl;

		delete[] infoLog;
		return 0;
	}

	mPrograms.push_back(handle);
	return handle;
}

//Public Delete Program
void ShaderUtilities::DeleteProgram(unsigned int a_program)
{
	ShaderUtilities* instance = GetInstance();
	instance->DeleteProgramInternal(a_program);
}

//Private Delete Program
void ShaderUtilities::DeleteProgramInternal(unsigned int a_program)
{
	for (auto iter = mPrograms.begin(); iter != mPrograms.end(); ++iter)
	{
		if (*iter == a_program)
		{
			glDeleteProgram(*iter);
			mPrograms.erase(iter);
			break;
		}
	}
}