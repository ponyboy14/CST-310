#include "Mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{

	m_drawCount = numVertices;


	//takes in number of vertex array objects and the array object
	glGenVertexArrays(1, &m_vertexArrayObject);
	
	glBindVertexArray(m_vertexArrayObject);
	
	//Allows blocks of data in GPU for arrays
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	
	//Informs how to interpret buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	
	//Put all vertex data into the array in the GPU
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	//Tells OpenGL how to read attributes as an array
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0,0);
	
	
	
	
	
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
