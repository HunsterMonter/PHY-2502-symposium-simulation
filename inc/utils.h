#ifndef _UTILS_
#define _UTILS_

#include "arrayOps.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>

/*
const T G {6.67430e-11};
const T pi {std::numbers::pi_v <long double>};
const T root2 {std::numbers::sqrt2_v <long double>};
const T root3 {std::numbers::sqrt3_v <long double>};
const T r2s2 {root2 / 2};
const T r3s2 {root3 / 2};
*/

template <std::floating_point T>
constexpr T max_err (T num1, T num2, T epsillon)
{
	T err = std::max (std::abs (num1), std::abs (num2)) * epsillon;

	return err;
}


template <std::floating_point T>
constexpr std::array <T, 2> rotation2D (const std::array <T, 2>& vecteur, T theta)
{
	auto&& [x, y] = vecteur;

	const T c {std::cos (theta)};
	const T s {std::sin (theta)};

	return std::array <T, 2> {c*x-s*y, s*x+c*y};
}


template <std::floating_point T>
constexpr std::array <T, 3> rotation2D (const std::array <T, 3>& vecteur, T theta)
{
	auto&& [I, J, z] = vecteur;
	auto&& [x, y] = rotation2D <T> (std::array <T, 2> {I, J}, theta);

	return std::array <T, 3> {x, y, z};
}


template <std::floating_point T>
constexpr std::array <T, 3> rotationEuler (const std::array <T, 3>& vecteur, T Omega, T i, T omega)
{
	auto&& [I, J, K] = vecteur;

	const T cW {std::cos (Omega)};
	const T sW {std::sin (Omega)};
	const T cw {std::cos (omega)};
	const T sw {std::sin (omega)};
	const T ci {std::cos (i)};
	const T si {std::sin (i)};

	const T x = (cW*cw - sW*ci*sw)*I + (-cW*sw - sW*ci*cw)*J + sW*si*K;
	const T y = (sW*cw + cW*ci*sw)*I + (cW*ci*cw - sW*sw)*J  - cW*si*K;
	const T z = si*sw*I + si*cw*J + ci*K;

	return std::array <T, 3> {x, y, z};
}


template <std::floating_point T>
constexpr T eccentricAnomaly (T M, T e, T epsillon)
{
	const T pi {std::numbers::pi_v <long double>};

	T E_prev {pi};
	T E_next {0};
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

template <std::floating_point T>
constexpr T reduceRange (T ang)
{
	const T pi {std::numbers::pi_v <long double>};
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


// Calcul de la force divisée par les deux masses entre la paire de planètes
template <std::floating_point T>
std::array <T, 3> force (std::array <T, 3> pos1, const std::array <T, 3>& pos2)
{
	// Vecteur r de pos2 à pos1
	pos1 -= pos2;
	const T G {6.67430e-20}; // kN*km^2/kg^2
	const T r3 {std::pow (std::hypot (pos1[0], pos1[1], pos1[2]), 3)};

	return -G * pos1 / (2 * r3);
}


template <std::floating_point T>
std::array <T, 2> force (std::array <T, 2> pos1, const std::array <T, 2>& pos2)
{
	// Vecteur r de pos2 à pos1
	pos1 -= pos2;
	const T G {6.67430e-11};
	const T r3 {std::pow (std::hypot (pos1[0], pos1[1]), 3)};

	return -G * pos1 / (2 * r3);
}


//template <size_t n, size_t m>
//void printSim (std::string filename, std::array <std::array <Planete, m>, n> sim, std::array <std::string, m> nomsPlanetes, epsillon)


#endif
