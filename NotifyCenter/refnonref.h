#pragma once

#include <typeinfo>
#include <iostream>

template <typename T>
void ref(T const& x)
{
	std::cout << "x is ref(T const&):"
		<< typeid(x).name() << std::endl;
}

template <typename T>
void nonref(T x)
{
	std::cout << "x is nonref(T):"
		<< typeid(x).name() << std::endl;
}

