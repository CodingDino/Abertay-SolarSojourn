// Solar Sojourn
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// D3DManager
//      Controls main DirectX objects and handles backbuffer and display device
#pragma once


// |----------------------------------------------------------------------------|
// |                                 Linking                                    |
// |----------------------------------------------------------------------------|
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include "Util.h"
#include "Singleton.h"


// |----------------------------------------------------------------------------|
// |                            Class: D3DManager                               |
// |----------------------------------------------------------------------------|
class D3DManager : public Singleton<D3DManager>
{
public:

    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	D3DManager();
	D3DManager(const D3DManager&);
	~D3DManager();
    
    // Initialization and shutdown
    bool Initialize(int screenWidth, int screenHeight, bool vsync, bool fullscreen, 
                    float screenDepth, float screenNear);
    void Shutdown();
    
    // clears the buffers in preparation for scene rendering
    void BeginScene(float, float, float, float);

    // flips the back buffer to the screen when rendering is complete
    void EndScene();

    // Get functions
    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();
    void GetProjectionMatrix(D3DXMATRIX&);
    void GetWorldMatrix(D3DXMATRIX&);
    void GetOrthoMatrix(D3DXMATRIX&);
    void GetVideoCardInfo(char*, int&);

    // Z Bufffer modification
    void TurnZBufferOn();
    void TurnZBufferOff();

    // Blending modification
    void TurnOnAlphaBlending();
    void TurnOnParticleBlending();
    void TurnOffAlphaBlending();

    // Culling modification
    void TurnOnBackCulling();
    void TurnOffBackCulling();

    // Render to Texture utility
    ID3D11DepthStencilView* GetDepthStencilView();
    void SetAsRenderTarget();
    void ResetViewport();
    
private:

    //|-------------------------------Private Functions-------------------------|

private:

    //|-----------------------------Private Data Members------------------------|

    // Vsync setting
    bool m_vsync_enabled;

    // Video card information
    int m_videoCardMemory;
    char m_videoCardDescription[128];

    // DirectX objects
    IDXGISwapChain* m_swapChain;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    ID3D11RenderTargetView* m_renderTargetView;
    ID3D11Texture2D* m_depthStencilBuffer;
    ID3D11DepthStencilState* m_depthStencilState;
    ID3D11DepthStencilView* m_depthStencilView;
    ID3D11RasterizerState* m_rasterState;
    ID3D11RasterizerState* m_cullingDisabledRasterState;
    ID3D11DepthStencilState* m_depthDisabledStencilState;
    ID3D11BlendState* m_alphaEnableBlendingState;
    ID3D11BlendState* m_particleAlphaEnableBlendingState;
    ID3D11BlendState* m_alphaDisableBlendingState;
	D3D11_VIEWPORT m_viewport;

    // Matrices
    D3DXMATRIX m_projectionMatrix;
    D3DXMATRIX m_worldMatrix;
    D3DXMATRIX m_orthoMatrix;
};