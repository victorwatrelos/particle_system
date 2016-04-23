#ifndef __OPENGL__HPP__
# define __OPENGL__HPP__

# include <iostream>
# include <fstream>
# include <string>
# include "OpenGLInc.hpp"
# include "OpenGLException.hpp"
# include "Matrix.hpp"

class OpenGL {
	public:
		OpenGL (void);
		OpenGL (int32_t width, int32_t height);
		OpenGL (const OpenGL &);
		virtual ~OpenGL ( void );
		OpenGL &operator=(const OpenGL &);
		friend std::ostream &operator<< (std::ostream &, const OpenGL &);

		void		setDynUniform(void);
		void		draw(void);
	private:
		int32_t		_width;
		int32_t		_height;
		uint32_t	_nbParticles;
		GLuint		_vs;
		GLuint		_fs;
		GLuint		_vbo[1];
		GLuint		_vao;
		GLuint		_shader_program;
		GLint		_uloc_P;

		void			_initOpenGL(void);
		void			_initShader(void);
		void			_initBuffer(void);
		void			_setUniformLocation(void);
		void			_setStaticUniform(void);
		std::string		*_getSrc(std::string filename) const;
		static GLuint	_getShader(const std::string *shaderSrc, GLenum shaderType);
};

#endif
