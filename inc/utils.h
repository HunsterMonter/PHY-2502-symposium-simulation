#pragma once
#include <array>


std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double i, long double omega);

long double
eccentricAnomaly (long double M, long double e, long double epsillon);
