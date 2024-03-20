#include "../../inc/utils.h"
#include "gtest/gtest.h"


TEST (TestEuler, RotationNulle)
{
	std::array <long double, 3> vec {3l, 7.1l, -5l};
	EXPECT_EQ (rotationEuler (vec, 0l, 0l, 0l), vec);
}
