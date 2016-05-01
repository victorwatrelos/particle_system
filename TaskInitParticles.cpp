#include "TaskInitParticles.hpp"

TaskInitParticles::TaskInitParticles (cl_context context, cl_device_id device, cl_int nbParticles)
{
	float	x;

	this->_context = context;
	this->_device = device;
	this->_nbParticle = nbParticles;
	this->_defineOptions.insert(t_DefineOption("COEFF_START", std::to_string(50.0f)));
	x = powf(nbParticles, 0.33333333f);
	this->_defineOptions.insert(t_DefineOption("SIZE_X", std::to_string(x)));
	this->_defineOptions.insert(t_DefineOption("SIZE_Y", std::to_string(x)));
	this->_defineOptions.insert(t_DefineOption("SIZE_Z", std::to_string(x)));
	this->_setSphereDefine();
}

void		TaskInitParticles::_setSphereDefine(void)
{
	int	tot_oa, tot_teta;
	float	rSphere, stepSphere, stepCircle, nbPointPerLine;

	rSphere = 100.f;
	stepCircle = (0.01f * M_PI);
	nbPointPerLine = 15;
	stepSphere = (4 * rSphere * M_PI * nbPointPerLine) / (this->_nbParticle * stepCircle);
	tot_oa = (int)((float)((rSphere / stepSphere) * 2.f));
	tot_teta = ((2.f * M_PI) / stepCircle);

	this->_defineOptions.insert(t_DefineOption("R_SPHERE", std::to_string(rSphere)));
	this->_defineOptions.insert(t_DefineOption("STEP_SPHERE", std::to_string(stepSphere)));
	this->_defineOptions.insert(t_DefineOption("STEP_CIRCLE", std::to_string(stepCircle)));
	this->_defineOptions.insert(t_DefineOption("NB_POINT_PER_LINE", std::to_string(nbPointPerLine)));
	this->_defineOptions.insert(t_DefineOption("TOT_OA", std::to_string(tot_oa)));
	this->_defineOptions.insert(t_DefineOption("TOT_TETA", std::to_string(tot_teta)));
}

void		TaskInitParticles::createKernel()
{
	this->_createKernel("kernel/initParticles.cl", "initParticles");
}
