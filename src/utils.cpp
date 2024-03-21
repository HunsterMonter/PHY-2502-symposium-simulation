#include <cmath>
#include <numbers>
#include "../inc/utils.h"

const long double pi {std::numbers::pi_v <long double>};


std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double i, long double omega)
{
	auto[I, J, K] = vecteur;

	long double cW {std::cos (Omega)};
	long double sW {std::sin (Omega)};
	long double cw {std::cos (omega)};
	long double sw {std::sin (omega)};
	long double ci {std::cos (i)};
	long double si {std::sin (i)};

	long double x = (cW*cw - sW*ci*sw)*I + (-cW*sw - sW*ci*cw)*J + sW*si*K;
	long double y = (sW*cw + cW*ci*sw)*I + (cW*ci*cw - sW*sw)*J  - cW*si*K;
	long double z = si*sw*I + si*cw*J + ci*K;

	return std::array <long double, 3> {x, y, z};
}


long double
eccentricAnomaly (long double M, long double e, long double epsillon)
{
	long double E_prev {pi};
	long double E_next {0};

	while (true)
	{
		E_next = M + e * std::sin (E_prev);

		if (std::abs (E_next-E_prev) < epsillon)
		{
			return E_next;
		}
		else
		{
			E_prev = E_next;
		}
	}
}
