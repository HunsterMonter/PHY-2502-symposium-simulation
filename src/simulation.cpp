#include "Planete.h"
#include "Systeme.h"
#include "utils.h"
#include <array>
#include <iostream>


int main ()
{
	Planete <3> p1 (7, 8, {1, 2, 3, 4, 5, 6});
	Planete <3> p2 (7, 8, {1, 2, 3, 4, 5, 6});
	Planete <3> p3 (7, 8, {1, 2, 3, 4, 5, 6});
	Planete <3> p4 (7, 8, {1, 2, 3, 4, 5, 6});
	Planete <3> p5 (2, {1, 2, 3}, {4, 5, 6});
	Planete <3> p8 (1, {p4, p5});
	std::array <Planete <3>, 1> a {p5};
	Planete <3> p9 (1, a);
	Planete <2> p10 (7, 8, {1, 2, 0, 0, 5, 6});

	for (auto i : p8.pos)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;

	std::array <Planete <3>, 4> Ps {p1, p2, p3, p4};
	Systeme <3, 4> s {p1, p2, p3, p4};

	return 0;
}
