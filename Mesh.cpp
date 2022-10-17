#include "Mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{

	GLenum err = glewInit();
	m_drawCount = numVertices;


	//takes in number of vertex array objects and the array object
	glGenVertexArrays(1, &m_vertexArrayObject);
	
	glBindVertexArray(m_vertexArrayObject);
	
	
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	
	
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);
	
	
	
	//converting our mixed lists into two lists of just tex Coords and positions separate
	for(unsigned int i =0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
		
	}
	
	
	
	
	//Allows blocks of data in GPU for arrays
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	
	//Informs how to interpret buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	
	//Put all vertex data into the array in the GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]),&positions[0] , GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	//Tells OpenGL how to read attributes as an array
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0,0);
	
	
	//Unbinds
	
	
	
	
	
	
	
	//Informs how to interpret buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	
	//Put all vertex data into the array in the GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]),&texCoords[0] , GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(1);
	//Tells OpenGL how to read attributes as an array
	glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 0,0);
	
	
	//Unbinds
	glBindVertexArray(0);
	
	

}


Mesh::~Mesh()
{
	//Deletes the created Vertex Array
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}



//Draws our Mesh
void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);
	
	//GLenum mode can be changed (will need to be changed later for painting
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
	
	
	
	
	//Unbinds
	glBindVertexArray(0);
}
