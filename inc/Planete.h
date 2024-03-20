#pragma once
#include <vector>
#include <array>


class Planete
{
public:
	Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double m, long double M);

	Planete (std::vector <Planete>, long double M);

private:
	std::array <long double, 3> pos;
	std::array <long double, 3> v;
	long double m;
};
