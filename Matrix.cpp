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

static void	display_matrix(GLfloat *m)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::cout << m[i * 4 + j] << ", ";
		}
		std::cout << std::endl;
	}
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
	display_matrix(res);
	return (res);
}

GLfloat		*Matrix::get_rot_m(float alpha)
{
	float	*res;
	float	cos_a;
	float	sin_a;

	if (!(res = Matrix::get_identity()))
		return (NULL);
	cos_a = cos(alpha);
	sin_a = sin(alpha);
	res[0] = cos_a;
	res[2] = -sin_a;
	res[8] = sin_a;
	res[10] = cos_a;
	return (res);
}
