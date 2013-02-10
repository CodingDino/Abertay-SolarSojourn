// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Model
//      Contains model data.


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
//#include "Texture.h"
#include "Util.h"
using namespace std;


// |----------------------------------------------------------------------------|
// |                              Class: Model                                  |
// |----------------------------------------------------------------------------|
class Model
{
private:

    //|-----------------------------Private Data Types--------------------------|

    // Holds a single vertex position, texture, and normal
    struct VertexType
    {
        D3DXVECTOR3 position;
        D3DXVECTOR2 texture;
        D3DXVECTOR3 normal;
    };

    // Holds vertex information, to be passed to shaders
    struct ModelType
    {
        float x, y, z;
        float tu, tv;
        float nx, ny, nz;
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Model();

    // Initialize the model, reads in a vertex and texture file
    bool Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename);

    // Releases data associated with the model
    void Shutdown();

    // Renders the model to the supplied context
    void Render(ID3D11DeviceContext* deviceContext);

    // Getter functions
    int GetIndexCount();

private:

    //|-------------------------------Private Functions-------------------------|

    // Sets up the buffers associated with this model
    bool InitializeBuffers(ID3D11Device* device);

    // Releases buffers associated with this model
    void ShutdownBuffers();

    // Renders the buffers
    void RenderBuffers(ID3D11DeviceContext* deviceContext);

    // Loads the given model from file
    bool LoadModel(char*);

    // Releases the model data
    void ReleaseModel();

private:

    //|-----------------------------Private Data Members------------------------|

    // Buffers
    ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;

    // Number of vertices and indices
    int m_vertexCount, m_indexCount;

    // Model
    ModelType* m_model;
};