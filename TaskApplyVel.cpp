#include "TaskApplyVel.hpp"

TaskApplyVel::TaskApplyVel (cl_context context, cl_device_id device, cl_int nbParticles)
{
	this->_context = context;
	this->_device = device;
	this->_nbParticle = nbParticles;
}

void		TaskApplyVel::createKernel()
{
	this->_createKernel("kernel/applyVel.cl", "applyVel");
}

void		TaskApplyVel::setBoxSize(float x, float y, float z)
{
	this->_defineOptions.insert(t_DefineOption("SIZE_X", std::to_string(x)));
	this->_defineOptions.insert(t_DefineOption("SIZE_Y", std::to_string(y)));
	this->_defineOptions.insert(t_DefineOption("SIZE_Z", std::to_string(z)));
}
