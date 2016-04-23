#ifndef __MATRIX__HPP__
# define __MATRIX__HPP__

# include "OpenGLInc.hpp"
# include <iostream>
# include <cmath>

namespace Matrix
{
	GLfloat		*get_identity(void);
	GLfloat		*get_projection(GLfloat fovy, GLfloat aspect, GLfloat near, GLfloat far);
}

#endif
