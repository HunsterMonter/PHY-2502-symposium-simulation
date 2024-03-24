#ifndef _PLANETE_
#define _PLANETE_

#include "utils.h"
#include <array>
#include <cassert>
#include <concepts>
#include <ranges>


template <std::floating_point T, size_t dim>
class PlaneteCtor {};


template <std::floating_point T, size_t dim>
class Planete
{
public:
	Planete () = default;

	Planete (T mass, T Mass, const std::array <T, 6>& orbitalElements)
	: m (mass) {
		auto&& [position, vitesse] = PlaneteCtor <T, dim>::orbit (mass, Mass, orbitalElements);

		pos = position;
		v = vitesse;
	}


	template <typename U>
	Planete (T mass, const U& planetes)
	: m (mass) {
		auto&& [posCOM, vCOM] = getCOM (planetes);

		pos = -m * posCOM;
		v = -m * vCOM;
	}


	Planete (T mass, const std::initializer_list <Planete>& planetes)
	: m (mass) {
		auto&& [posCOM, vCOM] = getCOM (planetes);

		pos = -posCOM / m;
		v = -vCOM / m;
	}


	Planete (T mass, std::array <T, dim> pos, std::array <T, dim> v)
	: pos (pos), v (v), m (mass) {}


	std::array <T, dim> pos;
	std::array <T, dim> v;
	T m;

private:

	template <typename U>
	std::tuple <std::array <T, dim>, std::array <T, dim>>
	getCOM (const U& planetes)
	{
		std::array <T, dim> posCOM = {0};
		std::array <T, dim> vCOM = {0};

		for (auto&& planete : planetes | std::views::as_const)
		{
			posCOM += planete.m * planete.pos;
			vCOM += planete.m * planete.v;
		}

		return std::make_tuple (posCOM, vCOM);
	}
};


template <std::floating_point T>
class PlaneteCtor <T, 3>
{
public:
	static std::tuple <std::array <T, 3>, std::array <T, 3>>
	orbit (T mass, T Mass, const std::array <T, 6>& orbitalElements)
	{	
		auto&& [e, a, i, Omega, omegaBar, L0] = orbitalElements;

		const T omega {reduceRange <T> (omegaBar - Omega)};
		const T M {reduceRange <T> (L0 - omegaBar)};
		const T E {eccentricAnomaly <T> (M, e, 1e-18)};
		const T beta {e / (1 + std::sqrt (1 - e*e))};

		const T nu {E + 2 * std::atan (beta * std::sin (E) / (1 - beta * std::cos (E)))};
		const T r {a * (1 - e*e) / (1 + e * std::cos (nu))};

		const T G {6.67430e-20}; // kN*km^2/kg^2
		const T mu {G * (Mass + mass)};
		const T l {std::sqrt (a * (1 - e*e) * mu)};

		const T nu_dot {l/(r*r)};
		const T r_dot {a * (1 - e*e) * e * std::sin (nu) * nu_dot / std::pow (1 + e * std::cos (nu), 2)};

		const std::array <T, 3> IJK {rotation2D <T> (std::array <T, 3> {r, 0, 0}, nu)};
		const std::array <T, 3> IJK_dot {rotation2D <T> (std::array <T, 3> {r_dot, r*nu_dot, 0}, nu)};

		std::array <T, 3> xyz {rotationEuler <T> (IJK, Omega, i, omega)};
		std::array <T, 3> xyz_dot {rotationEuler <T> (IJK_dot, Omega, i, omega)};

		return std::make_tuple (xyz, xyz_dot);
	}
};


template <std::floating_point T>
class PlaneteCtor <T, 2>
{
public:
	static std::tuple <std::array <T, 2>, std::array <T, 2>>
	orbit (T mass, T Mass, const std::array <T, 6>& orbitalElements)
	{
		auto&& [e, a, i, Omega, omegaBar, L0] = orbitalElements;
		assert ((Omega == 0) && "La longitude du noeud ascendant doit être nulle en 2D");
		assert ((i == 0) && "L'inclinaison doit être nulle en 2D");

		const T M {reduceRange <T> (L0 - omegaBar)};
		const T E {eccentricAnomaly <T> (M, e, 1e-18)};
		const T beta {e / (1 + std::sqrt (1 - e*e))};

		const T nu {E + 2 * std::atan (beta * std::sin (E) / (1 - beta * std::cos (E)))};
		const T r {a * (1 - e*e) / (1 + e * std::cos (nu))};

		const T G {6.67430e-20}; // kN*km^2/kg^2
		const T mu {G * (Mass + mass)};
		const T l {std::sqrt (a * (1 - e*e) * mu)};

		const T nu_dot {l/(r*r)};
		const T r_dot {a * (1 - e*e) * e * std::sin (nu) * nu_dot / std::pow (1 + e * std::cos (nu), 2)};

		std::array <T, 2> xy {rotation2D <T> (std::array <T, 2> {r, 0}, nu + omegaBar)};
		std::array <T, 2> xy_dot {rotation2D <T> (std::array <T, 2> {r_dot, r*nu_dot}, nu + omegaBar)};

		return std::make_tuple (xy, xy_dot);
	}
};

#endif
