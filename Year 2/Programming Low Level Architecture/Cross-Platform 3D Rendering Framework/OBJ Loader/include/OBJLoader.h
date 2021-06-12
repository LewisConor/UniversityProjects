#pragma once

//Includes
#include <glm/glm.hpp>
#include <vector>
#include <string>

//OBJ Vertex
class OBJVertex
{
public:
	enum VertexAttributeFlags
	{
		POSITION = (1 << 0),
		NORMAL = (1 << 1),
		UVCOORD = (1 << 2),
	};

	enum Offsets
	{
		PositionOffset = 0,
		NormalOffset = PositionOffset + sizeof(glm::vec4),
		UVCoordOffset = NormalOffset + sizeof(glm::vec4),
	};

	OBJVertex();
	~OBJVertex();

	glm::vec4 position;
	glm::vec4 normal;
	glm::vec2 uvcoord;

	bool operator == (const OBJVertex& a_rhs) const;
	bool operator < (const OBJVertex& a_rhs) const;
};

inline OBJVertex::OBJVertex() : position(0, 0, 0, 1), normal(0, 0, 0, 0), uvcoord(0, 0) {}
inline OBJVertex::~OBJVertex() {}

inline bool OBJVertex::operator == (const OBJVertex& a_rhs) const { return memcmp(this, &a_rhs, sizeof(OBJVertex)) == 0; }
inline bool OBJVertex::operator < (const OBJVertex& a_rhs) const { return memcmp(this, &a_rhs, sizeof(OBJVertex)) < 0; }

//OBJ Material
class OBJMaterial
{
public:
	OBJMaterial() : name(), kA(0.0f), kD(0.0f), kS(0.0f), textureFileNames(), textureIDs() {};
	~OBJMaterial() {};

	std::string name;
	glm::vec4 kA;
	glm::vec4 kD;
	glm::vec4 kS;

	enum TextureTypes
	{
		DiffuseTexture = 0,
		SpecularTexture,
		NormalTexture,

		TextureTypes_Count
	};

	std::string textureFileNames[TextureTypes_Count];
	unsigned int textureIDs[TextureTypes_Count];
};

//OBJ Mesh
class OBJMesh
{
public:
	OBJMesh();
	~OBJMesh();

	glm::vec4 CalculateFaceNormal(const unsigned int& a_indexA, const unsigned int& a_indexB, const unsigned int& a_indexC) const;
	void CalculateFaceNormals();

	OBJMaterial* m_material;
	std::string m_name;
	std::vector<OBJVertex> m_vertices;
	std::vector<unsigned int> m_indices;
};

inline OBJMesh::OBJMesh() {}
inline OBJMesh::~OBJMesh() {}

//OBJ Model
class OBJModel
{
public:
	OBJModel() : m_meshes(), m_path(), m_worldMatrix(glm::mat4(1.0f)) {}
	~OBJModel();

	bool Load(const char* a_filename, float a_scale = 1.0f);

	const char* GetPath() const { return m_path.c_str(); }
	unsigned int GetMeshCount() const{ return m_meshes.size(); }
	const glm::mat4& GetWorldMatrix() const { return m_worldMatrix; }
	OBJMesh* GetMeshByName(const char* a_name);
	OBJMesh* GetMeshByIndex(unsigned int a_index);
	OBJMaterial* GetMaterialByName(const char* a_name);
	OBJMaterial* GetMaterialByIndex(unsigned int a_index);
	unsigned int GetMaterialCount() const { return m_materials.size(); }

private:
	std::string LineType(const std::string& a_in);
	std::string LineData(const std::string& a_in);
	glm::vec4 ProcessVectorString(const std::string a_data);
	std::vector<std::string> SplitStringAtCharacter(std::string data, char a_character);
	void LoadMaterialLibrary(std::string a_mtllib);

	typedef struct OBJ_Face_Triplet
	{
		unsigned int v;
		unsigned int vt;
		unsigned int vn;
	}OBJ_Face_Triplet;

	OBJ_Face_Triplet ProcessTriplet(std::string a_triplet);

	std::vector<OBJMesh*> m_meshes;
	std::vector<OBJMaterial*> m_materials;
	std::string m_path;
	glm::mat4 m_worldMatrix;
};