#include "OpenCL.hpp"

OpenCL::OpenCL( GLuint particlesVBO, int nbParticles)
	: _nbParticles(nbParticles), _vbo(particlesVBO), _boxZ(5.0f) {
		this->_boxX = sqrt(nbParticles);
		this->_boxY = sqrt(nbParticles);
	this->_initOpenCL();
}

void	OpenCL::_initOpenCL(void)
{
	this->_createContext();
	this->_bindBuffer();
	this->_bindVBOBuffer();
	this->_initTask();
	this->_createCommandQueue();
	this->_setKernelArg();
	std::cout << "Enqueue" << std::endl;
	this->_taskInitParticles->enqueueKernel(this->_commandQueue);
	clFinish(this->_commandQueue);
	std::cout << "Stop" << std::endl;
}

void	OpenCL::_setKernelArg(void)
{
	this->_setInitParticlesArg();
	this->_setApplyVelArg();
}

void	OpenCL::_setApplyVelArg(void)
{
	cl_kernel	kernel = this->_taskApplyVel->getKernel();

	checkCLSuccess(clSetKernelArg(kernel, 0, sizeof(cl_mem),
				&this->_particlesVBO),
			"clSetKernelArg setApplyVelArg 0");

	checkCLSuccess(clSetKernelArg(kernel, 1, sizeof(cl_mem),
				&this->_particlesVelocity),
			"clSetKernelArg setApplyVelArg 1");
}

void	OpenCL::_setInitParticlesArg(void)
{
	cl_kernel	kernel = this->_taskInitParticles->getKernel();

	checkCLSuccess(clSetKernelArg(kernel, 0, sizeof(cl_mem),
				&this->_particlesVBO),
			"clSetKernelArg setInitParticlesArg 0");

	checkCLSuccess(clSetKernelArg(kernel, 1, sizeof(cl_mem),
				&this->_particlesVelocity),
			"clSetKernelArg setInitParticlesArg 1");
}

void	OpenCL::_initTask(void)
{
	this->_taskInitParticles = new TaskInitParticles(this->_context, this->_device, this->_nbParticles);
	this->_taskInitParticles->setMaxGid(std::to_string(this->_nbParticles));
	this->_taskInitParticles->setBoxSize(this->_boxX, this->_boxY, this->_boxZ);
	this->_taskInitParticles->createKernel();

	this->_taskApplyVel = new TaskApplyVel(this->_context, this->_device, this->_nbParticles);
	this->_taskApplyVel->setMaxGid(std::to_string(this->_nbParticles));
	this->_taskApplyVel->setBoxSize(this->_boxX, this->_boxY, this->_boxZ);
	this->_taskApplyVel->createKernel();
}

void	OpenCL::loop(void)
{
	this->_taskApplyVel->enqueueKernel(this->_commandQueue);
	clFinish(this->_commandQueue);
}

void    OpenCL::_getDeviceInfo() {
    size_t      size;
    char        *deviceName;

    checkCLSuccess(clGetDeviceInfo(this->_device,
                CL_DEVICE_NAME,
                0,
                NULL,
                &size),
        "clGetDeviceInfo size");
    deviceName = new char[size];
    checkCLSuccess(clGetDeviceInfo(this->_device,
                CL_DEVICE_NAME,
                size,
                deviceName,
                NULL),
            "clGetDeviceInfo info");
    std::cout << "Device: " << deviceName << std::endl;
    delete[] deviceName;
    checkCLSuccess(clGetDeviceInfo(this->_device,
                CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                sizeof(cl_uint),
                &(this->_maxWorkingDimensions),
                NULL),
            "clGetDeviceInfo max working dimensions");

    this->_maxWorkItemSize = new size_t[this->_maxWorkingDimensions];

    checkCLSuccess(clGetDeviceInfo(this->_device,
                CL_DEVICE_MAX_WORK_ITEM_SIZES,
                sizeof(size_t) * this->_maxWorkingDimensions,
                this->_maxWorkItemSize,
                NULL),
            "clGetDeviceInfo max working dimensions");

    std::cout << "(";
    for (cl_int i = 0; i < this->_maxWorkingDimensions; i++) {
        std::cout << this->_maxWorkItemSize[i] << ", ";
    }
    std::cout << ")" << std::endl;

}

void    OpenCL::checkCLSuccess(cl_int errNum, std::string name) {
    if (errNum != CL_SUCCESS) {
        std::cout << "OpenCL fail on " << name << std::endl;
        throw new OpenCLException();
    }
}

void    OpenCL::_createContext(void) {
    cl_int      err;

    CGLContextObj kCGLContext = CGLGetCurrentContext();
    CGLShareGroupObj kCGLShareGroup = CGLGetShareGroup(kCGLContext);

    cl_context_properties properties[] =
    {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        (cl_context_properties)kCGLShareGroup,
        0
    };

    this->_context = clCreateContext(properties, 0, 0, NULL, NULL, &err);
    checkCLSuccess(err, "clCreateContext");
    checkCLSuccess(clGetContextInfo(this->_context,
                CL_CONTEXT_NUM_DEVICES,
                sizeof(cl_int),
                &(this->_nbDevices),
                NULL),
        "clGetContextInfo");

    if (this->_nbDevices < 1) {
        throw new OpenCLException();
    }

    checkCLSuccess(clGetContextInfo(this->_context,
                CL_CONTEXT_DEVICES,
                sizeof(cl_device_id),
                &(this->_device),
                NULL),
        "clGetContextInfo");
}

void    OpenCL::_createCommandQueue( void ) {
    int     err;

    this->_commandQueue = clCreateCommandQueue(this->_context, this->_device, 0, &err);
    checkCLSuccess(err, "clCreateCommandQueue");
}

void	OpenCL::_bindVBOBuffer(void)
{
	cl_int		err;

	this->_particlesVBO = clCreateFromGLBuffer(
			this->_context,
			CL_MEM_READ_WRITE,
			this->_vbo,
			&err);
}

void	OpenCL::_bindBuffer(void)
{
    int		err;
    size_t	sizeBuf = this->_nbParticles * sizeof(cl_float) * 4;

    this->_particlesVelocity = clCreateBuffer(
    		this->_context,
    		CL_MEM_READ_WRITE,
    		sizeBuf,
    		NULL,
    		&err);
    checkCLSuccess(err, "clCreateBuffer particlesVelocity");
}

void	OpenCL::_release(void)
{
	clReleaseMemObject(this->_particlesVBO);
	clReleaseMemObject(this->_particlesVelocity);
	clReleaseContext(this->_context);
}

OpenCL::OpenCL (const OpenCL &src) {
	(void)src;
}

OpenCL::~OpenCL ( void ) {
	this->_release();
	delete this->_maxWorkItemSize;
}

OpenCL &OpenCL::operator=(const OpenCL &src) {
	(void)src;
	return *this;
}

std::ostream &operator<< (std::ostream &stream, const OpenCL &obj) {
	(void)obj;
	return stream;
}

