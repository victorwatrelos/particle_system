#include <iostream>
#include <cmath>

int main()
{
	for (float i = 0.f; i < 30.0f; i += 0.5f)
	{
		std::cout << "10.0f % " << i << " = " << std::fmod(10.0f, i) << std::endl;
	}
}
