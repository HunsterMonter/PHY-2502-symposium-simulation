#include "../inc/Planete.h"
#include <vector>
#include <cmath>


Planete::Planete (long double e, long double a, long double i, long double Omega, long double omegaBar, long double L0, long double mass, long double Mass)
: m (mass)
{
	long double omega = omegaBar - Omega;

	long double E;
	long double beta {e / (1 + std::sqrt (1 - e*e))};
	//long double nu {E + 2 * std::atan (beta * std::sin (E) / (1 - beta * std::cos (E)))}
}

