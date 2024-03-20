#include <iostream>
#include <array>
#include "../inc/utils.h"


int main ()
{
	std::array <long double, 3> vec {0.3, 5, -1};
	auto vec2 = rotationEuler (vec, 3, 1, 0);
	for (auto&& i : vec2)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
