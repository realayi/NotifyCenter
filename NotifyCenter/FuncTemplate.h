/*
1.Function templates ������Բ�ͬ��template arguments����a family of����
2.Function templates�����մ��ݶ������Ա���(arguments)�����Ͷ���ʵ����(instantiated)
3.�������ȷָ�� templates parameters
4.Function templates���Ա�����(overloaded)
5.����Function templatesʱ����ͬ��������ʽ֮�����ֻ����[���Ա�Ҫ�Ĳ���]
6.��ȷ��������ʽ�����غ�������д�����Ǳ����õ�֮ǰ

����
1.arguments�ͷ���ֵ֮���һ��Ҫע�⴫ֵ�ʹ����õĲ���
2.class T������д�������滻Ϊtypename T
*/

//template <class T>
template <typename T>
T my_min(T x, T y)
{
	return (x<y) ? x : y;
}

// ����������������ֵ�Ľϴ��ߣ�call-by-reference)
template <typename T>
inline T const& my_max (T const& a, T const& b)
{
	return a < b ? b : a;
}
// ����������������ֵ������ߣ�call-by-reference)
template <typename T>
inline T const& my_max (T const& a, T const& b, T const& c)
{
	return my_max (my_max(a,b), c); // �� max(a,b)���� by value ��ʽʱ�����д���
}
// �������� ints �Ľϴ���
inline int const& my_max (int const& a, int const& b)	//--my_max(3)���ɼ�ֱ�ӵ���my_max(2) template
{
	return a < b ? b : a;
}
// �������� C-style �ַ����Ľϴ��ߣ�call-by-value)
inline char const* my_max (char const* a, char const* b)
{
	return std::strcmp(a,b) < 0 ? b : a;
}
// ����������������ֵ������ߣ�call-by-reference)
// template <typename T>
// inline T const& my_max (T const& a, T const& b, T const& c)
// {
// 	return my_max (my_max(a,b), c); // �� max(a,b)���� by value ��ʽʱ�����д���
// }

