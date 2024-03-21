#pragma once
#include <vector>
#include <array>


class Planete
{
public:
	Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double mass, long double Mass);

	Planete (std::vector <Planete>, long double M);

private:
	std::array <long double, 3> pos;
	std::array <long double, 3> v;
	const long double m;
};
