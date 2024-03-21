#pragma once
#include <array>


constexpr std::array <long double, 3>
rotationEuler (const std::array <long double, 3>& vecteur, long double Omega, long double i, long double omega);

constexpr long double
eccentricAnomaly (long double M, long double e, long double epsillon);

constexpr long double
reduceRange (long double ang);

#include "../src/utils.cpp"
