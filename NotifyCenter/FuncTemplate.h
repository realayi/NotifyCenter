/*
1.Function templates 可以针对不同的template arguments定义a family of函数
2.Function templates将依照传递而来的自变量(arguments)的类型而被实例化(instantiated)
3.你可以明确指出 templates parameters
4.Function templates可以被重载(overloaded)
5.重载Function templates时，不同的重载形式之间最好只存在[绝对必要的差异]
6.请确保所有形式的重载函数都被写在他们被调用点之前

附加
1.arguments和返回值之类的一定要注意传值和传引用的差异
2.class T是早起写法，可替换为typename T
*/

//template <class T>
template <typename T>
T my_min(T x, T y)
{
	return (x<y) ? x : y;
}

// 传回两个任意类型值的较大者（call-by-reference)
template <typename T>
inline T const& my_max (T const& a, T const& b)
{
	return a < b ? b : a;
}
// 传回三个任意类型值的最大者（call-by-reference)
template <typename T>
inline T const& my_max (T const& a, T const& b, T const& c)
{
	return my_max (my_max(a,b), c); // 当 max(a,b)采用 by value 形式时，此行错误
}
// 传回两个 ints 的较大者
inline int const& my_max (int const& a, int const& b)	//--my_max(3)不可见直接调用my_max(2) template
{
	return a < b ? b : a;
}
// 传回两个 C-style 字符串的较大者（call-by-value)
inline char const* my_max (char const* a, char const* b)
{
	return std::strcmp(a,b) < 0 ? b : a;
}
// 传回三个任意类型值的最大者（call-by-reference)
// template <typename T>
// inline T const& my_max (T const& a, T const& b, T const& c)
// {
// 	return my_max (my_max(a,b), c); // 当 max(a,b)采用 by value 形式时，此行错误
// }

