// NotifyCenter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <string>
#include <functional>

#include "ClassTemplate.h"
#include "FuncTemplate.h"
#include "Stack.h"
#include "stack2.h"
#include "stack3.h"
#include "stack7.h"
#include "max5.h"
#include "refnonref.h"
#include "NotifyCenter.h"
#include "RValueRef.h"
#include "PostCmdEx.h"

using std::cout;
using std::endl;

void func1111(std::string& str1, const std::string& str2)
{
	std::string str3 = str1;
	str3.append(str2);
}

void func0(void)
{
	int i = 0;
	int j = ++i;
}

void funcInt(int a)
{
	int i = a;
	int j = ++i;
}
void funcInt2(int& a)
{
	int i = a;
	int j = ++i;
}

void funcIntRef(int& a)
{
	int i = a;
	int j = ++i;
	++a;
}

void funcIntCRef(const int& a)
{
	int i = a;
	int j = ++i;
}

class IntAdd
{
public:
	void AddOne(int a)
	{
		a++;
	}
	void AddTwo(int a, int b)
	{
		a++;
		b++;
	}
	void AddThree(int a, int b, int c)
	{
		a++;
		b++;
		c++;
	}
};

using namespace std::placeholders;

int _tmain(int argc, _TCHAR* argv[])
{
//	std::placeholders::_1

	std::string str111 = "1111";
	func1111(str111, "22222");
	int n1 = 2;
	int n2 = 10;
	double d1 = 1.5;
	double d2 = 3.2;
	cout << "较小整数" << my_min(n1, n2) << endl;
	cout << "较小实数" << my_min(d1, d2) << endl;
	my_max(7, 42, 68); // OK
	
	std::string s;
//	max_5("apple","peach"); // OK：类型相同 -->编译不过，返回值被认为不对
	max_5<const char*>("apple","peach");	//OK	-->算主动退化
//	max_5("apple","tomato"); // ERROR：类型不同
	max_5<char, 6, 7>("apple","tomato");
	max_5("apple",s); // ERROR：类型不同 --> OK:如果用string重载函数

	max_6("apple","tomato"); // OK：自变量在推导的时候，传参不是ref时可以发生退化[array->point]
//	max_6("apple",s); // ERROR：类型不同

	//--------准则一：
	//虽然可以调用到int的函数，但是将重载函数都写在被调用的前面是应遵守的
	const char* s1 = "frederic";
	const char* s2 = "anica";
	const char* s3 = "lucas";
	const char* s4 = my_max(s1, s2, s3); // ERROR
	//--------准则二：
	//虽然可以编译过，但传值和传引用引起的模糊是要避免的,细微的重载规则引发的非预期行为

//	temp_min(n1, d2);	--编译不过
	my_min<double>(n1, d2);	// --指明参数类型 ok

	myClass<int,int> class1(3, 5);
	class1.show();

	myClass<int,char> class2(3, 'a');
	class2.show();

	myClass<double,int> class3(1.1, 100);
	class3.show();

	Stack<Stack<int>> intStackStack;
	Stack<std::string> strStack;
	strStack.push("1234");

	Stack_2<int> intStack;
	Stack_2<int, std::deque<int> > intDequeStack;
	Stack_2<double> doubleVectorStack;
	intDequeStack = doubleVectorStack;
	Stack_2<int> intStack2 = doubleVectorStack;

	Stack7<int, std::vector> intStack7;
	intStack7.push(1);
	intStack7.push(3);
	intStack7.push(5);
	std::cout << intStack7.top() << std::endl;

	int nnnn = int();
	bool bbbbb = bool();

	ref("hello");
	nonref("hello");

	std::function<void(void)> a = func0;
//	auto stWrapped = wrapped0(a);
	std::function<void(int)> b = funcInt;
//	auto stWrapped1 = wrapped1<int>(b);
	std::function<void(int&)> c = funcIntRef;

// 	std::function<void(int)> d = NC::bind(funcInt2, _1);
// 	d(1000);

//	std::cout << typeid(d).name() << std::endl;
//	std::cout << typeid(NC::bind(funcInt2, _1)).name() << std::endl;

// 	g_objEventMgr.AddListener(100, a);
// 	g_objEventMgr.AddListener(100, NC::bind(&func0));
// 	g_objEventMgr.AddListener(101, NC::bind(b, NC::arg<int>(1)));
 	g_objEventMgr.AddListener(101, NC::bind(&funcIntRef, NC::argref<int>(1)));
// 	
// 	IntAdd addObj;
// 	g_objEventMgr.AddListener(101, NC::bind(&IntAdd::AddOne, &addObj, NC::arg<int>(1)));
// 	g_objEventMgr.AddListener(101, NC::bind(&IntAdd::AddTwo, &addObj, NC::arg<int>(1), NC::arg<int>(2)));
// 	g_objEventMgr.AddListener(101, NC::bind(&IntAdd::AddThree,
// 		&addObj, NC::arg<int>(1), NC::arg<int>(2), NC::arg<int>(3)));

	g_objEventMgr.AddListener(101, NC::bind(&funcIntCRef, NC::argcref<int>(1)));

//	g_objCmdMgr.AddListener(1, d);
//	g_objCmdMgr.AddListener(1, NC::bind(funcInt2, _1));

//	NotifyMsg0(100);
	NotifyMsg1(101, 100000);
//	NotifyMsg1(1, 1, 2);
//	NotifyMsg1(1, 1.2f);

// 	g_objCmdMgr.AddListener(2, c);
// 	NotifyMsg1(2, 100);

//	std::function<void(void)> fVoid = NC::bind(funcInt2, arg<int>());
//	std::function<void(int&)> fVoid = NC::bind(funcInt2, _1);
//	fVoid();
//	std::_Nil

	TestRValueRef();

// 	g_objCmdMgr.AddListener(100, postcmdex::bind(&funcIntRef, postcmdex::argref<int>()));
// 	PostCmdEx(100, 1000000);

	system("Pause");
	return 0;
}

