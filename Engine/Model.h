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
        D3DXVECTOR3 position;   // Vertex position in 3d space
        D3DXVECTOR2 texture;    // Texture coordinate for 2D texture
        D3DXVECTOR3 normal;     // Normal vector for this vertex
    };

    // Holds vertex information, to be passed to shaders
    struct ModelType
    {
        float x, y, z;          // Vertex position in 3d space
        float tu, tv;           // Texture coordinate for 2D texture
        float nx, ny, nz;       // Normal vector for this vertex
    };

public:

    //|-------------------------------Public Functions--------------------------|
    
    // Constructors and Destructors
    Model();

    // Initialize the model, reads in a vertex and texture file
    bool Initialize(ID3D11Device* device, char* modelFilename);

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