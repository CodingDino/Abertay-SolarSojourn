// Solar Exploration Sim
// Developed a coursework for Abertay University
// Based on tutorials from http://www.rastertek.com
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Mesh
//      Contains model information for a mesh


// |----------------------------------------------------------------------------|
// |								Includes									|
// |----------------------------------------------------------------------------|
#include "Mesh.h"


// |----------------------------------------------------------------------------|
// |						   Default Constructor								|
// |----------------------------------------------------------------------------|
Mesh::Mesh() : 
    m_meshWidth(0),
    m_meshLength(0),
    m_meshHeight(0),
    m_heightMap(0),
    m_textureRepeat(0),
    Model()
{
}

// |----------------------------------------------------------------------------|
// |						    Copy Constructor								|
// |----------------------------------------------------------------------------|
Mesh::Mesh(const Mesh& other)
{
}


// |----------------------------------------------------------------------------|
// |						     Deconstructor									|
// |----------------------------------------------------------------------------|
Mesh::~Mesh()
{
}


// |----------------------------------------------------------------------------|
// |						      Initialize									|
// |----------------------------------------------------------------------------|
bool Mesh::Initialize()
{
	DebugLog ("Mesh::Initialize() called.", DB_GRAPHICS, 1);
	bool result;

    // Set texture repeat if not provided
    if(!m_textureRepeat) m_textureRepeat = ((m_meshWidth+m_meshLength)/2)/4;

    // Generate a Height Map
    GenerateHeightMap();

    // Calculate the normals for the terrain data.
	result = CalculateNormals();
	if(!result)
	{
		return false;
	}

    // Calculate the texture coordinates.
	CalculateTextureCoordinates();

	// Set the number of vertices and indices.
	m_vertexCount = (m_meshWidth - 1) * (m_meshLength - 1) * 6;
	m_indexCount = m_vertexCount;

	// Set buffer flags
	m_bufferUsage = D3D11_USAGE_DEFAULT;
	m_bufferCPUAccess = 0;
	
	// Initialize the vertex and index buffers.
	result = InitializeBuffers();
	if(!result)
	{
		return false;
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						      Shutdown		    							|
// |----------------------------------------------------------------------------|
void Mesh::Shutdown()
{
	DebugLog ("Mesh::Shutdown() called.", DB_GRAPHICS, 1);

	// Release the height map data.
	ShutdownHeightMap();

    // Parent class shutdown
    Model::Shutdown();

	return;
}


// |----------------------------------------------------------------------------|
// |						  PopulateBuffers									|
// |----------------------------------------------------------------------------|
bool Mesh::PopulateBuffers(VertexType*& vertices, unsigned long*& indices)
{
	DebugLog ("Mesh::PopulateBuffers() called.", DB_GRAPHICS, 10);
    
    // Define Variables
	float positionX, positionZ;
	int index, i, j;
    float startX, startZ;
	int index1, index2, index3, index4;
	float tu, tv;

    // Initialize the index to the vertex array.
	index = 0;

    // Initialize starting position
    startX = 0.0f - m_meshWidth/2;
    startZ = 0.0f - m_meshLength/2;

	// Load the vertex and index arrays with the terrain data.
	for(j=0; j<(m_meshLength-1); j++)
	{
		for(i=0; i<(m_meshWidth-1); i++)
		{
            index1 = (m_meshWidth * j) + i;          // Bottom left.
			index2 = (m_meshWidth * j) + (i+1);      // Bottom right.
			index3 = (m_meshWidth * (j+1)) + i;      // Upper left.
			index4 = (m_meshWidth * (j+1)) + (i+1);  // Upper right.

			// Upper left.
			tv = m_heightMap[index3].tv;

			// Modify the texture coordinates to cover the top edge.
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index3].x, m_heightMap[index3].y, m_heightMap[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_heightMap[index3].tu, tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index3].nx, m_heightMap[index3].ny, m_heightMap[index3].nz);
			indices[index] = index;
			index++;

			// Upper right.
			tu = m_heightMap[index4].tu;
			tv = m_heightMap[index4].tv;

			// Modify the texture coordinates to cover the top and right edge.
			if(tu == 0.0f) { tu = 1.0f; }
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(tu, tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR2(m_heightMap[index1].tu, m_heightMap[index1].tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			indices[index] = index;
			index++;

			// Bottom left.
			vertices[index].position = D3DXVECTOR3(m_heightMap[index1].x, m_heightMap[index1].y, m_heightMap[index1].z);
			vertices[index].texture = D3DXVECTOR2(m_heightMap[index1].tu, m_heightMap[index1].tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index1].nx, m_heightMap[index1].ny, m_heightMap[index1].nz);
			indices[index] = index;
			index++;

			// Upper right.
			tu = m_heightMap[index4].tu;
			tv = m_heightMap[index4].tv;

			// Modify the texture coordinates to cover the top and right edge.
			if(tu == 0.0f) { tu = 1.0f; }
			if(tv == 1.0f) { tv = 0.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index4].x, m_heightMap[index4].y, m_heightMap[index4].z);
			vertices[index].texture = D3DXVECTOR2(tu, tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index4].nx, m_heightMap[index4].ny, m_heightMap[index4].nz);
			indices[index] = index;
			index++;

			// Bottom right.
			tu = m_heightMap[index2].tu;

			// Modify the texture coordinates to cover the right edge.
			if(tu == 0.0f) { tu = 1.0f; }

			vertices[index].position = D3DXVECTOR3(m_heightMap[index2].x, m_heightMap[index2].y, m_heightMap[index2].z);
			vertices[index].texture = D3DXVECTOR2(tu, m_heightMap[index2].tv);
			vertices[index].normal = D3DXVECTOR3(m_heightMap[index2].nx, m_heightMap[index2].ny, m_heightMap[index2].nz);
			indices[index] = index;
			index++;

		}
	}

	return true;
}


// |----------------------------------------------------------------------------|
// |						   RenderBuffers									|
// |----------------------------------------------------------------------------|
void Mesh::RenderBuffers()
{
	DebugLog ("Mesh::RenderBuffers() called.", DB_GRAPHICS, 10);

	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	D3DManager::GetRef()->GetDeviceContext()
		->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


// |----------------------------------------------------------------------------|
// |						  GenerateHeightMap									|
// |----------------------------------------------------------------------------|
void Mesh::GenerateHeightMap()
{
    if (!m_meshWidth || !m_meshLength)
        return;

    InitializeHeightMap();
    PerlinNoiseHeightMap();
    //SmoothHeightMap(6);
    //NormalizeHeightMap();
}


// |----------------------------------------------------------------------------|
// |						 InitializeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::InitializeHeightMap()
{
	int i, j, index;
    // Initialize starting position
    float startX = 0.0f - m_meshWidth/2;
    float startZ = 0.0f - m_meshLength/2;

    m_heightMap = new HeightMapType[m_meshWidth*m_meshLength];
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			index = (m_meshWidth * j) + i;

			m_heightMap[index].x = startX+(float)i;
			m_heightMap[index].y = (float)0;
			m_heightMap[index].z = startZ+(float)j;

			m_heightMap[index].nx = (float)0;
			m_heightMap[index].ny = (float)1;
			m_heightMap[index].nz = (float)0;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						  RandomizeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::RandomizeHeightMap()
{
	int i, j, index;

    // Initialize randomizer
    srand (time(0));
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			index = (m_meshWidth * j) + i;

			m_heightMap[index].y = (((float)rand()-(float)rand())/RAND_MAX) * m_meshHeight;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						  PerlinNoiseHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::PerlinNoiseHeightMap()
{
	int i, j, index;

    // Initialize perlin noise generator
    PerlinNoise noise(0.1,5,10,8,0);
    noise::module::Perlin libnoisePerlin;

	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			index = (m_meshLength * j) + i;

			//m_heightMap[index].y = noise.GetHeight(i,j);
			m_heightMap[index].y = exp(2*libnoisePerlin.GetValue (m_heightMap[index].x/70,m_heightMap[index].z/70,0.5));
		}
	}
}


// |----------------------------------------------------------------------------|
// |						  RandomizeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::SmoothHeightMap(int smoothFactor)
{
	int i, j, total(0);
    float sum = 0.0f;

    // Initialize randomizer
    srand (time(0));
    
    for(int s=0; s<smoothFactor; ++s)
    {
        // Read the image data into the height map.
        for(j=0; j<m_meshLength; j++)
        {
	        for(i=0; i<m_meshWidth; i++)
	        {
                // Sum all nearby heights

                if (j != 0 && i != 0) 
                {
                    sum += m_heightMap[(m_meshWidth * (j-1)) + (i-1)].y; 
                    ++total;
                }
                if (i != 0)
                {
                    sum += m_heightMap[(m_meshWidth * (j)) + (i-1)].y; 
                    ++total;
                }
                if (j != m_meshLength-1 && i != 0) 
                {
                    sum += m_heightMap[(m_meshWidth * (j+1)) + (i-1)].y; 
                    ++total;
                }
                if (j != 0) 
                {
                    sum += m_heightMap[(m_meshWidth * (j-1)) + (i)].y; 
                    ++total;
                }

                sum += m_heightMap[(m_meshWidth * (j)) + (i)].y; 
                ++total;

                if (j != m_meshLength-1) 
                {
                    sum += m_heightMap[(m_meshWidth * (j+1)) + (i)].y; 
                    ++total;
                }

                if (j != 0 && i != m_meshWidth-1) 
                {
                    sum += m_heightMap[(m_meshWidth * (j-1)) + (i+1)].y; 
                    ++total;
                }

                if (i != m_meshWidth-1) 
                {
                    sum += m_heightMap[(m_meshWidth * (j)) + (i+1)].y; 
                    ++total;
                }

                if (j != m_meshLength-1 && i != m_meshWidth-1)
                {
                    sum += m_heightMap[(m_meshWidth * (j+1)) + (i+1)].y; 
                    ++total;
                }

                // Set this height to the average
		        m_heightMap[(m_meshWidth * (j)) + (i)].y = sum / total;

                // Reset sum
                sum = 0.0f;
                total = 0;
	        }
        }
    }
}


// |----------------------------------------------------------------------------|
// |						  NormalizeHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::NormalizeHeightMap()
{
	int i, j, index;
    
	// Read the image data into the height map.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			m_heightMap[(m_meshWidth * j) + i].y /= MAXINT;
		}
	}
}


// |----------------------------------------------------------------------------|
// |						   ShutdownHeightMap								|
// |----------------------------------------------------------------------------|
void Mesh::ShutdownHeightMap()
{
	if(m_heightMap)
	{
		delete [] m_heightMap;
		m_heightMap = 0;
	}

	return;
}


// |----------------------------------------------------------------------------|
// |						    CalculateNormals								|
// |----------------------------------------------------------------------------|
bool Mesh::CalculateNormals()
{
	int i, j, index1, index2, index3, index, count;
	float vertex1[3], vertex2[3], vertex3[3], vector1[3], vector2[3], sum[3], length;
	Coord* normals;


	// Create a temporary array to hold the un-normalized normal vectors.
	normals = new Coord[(m_meshLength-1) * (m_meshWidth-1)];
	if(!normals)
	{
		return false;
	}

	// Go through all the faces in the mesh and calculate their normals.
	for(j=0; j<(m_meshLength-1); j++)
	{
		for(i=0; i<(m_meshWidth-1); i++)
		{
			index1 = (j * m_meshWidth) + i;
			index2 = (j * m_meshWidth) + (i+1);
			index3 = ((j+1) * m_meshWidth) + i;

			// Get three vertices from the face.
			vertex1[0] = m_heightMap[index1].x;
			vertex1[1] = m_heightMap[index1].y;
			vertex1[2] = m_heightMap[index1].z;
		
			vertex2[0] = m_heightMap[index2].x;
			vertex2[1] = m_heightMap[index2].y;
			vertex2[2] = m_heightMap[index2].z;
		
			vertex3[0] = m_heightMap[index3].x;
			vertex3[1] = m_heightMap[index3].y;
			vertex3[2] = m_heightMap[index3].z;

			// Calculate the two vectors for this face.
			vector1[0] = vertex1[0] - vertex3[0];
			vector1[1] = vertex1[1] - vertex3[1];
			vector1[2] = vertex1[2] - vertex3[2];
			vector2[0] = vertex3[0] - vertex2[0];
			vector2[1] = vertex3[1] - vertex2[1];
			vector2[2] = vertex3[2] - vertex2[2];

			index = (j * (m_meshWidth-1)) + i;

			// Calculate the cross product of those two vectors to get the un-normalized value for this face normal.
			normals[index].x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
			normals[index].y = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
			normals[index].z = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
		}
	}

	// Now go through all the vertices and take an average of each face normal 	
	// that the vertex touches to get the averaged normal for that vertex.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			// Initialize the sum.
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			// Initialize the count.
			count = 0;

			// Bottom left face.
			if(((i-1) >= 0) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_meshWidth-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Bottom right face.
			if((i < (m_meshWidth-1)) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_meshWidth-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper left face.
			if(((i-1) >= 0) && (j < (m_meshLength-1)))
			{
				index = (j * (m_meshWidth-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper right face.
			if((i < (m_meshWidth-1)) && (j < (m_meshLength-1)))
			{
				index = (j * (m_meshWidth-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}
			
			// Take the average of the faces touching this vertex.
			sum[0] = (sum[0] / (float)count);
			sum[1] = (sum[1] / (float)count);
			sum[2] = (sum[2] / (float)count);

			// Calculate the length of this normal.
			length = sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));
			
			// Get an index to the vertex location in the height map array.
			index = (j * m_meshWidth) + i;

			// Normalize the final shared normal for this vertex and store it in the height map array.
			m_heightMap[index].nx = (sum[0] / length);
			m_heightMap[index].ny = (sum[1] / length);
			m_heightMap[index].nz = (sum[2] / length);
		}
	}

	// Release the temporary normals.
	delete [] normals;
	normals = 0;

	return true;
}


// |----------------------------------------------------------------------------|
// |				     CalculateTextureCoordinates							|
// |----------------------------------------------------------------------------|
void Mesh::CalculateTextureCoordinates()
{
	int incrementCount, i, j, tuCount, tvCount;
	float incrementValue, tuCoordinate, tvCoordinate;

	// Calculate how much to increment the texture coordinates by.
	incrementValue = (float)m_textureRepeat / (float)m_meshWidth;

	// Calculate how many times to repeat the texture.
	incrementCount = m_meshWidth / m_textureRepeat;

	// Initialize the tu and tv coordinate values.
	tuCoordinate = 0.0f;
	tvCoordinate = 1.0f;

	// Initialize the tu and tv coordinate indexes.
	tuCount = 0;
	tvCount = 0;

	// Loop through the entire height map and calculate the tu and tv texture coordinates for each vertex.
	for(j=0; j<m_meshLength; j++)
	{
		for(i=0; i<m_meshWidth; i++)
		{
			// Store the texture coordinate in the height map.
			m_heightMap[(m_meshWidth * j) + i].tu = tuCoordinate;
			m_heightMap[(m_meshWidth * j) + i].tv = tvCoordinate;

			// Increment the tu texture coordinate by the increment value and increment the index by one.
			tuCoordinate += incrementValue;
			tuCount++;

			// Check if at the far right end of the texture and if so then start at the beginning again.
			if(tuCount == incrementCount)
			{
				tuCoordinate = 0.0f;
				tuCount = 0;
			}
		}

		// Increment the tv texture coordinate by the increment value and increment the index by one.
		tvCoordinate -= incrementValue;
		tvCount++;

		// Check if at the top of the texture and if so then start at the bottom again.
		if(tvCount == incrementCount)
		{
			tvCoordinate = 1.0f;
			tvCount = 0;
		}
	}

	return;
}