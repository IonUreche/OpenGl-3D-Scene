#include "Sphere.h"


Sphere::Sphere(glm::vec3 pos, float radius, unsigned int rings, unsigned int sectors)
{
	m_rings = rings;
	m_sectors = sectors;

	float const R = 1. / (float)(rings - 1);
	float const S = 1. / (float)(sectors - 1);
	int r, s;

	vertices.resize(rings * sectors * 3);
	colors.resize(rings * sectors * 3);
	normals.resize(rings * sectors * 3);
	texcoords.resize(rings * sectors * 2);
	std::vector<GLfloat>::iterator v = vertices.begin();
	std::vector<GLfloat>::iterator n = normals.begin();
	std::vector<GLfloat>::iterator t = texcoords.begin();
	std::vector<GLfloat>::iterator c = colors.begin();
	for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
		//float y = sin(-M_PI_2 + M_PI * r * R);
		//float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
		//float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);
		float phi = 2 * M_PI * s * S;
		float theta = M_PI * r * R - M_PI_2;

		float x = cos(theta) * cos(phi);
		float y = cos(theta) * sin(phi);
		float z = sin(theta);

		*t++ = s*S;
		*t++ = r*R;

		*v++ = x * radius + pos.x;
		*v++ = y * radius + pos.y;
		*v++ = z * radius + pos.z;

		*n++ = x + pos.x;
		*n++ = y + pos.y;
		*n++ = z + pos.z;

		*c++ = 1.0f;
		*c++ = 1.0f;
		*c++ = 1.0f;
	}

	indices.resize(rings * sectors * 4);
	std:vector<GLushort>::iterator i = indices.begin();
	for (r = 0; r < rings; r++) 
		for (s = 0; s < sectors; s++) {
			*i++ = r * sectors + s;
			*i++ = (r + 1) * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
	}
}

void Sphere::draw()
{
	CreateVBO();
	glPointSize(4.0f);

	glDrawArrays(GL_TRIANGLE_STRIP, 2 * m_sectors, m_sectors);
}

void Sphere::CreateVBO()
{
	// se creeaza un buffer nou se seteaza ca buffer curent si punctele sunt "copiate" in bufferul curent
	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	// se activeaza lucrul cu atribute; atributul 0 = pozitie
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// un nou buffer, pentru culoare
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
	// atributul 1 =  culoare
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// un nou buffer, pentru indici
	glGenBuffers(1, &elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), &indices[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 1, GL_SHORT, GL_FALSE, 0, 0);
}

void Sphere::DestroyVBO()
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &elementBufferId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

Sphere::~Sphere()
{
}
