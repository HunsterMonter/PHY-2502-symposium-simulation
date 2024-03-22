#pragma once
#include <vector>
#include <array>


class Planete
{
public:
	Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double mass, long double Mass);

	Planete (const std::vector <Planete>& planetes, long double mass);

	std::array <long double, 3> getPos () const;

	void setPos (std::array <long double, 3> p);

	std::array <long double, 3> getV () const;

	void setV (std::array <long double, 3> p);

	long double getM () const;

private:
	std::array <long double, 3> pos;
	std::array <long double, 3> v;
	const long double m;
};
