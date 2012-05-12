////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


/////////////
// GLOBALS //
/////////////
const int TEXTURE_REPEAT = 8;


//////////////
// INCLUDES //
//////////////
#include <fstream>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
		D3DXVECTOR4 color;
	};

	struct HeightMapType 
	{ 
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float r, g, b;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

public:
	TerrainClass();
	TerrainClass(const TerrainClass&);
	~TerrainClass();

	bool Initialize(ID3D10Device*, char*, WCHAR*, char*);
	void Shutdown();

	int GetVertexCount();
	ID3D10ShaderResourceView* GetTexture();

	void CopyVertexArray(void*);

private:
	bool LoadHeightMap(char*);
	void NormalizeHeightMap();
	bool CalculateNormals();
	void ShutdownHeightMap();

	void CalculateTextureCoordinates();
	bool LoadTexture(ID3D10Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadColorMap(char*);

	bool InitializeBuffers();
	void ShutdownBuffers();

private:
	VertexType* m_vertices;
	int m_vertexCount;
	int m_terrainWidth, m_terrainHeight;
	HeightMapType* m_heightMap;
	TextureClass* m_Texture;
};

#endif