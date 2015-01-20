#pragma once

#include <deque>
#include <stdexcept>
#include <memory>

template <typename T,
	template <typename ELEM,
	typename = std::allocator<ELEM> >
class CONT = std::deque>
class Stack7 {
private:
	CONT<T> elems; // Ԫ��
public:
	void push(T const&); // push Ԫ��
	void pop(); // pop Ԫ��
	T top() const; // ���� Stack7 �Ķ���Ԫ��
	bool empty() const { // Stack7 �Ƿ�Ϊ��
		return elems.empty();
	}
	// ����һ����Ԫ������Ϊ T2���� Stack7
	template<typename T2,
		template<typename
		ELEM2,
		typename = std::allocator<ELEM2>
	> class CONT2>
	Stack7<T,CONT>& operator= (Stack7<T2,CONT2> const&);
};
template <typename T, template <typename,typename> class CONT>
void Stack7<T,CONT>::push (T const& elem)
{
	elems.push_back(elem); // ׷��Ԫ��
}
template<typename T, template <typename,typename> class CONT>
void Stack7<T,CONT>::pop ()
{
	if (elems.empty()) {
			throw std::out_of_range("Stack7<>::pop(): empty Stack7");
	}
	elems.pop_back(); // �Ƴ����һ��Ԫ��
}
template <typename T, template <typename,typename> class CONT>
T Stack7<T,CONT>::top () const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack7<>::top(): empty Stack7");
	}
	return elems.back(); // �������һ��Ԫ�صĿ���
}
template <typename T, template <typename,typename> class CONT>
template <typename T2, template <typename,typename> class CONT2>
Stack7<T,CONT>&
	Stack7<T,CONT>::operator= (Stack7<T2,CONT2> const& op2)
{
	if ((void*)this == (void*)&op2) { // �Ƿ�ֵ���Լ�
		return *this;
	}
	Stack7<T2,CONT2> tmp(op2); // ���� assigned Stack7 ��һ�ݿ���
	elems.clear(); // �Ƴ�����Ԫ��
	while (!tmp.empty()) { // ��������Ԫ��
		elems.push_front(tmp.top());
		tmp.pop();
	}
	return *this;
}
