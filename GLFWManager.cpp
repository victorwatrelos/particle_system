#include "GLFWManager.hpp"

static void		error_callback(int error, const char* description)
{
	std::cout << "error: " << error << ", " << description << std::endl;
}

GLFWManager::GLFWManager( void ) 
	: _width(640), _height(480) {
	this->_initGlfw();
}

void	GLFWManager::run(void) {
	while (!glfwWindowShouldClose(this->_window))
	{
		this->_openGL->draw();
		glfwPollEvents();
		glfwSwapBuffers(this->_window);
	}
}

void	GLFWManager::_initGlfw(void)
{
    if (!glfwInit())
        exit(1);
	glfwWindowHint(GLFW_SAMPLES, 4);
  	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);
    this->_window = glfwCreateWindow(this->_width, this->_height, "particle system", NULL, NULL);
    if (!this->_window)
		exit(1);
	glfwMakeContextCurrent(this->_window);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(this->_window, this);
	glfwGetFramebufferSize(this->_window, &(this->_frameBufferWidth), &(this->_frameBufferHeight));
	this->_openGL = new OpenGL(this->_frameBufferWidth, this->_frameBufferHeight);
}

GLFWManager::GLFWManager (const GLFWManager &src) {
	(void)src;
}

GLFWManager::~GLFWManager ( void ) {
	delete this->_openGL;
	glfwTerminate();
}

GLFWManager &GLFWManager::operator=(const GLFWManager &src) {
	(void)src;
	return *this;
}

std::ostream &operator<< (std::ostream &stream, const GLFWManager &obj) {
	(void)obj;
	return stream;
}

