#ifndef _UTILS_
#define _UTILS_

#include "arrayOps.h"
#include <array>
#include <cmath>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>

constexpr long double G {6.67430e-11};
constexpr long double pi {std::numbers::pi_v <long double>};
constexpr long double root2 {std::numbers::sqrt2_v <long double>};
constexpr long double root3 {std::numbers::sqrt3_v <long double>};
constexpr long double r2s2 {root2 / 2};
constexpr long double r3s2 {root3 / 2};


constexpr std::array <long double, 2>
rotation2D (const std::array <long double, 2>& vecteur, long double theta)
{
	auto&& [x, y] = vecteur;

	const long double c {std::cos (theta)};
	const long double s {std::sin (theta)};

	return std::array <long double, 2> {c*x-s*y, s*x+c*y};
}


constexpr std::array <long double, 3>
rotation2D (const std::array <long double, 3>& vecteur, long double theta)
{
	auto&& [I, J, z] = vecteur;
	auto&& [x, y] = rotation2D (std::array <long double, 2> {I, J}, theta);

	return std::array <long double, 3> {x, y, z};
}


constexpr std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double i, long double omega)
{
	auto&& [I, J, K] = vecteur;
	/*
	const long double I = vecteur[0];
	const long double J = vecteur[1];
	const long double K = vecteur[2];
	*/

	const long double cW {std::cos (Omega)};
	const long double sW {std::sin (Omega)};
	const long double cw {std::cos (omega)};
	const long double sw {std::sin (omega)};
	const long double ci {std::cos (i)};
	const long double si {std::sin (i)};

	const long double x = (cW*cw - sW*ci*sw)*I + (-cW*sw - sW*ci*cw)*J + sW*si*K;
	const long double y = (sW*cw + cW*ci*sw)*I + (cW*ci*cw - sW*sw)*J  - cW*si*K;
	const long double z = si*sw*I + si*cw*J + ci*K;

	return std::array <long double, 3> {x, y, z};
}


constexpr long double
eccentricAnomaly (long double M, long double e, long double epsillon)
{
	long double E_prev {pi};
	long double E_next {0};
	const size_t n_max {1000};

	for (size_t i {0}; i < n_max; ++i)
	{
		E_next = M + e * std::sin (E_prev);

		if (std::abs (E_next-E_prev) < epsillon)
		{
			return M + e * std::sin (E_next);
		}
		E_prev = E_next;
	}

	return NAN;
}

constexpr long double
reduceRange (long double ang)
{
	const int tours {static_cast <int> (ang / (2*pi))};

	if (tours == 0)
	{
		return ang;
	}
	else if (tours > 0)
	{
		return ang - 2*pi*tours;
	}
	else
	{
		return ang + 2*pi*(-tours+1);
	}
}


//template <size_t n, size_t m>
//void printSim (std::string filename, std::array <std::array <Planete, m>, n> sim, std::array <std::string, m> nomsPlanetes, epsillon)


#endif
