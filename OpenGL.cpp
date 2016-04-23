#include "OpenGL.hpp"

OpenGL::OpenGL(void) 
	: _width(640), _height(480) {
	this->_initOpenGL();
}

OpenGL::OpenGL(int width, int height) 
	: _width(width), _height(height) {
	this->_initOpenGL();
}

void	OpenGL::_initOpenGL(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, this->_width, this->_height);
	this->_initShader();
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
	GLfloat						lstPt[] =
	{
		3.1f, 2.1f, -10.1f, 1.0f,
		0.0f, 0.0f, -10.f, 1.0f,
		2.f, 3.f, -10.f, 1.0f
	};

	this->_nbParticles = 3;
	glGenVertexArrays(1, &(this->_vao));
	glBindVertexArray(this->_vao);
	glGenBuffers(1, this->_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->_nbParticles * 4, lstPt, GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(this->_shader_program, "in_ParticlePos");
	glVertexAttribPointer(attrloc, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void		OpenGL::draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->_shader_program);
	glBindVertexArray(this->_vao);
	glDrawArraysInstanced(GL_POINTS, 0, 1, this->_nbParticles);
}

void		OpenGL::_setUniformLocation(void)
{
	this->_uloc_P = glGetUniformLocation(this->_shader_program, "P");
}

void		OpenGL::_setStaticUniform(void)
{
	GLfloat		*proj_matrix;

	proj_matrix = Matrix::get_projection(45, this->_width / this->_height, 0.1, 1000);
	glUniformMatrix4fv(this->_uloc_P, 1, GL_FALSE, proj_matrix);
	delete proj_matrix;
}

void		OpenGL::setDynUniform(void)
{
}

void		OpenGL::_initShader(void)
{
	std::string		*vertSrc;
	std::string		*fragSrc;

	std::cout << "Vertex shader compilation" << std::endl;
	vertSrc = this->_getSrc("shaders/vertex_shader.vert");
	std::cout << "Framgent shader compilation" << std::endl;
	fragSrc = this->_getSrc("shaders/fragment_shader.frag");
	std::cout << vertSrc << " " << fragSrc << std::endl;
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

