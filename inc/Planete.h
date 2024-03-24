#ifndef _PLANETE_
#define _PLANETE_

#include "utils.h"
#include <array>
#include <cassert>
#include <ranges>


template <size_t dim>
class Planete
{
public:
	Planete (long double mass, long double Mass, const std::array <long double, 6>& orbitalElements)
	: m (mass) {
		auto&& [e, a, i, Omega, omegaBar, L0] = orbitalElements;

		const long double omega {reduceRange (omegaBar - Omega)};
		const long double M {reduceRange (L0 - omegaBar)};
		const long double E {eccentricAnomaly (M, e, 1e-18)};
		const long double beta {e / (1 + std::sqrt (1 - e*e))};

		const long double nu {E + 2 * std::atan (beta * std::sin (E) / (1 - beta * std::cos (E)))};
		const long double r {a * (1 - e*e) / (1 + e * std::cos (nu))};

		const long double mu {G * (Mass + mass)};
		const long double l {std::sqrt (a * (1 - e*e) * mu)};

		const long double nu_dot {l/(r*r)};
		const long double r_dot {a * (1 - e*e) * e * std::sin (nu) * nu_dot / std::pow (1 + e * std::cos (nu), 2)};

		const std::array <long double, 3> IJK {rotation2D (std::array <long double, 3> {r, 0, 0}, nu)};
		const std::array <long double, 3> IJK_dot {rotation2D (std::array <long double, 3> {r_dot, r*nu_dot, 0}, nu)};

		pos = rotationEuler (IJK, Omega, i, omega);
		v = rotationEuler (IJK_dot, Omega, i, omega);
	}


	template <typename T>
	Planete (long double mass, const T& planetes)
	: m (mass) {
		auto&& [posFromCOM, vFromCOM] = getPosFromCOM (m, planetes);
		pos = posFromCOM;
		v = vFromCOM;
	}


	Planete (long double mass, const std::initializer_list <Planete>& planetes)
	: m (mass) {
		auto&& [posFromCOM, vFromCOM] = getPosFromCOM (m, planetes);
		pos = posFromCOM;
		v = vFromCOM;
	}


	Planete (long double mass, std::array <long double, dim> pos, std::array <long double, dim> v)
	: pos (pos), v (v), m (mass) {}


	std::array <long double, dim> pos;
	std::array <long double, dim> v;
	long double m;

private:
	template <typename T>
	std::tuple <std::array <long double, dim>, std::array <long double, dim>>
	getPosFromCOM (long double M, const T& planetes)
	{
		std::array <long double, dim> posFromCOM = {0};
		std::array <long double, dim> vFromCOM = {0};

		for (auto&& planete : planetes | std::views::as_const)
		{
			posFromCOM -= planete.m * planete.pos / M;
			vFromCOM -= planete.m * planete.v / M;
		}

		return std::make_tuple (posFromCOM, vFromCOM);
	}
};


template <>
Planete <2>::Planete (long double mass, long double Mass, const std::array <long double, 6>& orbitalElements)
: m (mass) {
	auto&& [e, a, i, Omega, omegaBar, L0] = orbitalElements;
	assert ((Omega == 0) && "La longitude du noeud ascendant doit être nulle en 2D");
	assert ((i == 0) && "L'inclinaison doit être nulle en 2D");

	const long double M {reduceRange (L0 - omegaBar)};
	const long double E {eccentricAnomaly (M, e, 1e-18)};
	const long double beta {e / (1 + std::sqrt (1 - e*e))};

	const long double nu {E + 2 * std::atan (beta * std::sin (E) / (1 - beta * std::cos (E)))};
	const long double r {a * (1 - e*e) / (1 + e * std::cos (nu))};

	const long double mu {G * (Mass + mass)};
	const long double l {std::sqrt (a * (1 - e*e) * mu)};

	const long double nu_dot {l/(r*r)};
	const long double r_dot {a * (1 - e*e) * e * std::sin (nu) * nu_dot / std::pow (1 + e * std::cos (nu), 2)};

	pos = rotation2D (std::array <long double, 2> {r, 0}, nu + omegaBar);
	v = rotation2D (std::array <long double, 2> {r_dot, r*nu_dot}, nu + omegaBar);
}

#endif
