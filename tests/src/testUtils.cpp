#include "../../inc/utils.h"
#include "gtest/gtest.h"
#include <algorithm>
#include <cmath>
#include <numbers>
#include <numeric>
#include <ranges>


const long double r3s2 {std::sqrt (static_cast <long double> (3))/2};
const long double r2s2 {std::sqrt (static_cast <long double> (2))/2};
const long double pi {std::numbers::pi_v <long double>};


TEST (TestEuler, RotationNulle)
{
	std::array <long double, 3> vec {3, 7.1, -5};
	EXPECT_EQ (rotationEuler (vec, 0, 0, 0), vec);
}


TEST (TestEuler, Omega30)
{
	std::array <long double, 3> I {1, 0, 0};
	std::array <long double, 3> J {0, 1, 0};
	std::array <long double, 3> K {0, 0, 1};

	std::array <long double, 3> x {rotationEuler (I, pi*30/180, 0, 0)};
	std::array <long double, 3> y {rotationEuler (J, pi*30/180, 0, 0)};
	std::array <long double, 3> z {rotationEuler (K, pi*30/180, 0, 0)};

	std::array <long double, 3> xE {r3s2, 0.5, 0};
	std::array <long double, 3> yE {-0.5, r3s2, 0};
	std::array <long double, 3> zE {K};

	for (auto&& [i, Ei] : std::views::zip (x, xE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (y, yE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (z, zE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
}


TEST (TestEuler, I30)
{
	std::array <long double, 3> I {1, 0, 0};
	std::array <long double, 3> J {0, 1, 0};
	std::array <long double, 3> K {0, 0, 1};

	std::array <long double, 3> x {rotationEuler (I, 0, pi*30/180, 0)};
	std::array <long double, 3> y {rotationEuler (J, 0, pi*30/180, 0)};
	std::array <long double, 3> z {rotationEuler (K, 0, pi*30/180, 0)};

	std::array <long double, 3> xE {I};
	std::array <long double, 3> yE {0, r3s2, 0.5};
	std::array <long double, 3> zE {0, -0.5, r3s2};

	for (auto&& [i, Ei] : std::views::zip (x, xE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (y, yE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (z, zE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
}


TEST (TestEuler, omega30)
{
	std::array <long double, 3> I {1, 0, 0};
	std::array <long double, 3> J {0, 1, 0};
	std::array <long double, 3> K {0, 0, 1};

	std::array <long double, 3> x {rotationEuler (I, 0, 0, pi*30/180)};
	std::array <long double, 3> y {rotationEuler (J, 0, 0, pi*30/180)};
	std::array <long double, 3> z {rotationEuler (K, 0, 0, pi*30/180)};

	std::array <long double, 3> xE {r3s2, 0.5, 0};
	std::array <long double, 3> yE {-0.5, r3s2, 0};
	std::array <long double, 3> zE {K};

	for (auto&& [i, Ei] : std::views::zip (x, xE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (y, yE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (z, zE))
	{
		EXPECT_LT (std::abs (i-Ei), 1e-19l);
	}
}


TEST (TestEuler, Omega45I30omega270)
{
	std::array <long double, 3> I {1, 0, 0};
	std::array <long double, 3> J {0, 1, 0};
	std::array <long double, 3> K {0, 0, 1};

	std::array <long double, 3> x {rotationEuler (I, pi*45/180, pi*30/180, pi*270/180)};
	std::array <long double, 3> y {rotationEuler (J, pi*45/180, pi*30/180, pi*270/180)};
	std::array <long double, 3> z {rotationEuler (K, pi*45/180, pi*30/180, pi*270/180)};

	std::array <long double, 3> xE {r2s2*r3s2, -r2s2*r3s2, -0.5};
	std::array <long double, 3> yE {r2s2, r2s2, 0};
	std::array <long double, 3> zE {0.5*r2s2, -0.5*r2s2 , r3s2};

	for (auto&& [i, Ei] : std::views::zip (x, xE))
	{
		EXPECT_LT (std::abs (i-Ei), 2e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (y, yE))
	{
		EXPECT_LT (std::abs (i-Ei), 2e-19l);
	}
	for (auto&& [i, Ei] : std::views::zip (z, zE))
	{
		EXPECT_LT (std::abs (i-Ei), 2e-19l);
	}
}


TEST (TestAnomalieExcentrique, Excentricy)
{
	std::array <long double, 10> e_vec;
	std::ranges::generate (e_vec, [n=0, size=e_vec.size ()]() mutable {return static_cast <long double> (n++)/(size-1);});

	long double epsillon {1e-9};
	long double E {pi/3};
	long double E_calc;
	long double M;

	for (auto&& e : e_vec | std::views::as_const)
	{
		M = E - e * std::sin (E);
		E_calc = eccentricAnomaly (M, e, epsillon);
		EXPECT_LT (std::abs (E-E_calc), epsillon);
	}
}


TEST (TestAnomalieExcentrique, EccentricAnomaly)
{
	std::array <long double, 10> E_vec;
	std::ranges::generate (E_vec, [n=0, size=E_vec.size ()]() mutable {return static_cast <long double> (n++)*2*pi/(size);});

	long double epsillon {1e-9};
	long double e {0.2};
	long double E_calc;
	long double M;

	for (auto&& E : E_vec | std::views::as_const)
	{
		M = E - e * std::sin (E);
		E_calc = eccentricAnomaly (M, e, epsillon);
		EXPECT_LT (std::abs (E-E_calc), epsillon);
	}
}


TEST (TestAnomalieExcentrique, Precision)
{
	std::array <long double, 10> epsillon_vec;
	std::ranges::generate (epsillon_vec, [n=0, size=epsillon_vec.size ()]() mutable {return std::pow (10, static_cast <long double> (n--)-8);});

	long double E {1e-9};
	long double E_calc;
	long double e {0.2};
	long double M;

	for (auto&& epsillon : epsillon_vec | std::views::as_const)
	{
		M = E - e * std::sin (E);
		E_calc = eccentricAnomaly (M, e, epsillon);
		EXPECT_LT (std::abs (E-E_calc), epsillon);
	}
}
