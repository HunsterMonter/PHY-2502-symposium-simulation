#include <cmath>
#include "utils.h"


std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double, i, long double omega)
{
	auto[i, j, k] = vecteur;

	long double cW {std::cos (Omega)};
	long double sW {std::sin (Omega)};
	long double cw {std::cos (omega)};
	long double cw {std::sin (omega)};
	long double ci {std::cos (i)};
	long double ci {std::sin (i)};

	long double x = (cW*cw - sW*ci*sw)*i + (-cW*sw - sW*ci*cw)*j + sW*si*k;
	long double y = (sW*cw + cW*ci*sw)*i + (cW*ci*cw - sW*sw)*j  - cW*si*k;
	long double z = si*sw*i + si*cw*j + ci*k;

	return std::array <long double, 3> {x, y, z}
}
