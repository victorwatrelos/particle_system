#include "OpenGL.hpp"

OpenGL::OpenGL(void) 
	: _width(640), _height(480), _nbParticles(100000) {
	this->_initOpenGL();
}

OpenGL::OpenGL(int32_t width, int32_t height, int32_t nbParticles) 
	: _width(width), _height(height), _nbParticles(nbParticles) {
	std::cout << "width: " << _width << " height: " << _height << std::endl;
	this->_initOpenGL();
}

void	OpenGL::_initOpenGL(void) {
	std::cout << "OK" << std::endl;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, this->_width, this->_height);
	glEnable(GL_PROGRAM_POINT_SIZE);
	this->_initShader();
	this->_initBuffer();
	glUseProgram(this->_shader_program);
	this->_setUniformLocation();
	this->_setStaticUniform();
}

std::string *OpenGL::_getSrc(std::string filename) const {
    std::ifstream ifs(filename);
    
    return new std::string( (std::istreambuf_iterator<char>(ifs) ),
                            (std::istreambuf_iterator<char>()) );
}

void		OpenGL::_initBuffer(void)
{
	GLuint						attrloc;

	std::cout << "init buffer" << std::endl;
	glGenVertexArrays(1, &(this->_vao));
	glBindVertexArray(this->_vao);
	glGenBuffers(1, this->_vbo);


	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * this->_nbParticles, NULL, GL_STREAM_DRAW);
	attrloc = glGetAttribLocation(this->_shader_program, "in_Position");
	glVertexAttribPointer(attrloc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);
	glBindVertexArray(0);
}

void		OpenGL::draw(void)
{
	this->setDynUniform();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->_shader_program);
	glBindVertexArray(this->_vao);
	glDrawArrays(GL_POINTS, 0, this->_nbParticles);
	glFinish();
}

void		OpenGL::_setUniformLocation(void)
{
	this->_uloc_P = glGetUniformLocation(this->_shader_program, "P");
	this->_uloc_R = glGetUniformLocation(this->_shader_program, "R");
}

void		OpenGL::_setStaticUniform(void)
{
	GLfloat		*proj_matrix;

	proj_matrix = Matrix::get_projection(45, this->_width / this->_height, 0.1, 10000);
	glUniformMatrix4fv(this->_uloc_P, 1, GL_FALSE, proj_matrix);
	delete proj_matrix;
}

void		OpenGL::setDynUniform(void)
{
	GLfloat		*rot_matrix;
	static float	alpha = 0.0f * M_PI;

	//alpha += 0.005f;
	if (alpha > 2.f * M_PI)
		alpha -= 2.f * M_PI;
	rot_matrix = Matrix::get_rot_m(alpha);
	glUniformMatrix4fv(this->_uloc_R, 1, GL_FALSE, rot_matrix);
	delete rot_matrix;
}

void		OpenGL::_initShader(void)
{
	std::string		*vertSrc;
	std::string		*fragSrc;

	std::cout << "Vertex shader compilation" << std::endl;
	vertSrc = this->_getSrc("shaders/vertex_shader.vert");
	std::cout << "Framgent shader compilation" << std::endl;
	fragSrc = this->_getSrc("shaders/fragment_shader.frag");
	std::cout << *vertSrc << " " << *fragSrc << std::endl;
	this->_vs = this->_getShader(vertSrc, GL_VERTEX_SHADER);
	this->_fs = this->_getShader(fragSrc, GL_FRAGMENT_SHADER);
	if (!(this->_shader_program = glCreateProgram()))
		throw new OpenGLException();
	glAttachShader(this->_shader_program, this->_vs);
	glAttachShader(this->_shader_program, this->_fs);
	glLinkProgram(this->_shader_program);
	glDetachShader(this->_shader_program, this->_vs);
	glDetachShader(this->_shader_program, this->_fs);
	glDeleteShader(this->_vs);
	glDeleteShader(this->_fs);
	glUseProgram(this->_shader_program);
}

GLuint		OpenGL::_getShader(const std::string *shaderSrc, GLenum shaderType)
{
	GLuint		shader;
	GLint		shader_ok;
    GLsizei		log_length;
    char		info_log[8192];
    const char	*src;

	src = shaderSrc->c_str();
	shader = glCreateShader(shaderType);
	glShaderSource (shader, 1, &src, NULL);
	glCompileShader (shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
	if (shader_ok != GL_TRUE)
	{
		std::cout << "ERROR: Failed to compile shader" << std::endl;
		glGetShaderInfoLog(shader, 8192, &log_length,info_log);
		std::cout << "ERROR: " << info_log << std::endl;
		glDeleteShader(shader);
		throw new OpenGLException();
	}
	return (shader);
}

OpenGL::OpenGL(const OpenGL &src) {
	(void)src;
}

OpenGL::~OpenGL( void ) {
	glDeleteProgram(this->_shader_program);
}

OpenGL &OpenGL::operator=(const OpenGL &src) {
	(void)src;
	return *this;
}

std::ostream &operator<<(std::ostream &stream, const OpenGL &obj) {
	(void)obj;
	return stream;
}

GLuint		OpenGL::getParticlesVBO(void)
{
	return this->_vbo[OPENCL_VBO];
}

