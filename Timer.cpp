#include "Timer.hpp"

Timer::Timer( void ) 
	: _isLaunch(false) {

}

void	Timer::start(void)
{
	this->_startTime = this->_getCurrentTime();
	this->_isLaunch = true;
}

uint64_t	Timer::getLastTime(void)
{
	return this->_time.back();
}

float		Timer::getMsFloatAverage(void)
{
	return ((float)this->getAverage()) / 1000.f;
}

uint64_t	Timer::getAverage(void)
{
	uint64_t	tot;

	if (this->_time.size() == 0)
		return 0;
	tot = 0;
	for (auto &i : this->_time) {
		tot += i;
	}
	return tot / this->_time.size();
}

void		Timer::flush(void)
{
	this->_time.clear();
}


void	Timer::stop(void)
{
	uint64_t	current;

	if (!this->_isLaunch)
		return ;
	current = this->_getCurrentTime();
	this->_time.push_back(this->_getCurrentTime() - this->_startTime);
	this->_isLaunch = false;
}

uint64_t	Timer::_getCurrentTime(void)
{
	struct timeval	tv;
	uint64_t		res;

	gettimeofday(&tv, NULL);
	res = tv.tv_usec;
	res += tv.tv_sec * 1000000;
	return (res);
}

Timer::Timer (const Timer &src) {
	(void)src;
}

Timer::~Timer ( void ) {
}

Timer &Timer::operator=(const Timer &src) {
	(void)src;
	return *this;
}

std::ostream &operator<< (std::ostream &stream, const Timer &obj) {
	(void)obj;
	return stream;
}
