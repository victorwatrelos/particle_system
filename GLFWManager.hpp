#ifndef __GLFW_MANAGER__HPP__
# define __GLFW_MANAGER__HPP__

# include "OpenGL.hpp"
# include "OpenCL.hpp"
# include <iostream>

class GLFWManager {
	public:
		GLFWManager (void);
		GLFWManager (const GLFWManager &);
		virtual ~GLFWManager ( void );
		GLFWManager &operator=(const GLFWManager &);
		friend std::ostream &operator<< (std::ostream &, const GLFWManager &);
		void		run(void);
	private:
		GLFWwindow	*_window;
		int			_width;
		int			_height;
		void		_initGlfw(void);
		OpenGL		*_openGL;
		OpenCL		*_openCL;
		int			_frameBufferWidth;
		int			_frameBufferHeight;
		int			_nbParticles;
};

#endif
