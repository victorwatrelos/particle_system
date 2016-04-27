#ifndef __TIME__HPP__
# define __TIME__HPP__

# include <iostream>
# include <sys/time.h>
# include <vector>

class Timer {
	public:
		Timer (void);
		Timer (const Timer &);
		virtual ~Timer ( void );
		void		start(void);
		void		stop(void);
		uint64_t	getLastTime(void);
		uint64_t	getAverage(void);
		float		getMsFloatAverage(void);
		void		flush(void);

		Timer &operator=(const Timer &);
		friend std::ostream &operator<< (std::ostream &, const Timer &);
	private:
		uint64_t				_getCurrentTime(void);
		uint64_t				_startTime;
		std::vector<uint64_t>	_time;
		bool					_isLaunch;
};

#endif
