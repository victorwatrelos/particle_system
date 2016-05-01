#ifndef __TASK_INIT_PARTICLES__HPP__
# define __TASK_INIT_PARTICLES__HPP__

# include <iostream>
# include "OpenCLInc.hpp"
# include "Task.hpp"

class TaskInitParticles : public Task {
	public:
		TaskInitParticles (cl_context context, cl_device_id device, cl_int nbParticles);
		void		createKernel(void);
	private:
		void		_setSphereDefine(void);
};

#endif

