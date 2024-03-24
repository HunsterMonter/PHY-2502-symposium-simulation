#include "Planete.h"
#include "Systeme.h"
#include "utils.h"
#include <array>
#include <iostream>


int main ()
{
	Planete p1 (1, 2, 3, 4, 5, 6, 7, 8);
	Planete p2 (1, 2, 3, 4, 5, 6, 7, 8);
	Planete p3 (1, 2, 3, 4, 5, 6, 7, 8);
	Planete p4 (1, 2, 3, 4, 5, 6, 7, 8);
	Planete p5 ({1, 2, 3}, {4, 5, 6}, 2);
	Planete p8 (1, {p4, p5});
	std::array <Planete, 2> a {p1, p2};
	Planete p9 (1, a);

	for (auto i : p9.pos)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::array <Planete, 4> Ps {p1, p2, p3, p4};
	Systeme <4> s {p1, p2, p3, p4};

	return 0;
}
