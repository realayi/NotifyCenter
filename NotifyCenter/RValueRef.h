#pragma once
#include <iostream>
using namespace std;  

// 基于安全考虑，具有名字的声明为右值的参数不会被认定为右值：
bool is_r_value(int &&) { std::cout<< "considered as r value" << std::endl; return true; }  
bool is_r_value(const int &) { std::cout<< "not considered as r value" << std::endl;  return false; }  

void test(int && i)  
{  
	bool isRValue = is_r_value(i); // i 為具名變數，即使被宣告成右值也不會被認定是右值。false  
	isRValue = is_r_value(std::move<int&>(i)); // 使用 std::move<T>() 取得右值。 true  
}

struct X {};  
void inner(const X&) {cout << "inner(const X&)" << endl;}  
void inner(X&&) {cout << "inner(X&&)" << endl;}  
template<typename T>  
void outer(T&& t) {
	cout << typeid(T).name() << endl;
	inner(forward<T>(t));
} 

void TestRValueRef(void)
{
	//非常量左值引用:只能绑定到非常量左值，不能绑定到常量左值、非常量右值和常量右值。
	{
		int a = 5;  
		const int b = 5;  
 		int& v1 = a; // 绑定到非常量左值  
// 		int& v2 = 5; // 常量右值， compile error  
// 		int& v3 = b; // 常量左值， compile error  
// 		int& v4 = a + b; // 非常量右值， compile error, a + b为临时对象
	}
	
	//常量左值引用:可以绑定到所有类型的值，包括非常量左值、常量左值、非常量右值和常量右值。
	{
		int a = 5;
		const int b = 5;

		const int& v1 = a; // 绑定到非常量左值   
		const int& v2 = 5; // 常量右值
		const int& v3 = b; // 常量左值
		const int& v4 = a + b; // 非常量右值， a + b为临时对象
	}

	//非常量右值引用:只能绑定到非常量右值，不能绑定到非常量左值、常量左值和常量右值。
	//#hy:????有点问题
	{
		int a = 5;  
		const int b = 5;  

		int&& v1 = 5;  
// 		int&& v2 = a;   //compile error  
 		int&& v2 = static_cast<int&&>(a);
		v2 = 10;
// 		int&& v3 = b;   //compile error  
// 		int&& v4 = a + b;
		v1 = 7;
		v1 = 8;
	}

	//常量右值引用:可以绑定到非常量右值和常量右值，不能绑定到非常量左值和常量左值
	{
		int a = 5;  
		const int b = 5;  

		const int&& v1 = 5;						//常量右值
//		const int&& v2 = a; //compile error		//非常量左值
//		const int&& v3 = b; //compile error		//常量左值
		const int&& v4 = a + b;					//非常量右值
	}

	{
		int a = 5;
		const int b = 6;
		int c = 7;
//		test(a+b);
		test(100);
		test(a+c);
	}

	{
		int a = 5;
		int& b = static_cast<int&>(a);
		b = 10;
		b = 100;
	}

	{
		int a = 5;  
		int&& b = move(a);
		b = 10;
		X&& c = move(X());
	}

	{
		X a;  
		outer(a);  
		outer(X());  
		inner(forward<X>(X())); 
	}
}
