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
	std::cout << "c to set init as cube or sphere" << std::endl;
}

int		main(int ac, char **av)
{
	GLFWManager		*manager = NULL;
	int				nbParticles;

	if (ac < 2 || (nbParticles = std::atoi(av[1])) < 1 || nbParticles > 3100000)
	{
		std::cout << "./particle_system nb_particles (btw 1-3100000)" << std::endl;
		return (1);
	}
	printHelp();
	std::cout << nbParticles << std::endl;
	try {
		manager = new GLFWManager(nbParticles);
		manager->run();
	} catch (OpenCLException& e) {
		std::cout << "OpenCL Exception, End of program" << std::endl;
	} catch (OpenGLException& e) {
		std::cout << "OpenGL Exception, End of program" << std::endl;
	}
	if (manager)
		delete manager;
	return (0);
}
