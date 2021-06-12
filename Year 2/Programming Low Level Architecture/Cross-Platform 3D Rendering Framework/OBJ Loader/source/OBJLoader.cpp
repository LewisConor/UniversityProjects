#include "OBJLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>

//OBJ MESH FUNCTIONS

//Calculate Single Face Normal
glm::vec4 OBJMesh::CalculateFaceNormal(const unsigned int& a_indexA, const unsigned int& a_indexB, const unsigned int& a_indexC) const
{
	glm::vec3 a = m_vertices[a_indexA].position;
	glm::vec3 b = m_vertices[a_indexB].position;
	glm::vec3 c = m_vertices[a_indexC].position;

	glm::vec3 ab = glm::normalize(b - a);
	glm::vec3 ac = glm::normalize(c - a);

	return glm::vec4(glm::cross(ab, ac), 0.0f);
}

//Calculate All the Faces
void OBJMesh::CalculateFaceNormals()
{
	for (int i = 0; i < m_indices.size(); i += 3)
	{
		glm::vec4 normal = CalculateFaceNormal(i, i + 1, i + 2);

		m_vertices[i].normal = m_vertices[i + 1].normal = m_vertices[i + 2].normal = normal;
	}
}

//OBJ MODEL FUNCTIONS

OBJModel::~OBJModel()
{
	for (int i = 0; i < m_meshes.size(); ++i)
	{
		m_meshes[i]->m_vertices.clear();
		m_meshes[i]->m_indices.clear();

		delete m_meshes[i];
		m_meshes[i] = nullptr;
	}
	m_meshes.clear();

	m_materials.clear();
}

//Load OBJ Model
bool OBJModel::Load(const char* a_filename, float a_scale)
{
	std::cout << "Attempting to open file: " << a_filename << std::endl;

	std::fstream file;
	file.open(a_filename, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		std::cout << "Successfully Opened File" << std::endl;
		std::cout << std::endl;

		std::string filePath = a_filename;
		size_t path_end = filePath.find_last_of("\/\\");

		if (path_end != std::string::npos)
		{
			filePath = filePath.substr(0, path_end + 1);
		}
		else
		{
			filePath = "";
		}

		m_path = filePath;

		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileSize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);

		if (fileSize == 0)
		{
			std::cout << "File contains no data...Closing File..." << std::endl;
			file.close();
		}

		std::cout << "OBJ File Data:" << std::endl;
		std::cout << "File size: " << fileSize / 1024 << "KB" << std::endl;

		std::string fileLine;

		OBJMesh* currentMesh = nullptr;
		OBJMaterial* currentMTL = nullptr;
		std::vector<glm::vec4> vertexData;
		std::vector<glm::vec4> normalData;
		std::vector<glm::vec2> UVData;

		while (!file.eof())
		{
			if (std::getline(file, fileLine))
			{
				if (fileLine.size() > 0)
				{
					std::string dataType = LineType(fileLine);
					if (dataType.length() == 0) { continue; }
					std::string data = LineData(fileLine);

					if (dataType == "#")
					{
						std::cout << "Comment(" <<  data << ")" << std::endl;
						continue;
					}

					if (dataType == "mtllib")
					{
						std::cout << "Material File: " << data << std::endl;
						LoadMaterialLibrary(data);
						continue;
					}

					if (dataType == "g" || dataType == "o")
					{
						std::cout << std::endl;
						std::cout << "OBJ Group Found: " << data << std::endl;;

						if (currentMesh != nullptr)
						{
							std::cout << "Current Mesh added to Mesh Vector " << std::endl;
							m_meshes.push_back(currentMesh);
						}

						std::cout << "Current Mesh Allocated" << std::endl;
						currentMesh = new OBJMesh();
						currentMesh->m_name = data;

						if (currentMTL != nullptr)
						{
							currentMesh->m_material = currentMTL;
							currentMTL = nullptr;
						}

						continue;
					}

					if (dataType == "v")
					{
						glm::vec4 vertex = ProcessVectorString(data);
						vertex *= a_scale;
						vertex.w = 1.0f;
						vertexData.push_back(vertex);
						continue;
					}

					if (dataType == "vt")
					{
						glm::vec4 uvCoordv4 = ProcessVectorString(data);
						glm::vec2 uvCoord = glm::vec2(uvCoordv4.x, uvCoordv4.y);
						UVData.push_back(uvCoord);
						continue;
					}

					if (dataType == "vn")
					{
						glm::vec4 normal = ProcessVectorString(data);
						normal.w = 0.0f;
						normalData.push_back(normal);
						continue;
					}

					if (dataType == "f")
					{
						if (currentMesh == nullptr)
						{
							currentMesh = new OBJMesh();

							if (currentMTL != nullptr)
							{
								currentMesh->m_material = currentMTL;
								currentMTL = nullptr;
							}
						}

						std::vector<std::string> faceData = SplitStringAtCharacter(data, ' ');
						unsigned int ci = currentMesh->m_vertices.size();

						for (auto iter = faceData.begin(); iter != faceData.end(); ++iter)
						{
							OBJ_Face_Triplet triplet = ProcessTriplet(*iter);
							OBJVertex currentVertex;

							currentVertex.position = vertexData[triplet.v - 1];

							if (triplet.vn != 0)
							{
								currentVertex.normal = normalData[triplet.vn - 1];
							}

							if (triplet.vt != 0)
							{
								currentVertex.uvcoord = UVData[triplet.vt - 1];
							}

							currentMesh->m_vertices.push_back(currentVertex);
						}

						bool calcNormals = normalData.empty();
						for (unsigned int offset = 1; offset < (faceData.size() - 1); ++offset)
						{
							currentMesh->m_indices.push_back(ci);
							currentMesh->m_indices.push_back(ci + offset);
							currentMesh->m_indices.push_back(ci + 1 + offset);

							if (calcNormals)
							{
								glm::vec4 normal = currentMesh->CalculateFaceNormal(ci, ci + offset, ci + offset + 1);

								currentMesh->m_vertices[ci].normal = normal;
								currentMesh->m_vertices[ci + offset].normal = normal;
								currentMesh->m_vertices[ci + offset + 1].normal = normal;
							}
						}

						continue;
					}

					if (dataType == "usemtl")
					{
						OBJMaterial* mtl = GetMaterialByName(data.c_str());

						if (mtl != nullptr)
						{
							currentMTL = mtl;

							if (currentMesh != nullptr) { currentMesh->m_material = currentMTL; }

							continue;
						}
					}
				}
			}
		}

		std::cout << std::endl;
		
		if (currentMesh != nullptr) 
		{ 
			std::cout << "Current Mesh added to Mesh Vector " << std::endl;
			m_meshes.push_back(currentMesh); 
		}

		file.close();
		return true;
	}
	return false;
}

//Split Vector String
glm::vec4 OBJModel::ProcessVectorString(const std::string a_data)
{
	std::stringstream iss(a_data);
	glm::vec4 vecData = glm::vec4(0.0f);
	int i = 0;

	for (std::string val; iss >> val; ++i)
	{
		float fVal = std::stof(val);
		vecData[i] = fVal;
	}

	return vecData;
}

//Split String at Character Level
std::vector<std::string> OBJModel::SplitStringAtCharacter(std::string data, char a_character)
{
	std::vector<std::string> lineData;
	std::stringstream iss(data);
	std::string lineSegment;

	while (std::getline(iss, lineSegment, a_character))
	{
		lineData.push_back(lineSegment);
	}

	return lineData;
}

//Process Vertext Triplet
OBJModel::OBJ_Face_Triplet OBJModel::ProcessTriplet(std::string a_triplet)
{
	std::vector<std::string> vertexIndices = SplitStringAtCharacter(a_triplet, '\/');
	
	OBJ_Face_Triplet ft;
	ft.v = 0, ft.vn = 0, ft.vt = 0;
	ft.v = std::stoi(vertexIndices[0]);

	if (vertexIndices.size() >= 2)
	{
		if (vertexIndices[1].size() > 0)
		{
			ft.vt = std::stoi(vertexIndices[1]);
		}

		if (vertexIndices.size() >= 3)
		{
			ft.vn = std::stoi(vertexIndices[2]);
		}
	}

	return ft;
}

//Get Line Type
std::string OBJModel::LineType(const std::string& a_in)
{
	if (!a_in.empty())
	{
		size_t token_start = a_in.find_first_not_of(" \t");
		size_t token_end = a_in.find_first_of(" \t", token_start);

		if (token_start != std::string::npos && token_end != std::string::npos)
		{
			return a_in.substr(token_start, token_end - token_start);
		}
		else if (token_start != std::string::npos)
		{
			return a_in.substr(token_start);
		}
	}

	return "";
}

//Get Line Data
std::string OBJModel::LineData(const std::string& a_in)
{
	if (!a_in.empty())
	{
		size_t token_start = a_in.find_first_not_of(" \t");
		size_t token_end = a_in.find_first_of(" \t", token_start);

		size_t data_start = a_in.find_first_not_of(" \t", token_end);
		size_t data_end = a_in.find_last_not_of(" \t\n\r");

		if (data_start != std::string::npos && data_end != std::string::npos)
		{
			return a_in.substr(data_start, data_end - data_start + 1);
		}
		else if (data_start != std::string::npos)
		{
			return a_in.substr(data_start);
		}
	}

	return "";
}

//Get Mesh by Index
OBJMesh* OBJModel::GetMeshByIndex(unsigned int a_index)
{
	unsigned int meshCount = m_meshes.size();

	if (meshCount > 0 && a_index < meshCount) { return m_meshes[a_index]; }

	return nullptr;
}

OBJMaterial* OBJModel::GetMaterialByName(const char* a_name)
{
	for (auto iter = m_materials.begin(); iter != m_materials.end(); ++iter)
	{
		OBJMaterial* mat = (*iter);

		if (mat->name == a_name) { return mat; }
	}

	return nullptr;
}

OBJMaterial* OBJModel::GetMaterialByIndex(unsigned int a_index)
{
	unsigned int materialCount = m_materials.size();

	if (materialCount > 0 && a_index < materialCount) { return m_materials[a_index]; }

	return nullptr;
}

void OBJModel::LoadMaterialLibrary(std::string a_mtllib)
{
	std::string matFile = m_path + a_mtllib;
	
	std::cout << "Loading Material File: " << matFile << std::endl;

	std::fstream file;
	file.open(matFile, std::ios_base::in | std::ios_base::binary);

	if (file.is_open())
	{
		std::cout << "Material File Opened...Loading Content..." << std::endl;

		file.ignore(std::numeric_limits<std::streamsize>::max());
		std::streamsize fileSize = file.gcount();
		file.clear();
		file.seekg(0, std::ios_base::beg);

		if (fileSize == 0)
		{
			std::cout << "Material File contains no data, closing...";
			file.close();
		}

		std::cout << "Material File Size: " << fileSize / 1024 << " KB" << std::endl;

		std::string fileLine;
		OBJMaterial* currentMaterial = nullptr;

		while (!file.eof())
		{
			if (std::getline(file, fileLine))
			{
				if (fileLine.size() > 0)
				{
					std::string dataType = LineType(fileLine);
					if (dataType.length() == 0) { continue; }
					std::string data = LineData(fileLine);

					if (dataType == "#")
					{
						std::cout << "Comment(" << data << ")" << std::endl;
						
						continue;
					}

					if (dataType == "newmtl")
					{
						std::cout << "New Material Found: " << data << std::endl;

						if (currentMaterial != nullptr)
						{
							m_materials.push_back(currentMaterial);
						}

						currentMaterial = new OBJMaterial();
						currentMaterial->name = data;
						
						continue;
					}

					if (dataType == "Ns")
					{
						if (currentMaterial != nullptr)
						{
							currentMaterial->kS.a = std::stof(data);
						}

						continue;
					}

					if (dataType == "Ka")
					{
						if (currentMaterial != nullptr)
						{
							float kAd = currentMaterial->kA.a;
							currentMaterial->kA = ProcessVectorString(data);
							currentMaterial->kA.a = kAd;
						}

						continue;
					}

					if (dataType == "Kd")
					{
						if (currentMaterial != nullptr)
						{
							float kDa = currentMaterial->kD.a;
							currentMaterial->kD = ProcessVectorString(data);
							currentMaterial->kD.a = kDa;
						}

						continue;
					}

					if (dataType == "Ks")
					{
						if (currentMaterial != nullptr)
						{
							float kSa = currentMaterial->kS.a;
							currentMaterial->kS = ProcessVectorString(data);
							currentMaterial->kS.a = kSa;
						}
					}

					if (dataType == "Ke")
					{
						continue;
					}

					if (dataType == "Ni")
					{
						if (currentMaterial != nullptr)
						{
							currentMaterial->kA.a = std::stof(data);
						}

						continue;
					}

					if (dataType == "d" || dataType == "Tr")
					{
						if (currentMaterial != nullptr)
						{
							currentMaterial->kD.a = std::stof(data);

							if (dataType == "Tr")
							{
								currentMaterial->kD.a = 1.0f - currentMaterial->kD.a;
							}

							continue;
						}
					}

					if (dataType == "illum")
					{
						continue;
					}


					if (dataType == "map_Kd")
					{
						std::vector<std::string> mapData = SplitStringAtCharacter(data, ' ');
						currentMaterial->textureFileNames[OBJMaterial::TextureTypes::DiffuseTexture] = m_path + mapData[mapData.size() - 1];

						continue;
					}
					
					if (dataType == "map_Ks")
					{
						std::vector<std::string> mapData = SplitStringAtCharacter(data, ' ');
						currentMaterial->textureFileNames[OBJMaterial::TextureTypes::SpecularTexture] = m_path + mapData[mapData.size() - 1];

						continue;
					}
					
					if (dataType == "map_bump" || dataType == "bump")
					{
						std::vector<std::string> mapData = SplitStringAtCharacter(data, ' ');
						currentMaterial->textureFileNames[OBJMaterial::TextureTypes::NormalTexture] = m_path + mapData[mapData.size() - 1];

						continue;
					}
				}
			}
		}

		if (currentMaterial != nullptr)
		{
			m_materials.push_back(currentMaterial);
		}

		file.close();
	}
}