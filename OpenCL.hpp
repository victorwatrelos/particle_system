#ifndef __OPENCL__HPP__
# define __OPENCL__HPP__

# include <iostream>
# include "OpenCLInc.hpp"
# include "OpenGLInc.hpp"
# include "OpenCLException.hpp"
# include "Task.hpp"
# include "TaskInitParticles.hpp"
# include "TaskApplyVel.hpp"

class OpenCL {
	public:
		OpenCL(GLuint particlesVBO, int nbParticles);
		OpenCL (const OpenCL &);
		virtual ~OpenCL ( void );
		static void		checkCLSuccess(cl_int errNum, std::string name);
		void			loop(void);

		OpenCL &operator=(const OpenCL &);
		friend std::ostream &operator<< (std::ostream &, const OpenCL &);
	private:
		OpenCL (void);
		void	_initOpenCL(void);
		void	_createContext(void);
		void	_getDeviceInfo(void);
		void	_release(void);
		void	_bindBuffer(void);
		void	_bindVBOBuffer();
		void	_createCommandQueue(void);
		void	_initTask(void);
		void	_setKernelArg(void);
		void	_setInitParticlesArg(void);
		void	_setApplyVelArg(void);

		cl_context			_context;
		cl_int				_nbDevices;
		cl_device_id		_device;
		cl_int				_maxWorkingDimensions;
		size_t				*_maxWorkItemSize;
		cl_mem				_particlesVelocity;
		cl_mem				_particlesVBO;
		cl_command_queue	_commandQueue;
		int					_nbParticles;
		GLuint				_vbo;
		TaskInitParticles	*_taskInitParticles;
		TaskApplyVel		*_taskApplyVel;
		float				_boxX;
		float				_boxY;
		float				_boxZ;


};

#endif

