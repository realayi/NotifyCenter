#pragma once
#include <iostream>
using namespace std;  

// ���ڰ�ȫ���ǣ��������ֵ�����Ϊ��ֵ�Ĳ������ᱻ�϶�Ϊ��ֵ��
bool is_r_value(int &&) { std::cout<< "considered as r value" << std::endl; return true; }  
bool is_r_value(const int &) { std::cout<< "not considered as r value" << std::endl;  return false; }  

void test(int && i)  
{  
	bool isRValue = is_r_value(i); // i �����׃������ʹ���������ֵҲ�������J������ֵ��false  
	isRValue = is_r_value(std::move<int&>(i)); // ʹ�� std::move<T>() ȡ����ֵ�� true  
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
	//�ǳ�����ֵ����:ֻ�ܰ󶨵��ǳ�����ֵ�����ܰ󶨵�������ֵ���ǳ�����ֵ�ͳ�����ֵ��
	{
		int a = 5;  
		const int b = 5;  
 		int& v1 = a; // �󶨵��ǳ�����ֵ  
// 		int& v2 = 5; // ������ֵ�� compile error  
// 		int& v3 = b; // ������ֵ�� compile error  
// 		int& v4 = a + b; // �ǳ�����ֵ�� compile error, a + bΪ��ʱ����
	}
	
	//������ֵ����:���԰󶨵��������͵�ֵ�������ǳ�����ֵ��������ֵ���ǳ�����ֵ�ͳ�����ֵ��
	{
		int a = 5;
		const int b = 5;

		const int& v1 = a; // �󶨵��ǳ�����ֵ   
		const int& v2 = 5; // ������ֵ
		const int& v3 = b; // ������ֵ
		const int& v4 = a + b; // �ǳ�����ֵ�� a + bΪ��ʱ����
	}

	//�ǳ�����ֵ����:ֻ�ܰ󶨵��ǳ�����ֵ�����ܰ󶨵��ǳ�����ֵ��������ֵ�ͳ�����ֵ��
	//#hy:????�е�����
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

	//������ֵ����:���԰󶨵��ǳ�����ֵ�ͳ�����ֵ�����ܰ󶨵��ǳ�����ֵ�ͳ�����ֵ
	{
		int a = 5;  
		const int b = 5;  

		const int&& v1 = 5;						//������ֵ
//		const int&& v2 = a; //compile error		//�ǳ�����ֵ
//		const int&& v3 = b; //compile error		//������ֵ
		const int&& v4 = a + b;					//�ǳ�����ֵ
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
