#include "GLFWManager.hpp"
#include <unistd.h>

static void		error_callback(int error, const char* description)
{
	std::cout << "error: " << error << ", " << description << std::endl;
}

GLFWManager::GLFWManager( int nbParticles ) 
	: _width(1000), _height(1000), _nbParticles(nbParticles) {
	this->_time = 0;
	this->_xPos = 0.5f;
	this->_yPos = 0.5f;
	this->_initGlfw();
}

static void			key_callback(GLFWwindow *window, int key,
		int scancode, int action, int mods)
{
	GLFWManager	*glfwManager;

	glfwManager = reinterpret_cast<GLFWManager *>(glfwGetWindowUserPointer(window));
	glfwManager->ctrl.addInput(key, scancode, action, mods);
	glfwManager->updateCtrl();
}

static void cursorCallback(GLFWwindow* window, double xPos, double yPos)
{
	GLFWManager	*glfwManager;

	glfwManager = reinterpret_cast<GLFWManager *>(glfwGetWindowUserPointer(window));
	glfwManager->setCursorPos(xPos, yPos);
}

void	GLFWManager::updateCtrl(void)
{
	this->_openGL->setBorderSize(this->ctrl.getZoom());
	this->_openCL->setBorderSize(this->ctrl.getZoom());
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
	float			calcFps;

	gettimeofday(&time, NULL);
	tmpTime = time.tv_sec * 1000000 + time.tv_usec;
	if (tmpTime - this->_time > 1000000)
	{
		calcFps = 1.0f / (this->_timerTotal.getMsFloatAverage() / 1000.f);
		this->_time = tmpTime;
		glfwSetWindowTitle(this->_window, (std::to_string(calcFps) + " / " + std::to_string(this->_nbFrame)).c_str());
/*		std::cout << "FPS:\t\t" << this->_nbFrame << std::endl;
		std::cout << "OpenCL av:\t" << this->_timerOpenCL.getMsFloatAverage() << "ms" << std::endl;
		std::cout << "OpenGL av:\t" << this->_timerOpenGL.getMsFloatAverage() << "ms" << std::endl;
		std::cout << "Total av:\t" << this->_timerTotal.getMsFloatAverage() << "ms" << std::endl;*/
		this->_nbFrame = 0;
	}
	this->_nbFrame++;

}

void	GLFWManager::_inLoop(void)
{
		this->ctrl.loop();
		this->updateCtrl();
		this->_timerOpenCL.start();
		if (this->ctrl.getGravity())
			this->_openCL->setPos(this->_xPos, this->_yPos);
		if (!this->ctrl.isRunning() && this->ctrl.isSetCenter())
			this->_openCL->initParticles(this->ctrl.isCube());
		if (this->ctrl.isRunning())
			this->_openCL->loop();
		this->_timerOpenCL.stop();
		this->_timerOpenGL.start();
		this->_openGL->draw();
		this->_timerOpenGL.stop();
}

void	GLFWManager::run(void) {
	this->_nbFrame = 0;
	this->_openGL->draw();
	glfwSwapBuffers(this->_window);
	while (!glfwWindowShouldClose(this->_window))
	{
		this->_timerTotal.start();
		this->_inLoop();
		glfwPollEvents();
		glfwSwapBuffers(this->_window);
		this->_timerTotal.stop();
		this->_tick();
	}
}

void	GLFWManager::_initGlfw(void)
{
	float		ratio;

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
	glfwSetKeyCallback(this->_window, key_callback);
	glfwGetFramebufferSize(this->_window, &(this->_frameBufferWidth), &(this->_frameBufferHeight));
	std::cout << "Start opengl" << std::endl;
	this->_openGL = new OpenGL(this->_frameBufferWidth, this->_frameBufferHeight, this->_nbParticles, 30000);
	ratio =  (float)(this->_height) / (float)(this->_width);
	this->_openCL = new OpenCL(this->_openGL->getParticlesVBO(), this->_openGL->getParticlesColorVBO(), this->_nbParticles, ratio);
}

GLFWManager::GLFWManager (const GLFWManager &src) {
	(void)src;
}

GLFWManager::~GLFWManager ( void ) {
	if (this->_openGL)
		delete this->_openGL;
	if (this->_openCL)
		delete this->_openCL;
	glfwDestroyWindow(this->_window);
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

