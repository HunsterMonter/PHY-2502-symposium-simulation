#include <array>
#include <cmath>
#include <numbers>


constexpr std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double i, long double omega)
{
	auto[I, J, K] = vecteur;

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
	const long double pi {std::numbers::pi_v <long double>};
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


constexpr long double
reduceRange (long double ang)
{
	const long double pi {std::numbers::pi_v <long double>};
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
