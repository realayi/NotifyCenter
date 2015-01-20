#pragma once

#include <string>

template <typename T>
inline T const& max_5(T const& a, T const& b)
{
	return a < b ? b : a;
}

template <typename T>
inline T max_6(T a, T b)
{
	return a < b ? b : a;
}

template <typename T, int N, int M>
T const* max_5(T const(&a)[N], T const (&b)[M])
{
	return a < b ? b : a;
}

//重载并不是走模板的推导
//[自动类型转化]只适合于常规函数，在templates中不予考虑
//non-template函数转化参数
std::string const& max_5(std::string const& a, std::string const&b)
{
	return a < b ? b : a;
}
