#pragma once

#include <iostream>
using namespace std;

template <typename T1, typename T2>
class myClass
{
private:
	T1 t1;
	T2 t2;
public:
	myClass(T1 a, T2 b);
	void show(void);
};

template <typename T1, typename T2>
myClass<T1, T2>::myClass( T1 a, T2 b )
	: t1(a)
	, t2(b)
{
}

template <typename T1, typename T2>
void myClass<T1, T2>::show( void )
{
	cout << "t1=" << t1 << " t2=" << t2 << endl;
}



