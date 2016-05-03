#ifndef __CONTROL__HPP__
# define __CONTROL__HPP__

# include "OpenGLInc.hpp"
# include <iostream>
# include <math.h>
# define ZOOM_STEP 1000.f
# define MAX_ZOOM 200000.f
# define MIN_ZOOM 500.f

class Control {
	public:
		Control (void);
		Control (const Control &);
		virtual ~Control ( void );

		Control &operator=(const Control &);
		friend std::ostream &operator<< (std::ostream &, const Control &);
		void	addInput(int key, int scancode, int action, int mods);
		float	getZoom(void);
		void	loop(void);
		bool	getGravity(void);
		bool	isRunning(void);
		bool	isSetCenter(void);
		bool	isCube(void);
		bool	isQuit(void);
	private:
		float		_zoom;
		bool		_zoomBtnP = false;
		bool		_zoomBtnM = false;
		bool		_fixedGrav = true;
		bool		_running = false;
		bool		_setCenter = false;
		bool		_quit = false;
		bool		_isCube = true;
};

#endif
