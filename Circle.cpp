#include "Circle.h"
#include "shaders\Shader.h"

#include <iostream>

Circle::Circle()
{
	m_Shader = nullptr;
	m_vaoID = 0;
	m_vboID[0] = 0;
	m_vboID[1] = 0;
	m_Radius = 0.0f;
}

void Circle::SetRadius(float radius)
{
	m_Radius = radius;
}


void Circle::Init(float colour[3], GLubyte* textureValues, int textureWidth, int textureHeight)
{
	//Load the GLSL program 
	m_Shader = new Shader;
	if (!m_Shader->load("Basic", "./glslfiles/basicTexture.vert", "./glslfiles/basicTexture.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	//create the texture on the GPU
	glGenTextures(1, &m_TexName);
	glBindTexture(GL_TEXTURE_2D, m_TexName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  //or use GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureValues);

	//Create the geometry
	double step = 10;
	float size = (int)((360.0 / step) + 1) * 3;
	float* vert = new float[size * 3];
	float* col = new float[size * 3];
	float* tex = new float[(int)((size / 3.0) * 2.0 * 3.0)];

	m_NumOfVerts = 0;
	for (double i = 0; i < 360; i += step)
	{
		float xcoord = m_Radius * cos(glm::radians(i));
		float ycoord = m_Radius * sin(glm::radians(i));
		vert[m_NumOfVerts * 3] = xcoord;
		vert[m_NumOfVerts * 3 + 1] = ycoord;
		vert[m_NumOfVerts * 3 + 2] = 0.0;

		col[m_NumOfVerts * 3] = 0.0;
		col[m_NumOfVerts * 3 + 1] = 0.0;
		col[m_NumOfVerts * 3 + 2] = 1.0;

		tex[m_NumOfVerts * 2] = 0.5 + 0.5 * cos(glm::radians(i));
		tex[m_NumOfVerts * 2 + 1] = 0.5 + 0.5 * sin(glm::radians(i));

		m_NumOfVerts++;

		i += step;

		xcoord = m_Radius * cos(glm::radians(i));
		ycoord = m_Radius * sin(glm::radians(i));

		vert[m_NumOfVerts * 3] = xcoord;
		vert[m_NumOfVerts * 3 + 1] = ycoord;
		vert[m_NumOfVerts * 3 + 2] = 0.0;

		col[m_NumOfVerts * 3] = 0.0;
		col[m_NumOfVerts * 3 + 1] = 0.0;
		col[m_NumOfVerts * 3 + 2] = 1.0;

		tex[m_NumOfVerts * 2] = 0.5 + 0.5 * cos(glm::radians(i));
		tex[m_NumOfVerts * 2 + 1] = 0.5 + 0.5 * sin(glm::radians(i));

		m_NumOfVerts++;

		vert[m_NumOfVerts * 3] = 0.0;
		vert[m_NumOfVerts * 3 + 1] = 0.0;
		vert[m_NumOfVerts * 3 + 2] = 0.0;

		col[m_NumOfVerts * 3] = 0.0;
		col[m_NumOfVerts * 3 + 1] = 0.0;
		col[m_NumOfVerts * 3 + 2] = 1.0;

		tex[m_NumOfVerts * 2] = 0.5;
		tex[m_NumOfVerts * 2 + 1] = 0.5;

		m_NumOfVerts++;

		i -= step;
	}

	//VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);

	glGenBuffers(3, m_vboID); // we need two VBOs - one for the vertices and one for the colours

	//Lets set up the vertices.
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);

	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, m_NumOfVerts * 3 * sizeof(GLfloat), vert, GL_STATIC_DRAW);

	//set the position - linked to the position shader input
	GLint vertexLocation = glGetAttribLocation(m_Shader->handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Now set up the colours
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, m_NumOfVerts * 3 * sizeof(GLfloat), col, GL_STATIC_DRAW);

	//set the colour - linked to the colour shader input.
	GLint colorLocation = glGetAttribLocation(m_Shader->handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	//location in shader, number of componentns,  type, normalised, stride, pointer to first attribute
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Now set up the texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, m_NumOfVerts * 2 * sizeof(GLfloat), tex, GL_STATIC_DRAW);

	//set the colour - linked to the colour shader input.
	GLint textureLocation = glGetAttribLocation(m_Shader->handle(), "in_TexCoord");
	glEnableVertexAttribArray(textureLocation);
	//location in shader, number of componentns,  type, normalised, stride, pointer to first attribute
	glVertexAttribPointer(textureLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//good practice to bind to 0.
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Circle::Render(glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	glUseProgram(m_Shader->handle());  // use the shader

	//set the uniform for the projectionmatrix
	glUniformMatrix4fv(glGetUniformLocation(m_Shader->handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	//pass the uniform for the ModelView matrix to the shader
	glUniformMatrix4fv(glGetUniformLocation(m_Shader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	//set the DiffuseMap in GLSL to the texture unit 0.
	glUniform1i(glGetUniformLocation(m_Shader->handle(), "DiffuseMap"), 0);

	glBindTexture(GL_TEXTURE_2D, m_TexName);

	//Draw the object
	glBindVertexArray(m_vaoID);		// select first VAO
	glDrawArrays(GL_TRIANGLES, 0, m_NumOfVerts);	// draw first object

	glBindVertexArray(0); //unbind the vertex array object
	glUseProgram(0); //turn off the current shader
}
