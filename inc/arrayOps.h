#ifndef _ARRAYOPS_
#define _ARRAYOPS_

#include <array>
#include <cstddef>


template <typename T, size_t n>
std::array <T, n>& operator+= (std::array <T, n>& lhs, const std::array <T, n>& rhs)
{
	for (size_t i {0}; i < n; ++i)
	{
		lhs[i] += rhs[i];
	}

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator+ (std::array <T, n> lhs, const std::array <T, n>& rhs)
{
	lhs += rhs;

	return lhs;
}


template <typename T, size_t n>
std::array <T, n>& operator-= (std::array <T, n>& lhs, const std::array <T, n>& rhs)
{
	for (size_t i {0}; i < n; ++i)
	{
		lhs[i] -= rhs[i];
	}

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator- (std::array <T, n> lhs, const std::array <T, n>& rhs)
{
	lhs -= rhs;

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator- (const std::array <T, n>& rhs)
{
	std::array <T, n> lhs = {0};
	lhs -= rhs;

	return lhs;
}


template <typename T, size_t n>
std::array <T, n>& operator*= (std::array <T, n>& lhs, const T& rhs)
{
	for (size_t i {0}; i < n; ++i)
	{
		lhs[i] *= rhs;
	}

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator* (std::array <T, n> lhs, const T& rhs)
{
	lhs *= rhs;

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator* (const T& lhs, std::array <T, n> rhs)
{
	rhs *= lhs;

	return rhs;
}


template <typename T, size_t n>
std::array <T, n>& operator/= (std::array <T, n>& lhs, const T& rhs)
{
	for (size_t i {0}; i < n; ++i)
	{
		lhs[i] /= rhs;
	}

	return lhs;
}


template <typename T, size_t n>
std::array <T, n> operator/ (std::array <T, n> lhs, const T& rhs)
{
	lhs /= rhs;

	return lhs;
}

#endif
