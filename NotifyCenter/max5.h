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

//���ز�������ģ����Ƶ�
//[�Զ�����ת��]ֻ�ʺ��ڳ��溯������templates�в��迼��
//non-template����ת������
std::string const& max_5(std::string const& a, std::string const&b)
{
	return a < b ? b : a;
}
