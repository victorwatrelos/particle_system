#include "GLFWManager.hpp"
#include <unistd.h>

static void		error_callback(int error, const char* description)
{
	std::cout << "error: " << error << ", " << description << std::endl;
}

GLFWManager::GLFWManager( void ) 
	: _width(1500), _height(1000), _nbParticles(3000000) {
	this->_initGlfw();
}

static void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	GLFWManager	*glfwManager;

	glfwManager = reinterpret_cast<GLFWManager *>(glfwGetWindowUserPointer(window));
	glfwManager->setCursorPos(xPos, yPos);
}

void	GLFWManager::setCursorPos(double xPos, double yPos)
{
	this->_xPos = xPos / this->_width;
	this->_yPos = yPos / this->_height;
}

void	GLFWManager::_tick(void)
{
	struct timeval	time;
	int64_t			tmpTime;

	gettimeofday(&time, NULL);
	tmpTime = time.tv_sec * 1000000 + time.tv_usec;
	if (tmpTime - this->_time > 1000000)
	{
		this->_time = tmpTime;
		std::cout << "FPS:\t\t" << this->_nbFrame << std::endl;
		std::cout << "OpenCL av:\t" << this->_timerOpenCL.getMsFloatAverage() << "ms" << std::endl;
		std::cout << "OpenGL av:\t" << this->_timerOpenGL.getMsFloatAverage() << "ms" << std::endl;
		std::cout << "Total av:\t" << this->_timerTotal.getMsFloatAverage() << "ms" << std::endl;
		this->_nbFrame = 0;
	}
	this->_nbFrame++;

}

void	GLFWManager::run(void) {
	char	str[512];

	this->_nbFrame = 0;
	this->_openGL->draw();
	glfwSwapBuffers(this->_window);
	while (!glfwWindowShouldClose(this->_window))
	{
		this->_timerOpenCL.start();
		this->_timerTotal.start();
		this->_openCL->setPos(this->_xPos, this->_yPos);
		this->_openCL->loop();
		this->_timerOpenCL.stop();
		this->_timerOpenGL.start();
		this->_openGL->draw();
		this->_timerOpenGL.stop();
		glfwPollEvents();
		glfwSwapBuffers(this->_window);
		this->_timerTotal.stop();
		this->_tick();
		(void)str;
	}
}

void	GLFWManager::_initGlfw(void)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(1);
	glfwWindowHint(GLFW_SAMPLES, 4);
  	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->_window = glfwCreateWindow(this->_width, this->_height, "particle system", NULL, NULL);
    if (!this->_window)
		exit(1);
	glfwMakeContextCurrent(this->_window);
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(this->_window, this);
	glfwSetCursorPosCallback(this->_window, cursorCallback);
	glfwGetFramebufferSize(this->_window, &(this->_frameBufferWidth), &(this->_frameBufferHeight));
	std::cout << "start opengl" << std::endl;
	this->_openGL = new OpenGL(this->_frameBufferWidth, this->_frameBufferHeight, this->_nbParticles);
	this->_openCL = new OpenCL(this->_openGL->getParticlesVBO(), this->_nbParticles);
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

