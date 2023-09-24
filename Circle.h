#pragma once
class Shader;

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "gl\glew.h"

class Circle
{
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[3];	// ids for Vertex Buffer Objects

	Shader* m_Shader;  ///shader object 

	float m_Radius;
	int m_NumOfVerts;

	GLuint m_TexName; //identifier for the texture

public:
	Circle();					//default constructor
	void Init(float colour[3], GLubyte* textureValues, int textureWidth, int textureHeight);
	void SetRadius(float radius);
	void Render(glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
};