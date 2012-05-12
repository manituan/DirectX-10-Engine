////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Text = 0;
	m_Terrain = 0;
	m_TerrainShader = 0;
	m_Light = 0;
	m_Light_2=0;
	m_LightShader = 0;
	m_QuadTree = 0;
	m_Frustum = 0;
	m_Model=0;
	m_Model_2=0;
	m_ModelList=0;
	//m_MultiTextureShader=0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;
	char videoCard[128];
	int videoMemory;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Retrieve the video card information.
	m_D3D->GetVideoCardInfo(videoCard, videoMemory);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Set the video card information in the text object.
	result = m_Text->SetVideoCardInfo(videoCard, videoMemory);
	if(!result)
	{
		MessageBox(hwnd, L"Could not set video card info in the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	m_Model_2 = new ModelClass;
	if(!m_Model_2)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), L"../Manituan/data/Cuerpo.tif", "../Manituan/data/body.txt");
	//Prueba de multitextura
	//result = m_Model->Initialize(m_D3D->GetDevice(), "../Manituan/data/body.txt", L"../Manituan/data/stone01.dds",L"../Manituan/data/dirt01.dds");
	
	result = m_Model_2->Initialize(m_D3D->GetDevice(), L"../Manituan/data/Casco.tif", "../Manituan/data/head.txt");
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model list object.
	m_ModelList = new ModelListClass;
	if(!m_ModelList)
	{
		return false;
	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(196);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Manituan/data/heightmap01.bmp", L"../Manituan/data/dirt01.dds", 
								   "../Manituan/data/colorm01.bmp");
	/*result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Manituan/data/heightmap01.bmp", L"../Manituan/data/stone01.dds", 
				     "../Manituan/data/dirt01.dds");*/

	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	//m_MultiTextureShader = new MultiTextureShaderClass;
	//if(!m_MultiTextureShader)
	//{
	//	return false;
	//}

	//// Initialize the multitexture shader object.
	//result = m_MultiTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);
	m_Light->SetDirection(1.0f, 1.0f, 1.0f);

	// Create the light object.
	m_Light_2 = new LightClass;

	m_Light_2->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light_2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light_2->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light_2->SetSpecularPower(32.0f);
	m_Light_2->SetDirection(1.0f,0.0f, 1.0f);

	if(!m_Light_2)
	{
		return false;
	}

	// Create the quad tree object.
	m_QuadTree = new QuadTreeClass;
	if(!m_QuadTree)
	{
		return false;
	}

	// Initialize the quad tree object.
	result = m_QuadTree->Initialize(m_Terrain, m_D3D->GetDevice());
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the quad tree object.", L"Error", MB_OK);
		return false;
	}

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if(!m_Frustum)
	{
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the frustum object.
	if(m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the model list object.
	if(m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the quad tree object.
	if(m_QuadTree)
	{
		m_QuadTree->Shutdown();
		delete m_QuadTree;
		m_QuadTree = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if(m_Light_2)
	{
		delete m_Light_2;
		m_Light_2 = 0;
	}

	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the multitexture shader object.
	/*if(m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}*/

	// Release the terrain object.
	if(m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the Direct3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;


	// Set the frames per second.
	result = m_Text->SetFps(fps);
	if(!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu);
	if(!result)
	{
		return false;
	}

	// Render the graphics for the frame.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::SetCameraPosition(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	bool result;


	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Set the camera position and rotation in the text class.
	result = m_Text->SetCameraPosition(posX, posY, posZ, rotX, rotY, rotZ);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	int modelCount, renderCount, index;
	bool renderModel, result;
	float positionX, positionY, positionZ, radius;
	D3DXVECTOR4 color;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();

	// Initialize the count of models that have been rendered.
	renderCount = 0;

	//Cada vertex Buffer le hago una transformación en el mundo y lo meto en el VB´ con todos, el cual solo tengo que renderizar una vez.

	// Go through all the models and render them only if they can be seen by the camera view.
	for(index=0; index<modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.
		m_ModelList->GetData(index, positionX, positionY, positionZ, color);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 1.0f;

		// Check if the sphere model is in the view frustum.
		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);

		// If it can be seen then render it, if not skip this model and check the next sphere.
		if(renderModel)
		{
			// Move the model to the location it should be rendered at.
			D3DXMatrixTranslation(&worldMatrix, positionX, positionY, positionZ); 

			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_Model->Render(m_D3D->GetDevice());

			//Esta linea peta
			/*m_MultiTextureShader->Render(m_D3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				     m_Model->GetTextureArray());*/

			// Render the model using the light shader.
			m_LightShader->Render(m_D3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
						  m_Model->GetTexture(), m_Camera->GetPosition(), m_Light->GetDirection(), m_Light->GetAmbientColor(), 
						  m_Light->GetDiffuseColor(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_Model_2->Render(m_D3D->GetDevice());

			// Render the model using the light shader.
			m_LightShader->Render(m_D3D->GetDevice(), m_Model_2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
						  m_Model_2->GetTexture(), m_Camera->GetPosition(), m_Light->GetDirection(), m_Light->GetAmbientColor(), 
						  m_Light->GetDiffuseColor(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			
			m_LightShader->Render(m_D3D->GetDevice(), m_Model_2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
						  m_Model_2->GetTexture(), m_Camera->GetPosition(), m_Light_2->GetDirection(), m_Light_2->GetAmbientColor(), 
						  m_Light_2->GetDiffuseColor(), m_Light_2->GetSpecularColor(), m_Light_2->GetSpecularPower());

			// Reset to the original world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);

			// Since this model was rendered then increase the count for this frame.
			renderCount++;
		}
	}

	// Set the terrain shader parameters that it will use for rendering.
	m_TerrainShader->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, m_Terrain->GetTexture(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection());

	

	// Render the terrain using the quad tree and terrain shader.
	m_QuadTree->Render(m_Frustum, m_D3D->GetDevice(), m_TerrainShader);

	//Es un metodo de text que pinta la leyenda, no va.
	result=m_Text->SetLeyenda();

	result = m_Text->SetRenderCount(m_QuadTree->GetDrawCount());
	if(!result)
	{
		return false;
	}

	// Turn off the Z buffer and turn alpha blending on to begin rendering 2D text.
	m_D3D->TurnZBufferOff();
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	m_Text->Render(m_D3D->GetDevice(), worldMatrix, orthoMatrix);

	// Turn the Z buffer back on and alpha blending off now that all 2D text rendering has completed.
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}