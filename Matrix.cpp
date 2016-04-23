#include "Matrix.hpp"

GLfloat		*Matrix::get_identity(void)
{
	GLfloat	*res;

	res = new GLfloat[16]();
	res[0] = 1;
	res[5] = 1;
	res[10] = 1;
	res[15] = 1;
	return (res);
}

GLfloat		*Matrix::get_projection(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far)
{
	GLfloat		f;
	GLfloat		*res;

	res = new GLfloat[16]();
	f = 1.0f / tanf(fovy / 2.0f);
	res[0] = f / aspect;
	res[5] = f;
	res[10] = (far + near) / (near - far);
	res[11] = -1.0f;
	res[14] = 2.0f * (far * near) / (near - far);
	res[15] = 0.0f;
	return (res);
}
