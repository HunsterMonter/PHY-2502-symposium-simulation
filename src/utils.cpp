#include <cmath>
#include "../inc/utils.h"


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
