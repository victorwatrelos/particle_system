#include "Control.hpp"

Control::Control( void ) 
	: _zoom(30000.f)
{

}

Control::Control (const Control &src) {
	(void)src;
}

bool	Control::getGravity(void)
{
	return (this->_fixedGrav);
}

float	Control::getZoom(void)
{
	return (this->_zoom);
}

bool	Control::isRunning()
{
	return (this->_running);
}

bool	Control::isSetCenter()
{
	return (this->_setCenter);
}

void	Control::loop(void)
{
	if (this->_zoomBtnP)
		this->_zoom = fmin(this->_zoom + ZOOM_STEP, MAX_ZOOM);
	if (this->_zoomBtnM)
		this->_zoom = fmax(this->_zoom - ZOOM_STEP, MIN_ZOOM);
}

bool	Control::isCube(void)
{
	return (this->_isCube);
}

void	Control::addInput(int key, int scancode, int action, int mods)
{
	//std::cout << "key: " << (char)key <<  " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
	(void)scancode;
	(void)mods;
	if (action == GLFW_PRESS)
	{
		if (key == '=')
			this->_zoomBtnM = true;
		if (key == '-')
			this->_zoomBtnP = true;
		if (key == 'T')
			this->_fixedGrav = !this->_fixedGrav;
		if (key == 'R')
			this->_running = !this->_running;
		if (key == 'F')
		{
			this->_setCenter = !this->_setCenter;
			this->_running = false;
			this->_fixedGrav = false;
		}
		if (key == 'C')
			this->_isCube = !this->_isCube;
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == '=')
			this->_zoomBtnM = false;
		if (key == '-')
			this->_zoomBtnP = false;
	}
}

Control::~Control ( void ) {
}

Control &Control::operator=(const Control &src) {
	(void)src;
	return *this;
}

std::ostream &operator<< (std::ostream &stream, const Control &obj) {
	(void)obj;
	return stream;
}
