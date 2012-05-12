////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "textclass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
#include "lightclass.h"
#include "lightshaderclass.h"
#include "quadtreeclass.h"
#include "frustumclass.h"
#include "modelclass.h"
#include "modellistclass.h"
#include "multitextureshaderclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);

	bool SetCameraPosition(float, float, float, float, float, float);

private:
	bool Render();

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	TextClass* m_Text;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	LightClass* m_Light;
	LightClass* m_Light_2;
	LightShaderClass* m_LightShader;
	QuadTreeClass* m_QuadTree;
	FrustumClass* m_Frustum;
	ModelClass* m_Model;
	ModelListClass* m_ModelList;
	ModelClass* m_Model_2;
	MultiTextureShaderClass* m_MultiTextureShader;

};

#endif
