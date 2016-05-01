#include <vector>
#include "GLFWManager.hpp"
#include "OpenCLException.hpp"
#include "OpenGLException.hpp"

void	printHelp(void)
{
	std::cout << "+ / - to zoom" << std::endl;
	std::cout << "t to move / stop moving the gravity center" << std::endl;
	std::cout << "r to launch / stop the simulation" << std::endl;
	std::cout << "f to set start position (Simulation must be not running)" << std::endl;
}

int		main()
{
	GLFWManager		manager;

	printHelp();
	try {
		manager.run();
	} catch (OpenCLException *e) {
		std::cout << "OpenCL Exception, End of program" << std::endl;
	}
}
