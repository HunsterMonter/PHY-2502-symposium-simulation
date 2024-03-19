#pragma once
#include <array>


template <std::size_t N>
class Planete
{
public:
	Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double m, long double M);

	Planete (std::array <Planete, N>, long double M)

private:
	long double x;
	long double y;
	long double z;

	long double vx;
	long double vy;
	long double vz;

	long double m;
};
