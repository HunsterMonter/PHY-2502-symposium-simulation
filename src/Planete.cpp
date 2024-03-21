#include "Planete.h"
#include "utils.h"
#include <vector>
#include <cmath>

constexpr long double G {6.67430e-11};


Planete::Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double mass, long double Mass)
: m (mass)
{
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

	const std::array <long double, 3> IJK {rotationEuler (std::array <long double, 3> {r, 0, 0}, nu, 0, 0)};
	const std::array <long double, 3> IJK_dot {rotationEuler (std::array <long double, 3> {r_dot, r*nu_dot, 0}, nu, 0, 0)};

	pos = rotationEuler (IJK, Omega, i, omega);
	v = rotationEuler (IJK_dot, Omega, i, omega);
}

