#include <vector>
#include "GLFWManager.hpp"
#include "OpenCLException.hpp"
#include "OpenGLException.hpp"

int		main()
{
	GLFWManager		manager;

	try {
		manager.run();
	} catch (std::exception *e) {
		std::cout << "OpenCL Exception, End of program" << std::endl;
	}
}
