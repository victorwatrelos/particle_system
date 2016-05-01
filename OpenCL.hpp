#ifndef __OPENCL__HPP__
# define __OPENCL__HPP__

# include <iostream>
# include "OpenCLInc.hpp"
# include "OpenGLInc.hpp"
# include "OpenCLException.hpp"
# include "Task.hpp"
# include "TaskInitParticles.hpp"
# include "TaskApplyVel.hpp"
# define PARTICLES_PER_WORK_ITEM 1

class OpenCL {
	public:
		OpenCL(GLuint particlesVBO, GLuint particlesColorVBO, int nbParticles, float ratio);
		OpenCL (const OpenCL &);
		virtual ~OpenCL ( void );
		static void		checkCLSuccess(cl_int errNum, std::string name);
		void			loop(void);
		void			setPos(double x, double y);
		void			setBorderSize(float size);
		void			initParticles(int isCube);

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
		void	_setDynApplyVelArg(void);
		void	_acquireGLObject(void);
		void	_releaseGLObject(void);
		void	_setInitParticlesTypeArg(int isCube);

		cl_context			_context;
		cl_int				_nbDevices;
		cl_device_id		_device;
		cl_int				_maxWorkingDimensions;
		size_t				*_maxWorkItemSize;
		cl_mem				_particlesVelocity;
		cl_mem				_particlesVBO;
		cl_mem				_particlesColorVBO;
		cl_command_queue	_commandQueue;
		int					_nbParticles;
		GLuint				_vbo;
		GLuint				_colorVBO;
		TaskInitParticles	*_taskInitParticles;
		TaskApplyVel		*_taskApplyVel;
		float				_boxX;
		float				_boxY;
		float				_boxZ;
		float				_posX;
		float				_posY;
		cl_uint				_maxComputeUnit;
		float				_ratio;
		float				_borderSize = 30000.f;

};

#endif

