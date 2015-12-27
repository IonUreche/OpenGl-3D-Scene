#pragma once

#include <vector>
#include <GL/glew.h> 
#include <GL/freeglut.h>
#include <glm\vec3.hpp>

#include <cmath> 
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923

using namespace std;

class Sphere
{
protected:
	int m_rings;
	int m_sectors;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> texcoords;
	std::vector<GLfloat> colors;
	std::vector<GLushort> indices;

public:
	Sphere(glm::vec3 pos, float radius, unsigned int rings, unsigned int sectors);
	~Sphere();

	void draw();

private:

	GLuint
		VaoId,
		VboId,
		elementBufferId,
		ColorBufferId,
		VertexShaderId,
		FragmentShaderId,
		ProgramId;

	void CreateVBO();
	void DestroyVBO();
};

