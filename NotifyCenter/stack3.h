#pragma once

#include <vector>
#include <stdexcept>

template <typename T, typename CONT = std::vector<T> >
class Stack_2 {
private:
	CONT elems; // Ԫ��
public:
	void push(T const&); // push Ԫ��
	void pop(); // pop Ԫ��
	T top() const; // ���� Stack_2 �Ķ���Ԫ��
	bool empty() const { // Stack_2 �Ƿ�Ϊ��
			return elems.empty();
	}

	Stack_2();

	template <typename T2, typename CONT2>
	Stack_2(Stack_2<T2,CONT2> const& obj);

	template <typename T2, typename CONT2>
	Stack_2<T,CONT>& operator=(Stack_2<T2,CONT2> const&);

};

template <typename T, typename CONT /*= std::vector<T> */>
Stack_2<T, CONT>::Stack_2()
{
}

template <typename T, typename CONT>
	template <typename T2, typename CONT2>
Stack_2<T,CONT>::Stack_2( Stack_2<T2,CONT2> const& obj)
{
}

template <typename T, typename CONT>
	template <typename T2, typename CONT2>
Stack_2<T,CONT>& Stack_2<T,CONT>::operator=( Stack_2<T2,CONT2> const& op2)
{
	if ((void*)this == (void*)&op2)			//�ж��Ƿ��Լ�
	{
		return *this;
	}

	Stack_2<T2,CONT2> tmp(op2);
	elems.clear();
	while (!tmp.empty())
	{
		elems.push_back((T)tmp.top());
		tmp.pop();
	}
	
	return *this;
}

template <typename T, typename CONT>
void Stack_2<T,CONT>::push (T const& elem)
{
	elems.push_back(elem); // ׷��Ԫ��
}
template <typename T, typename CONT>
void Stack_2<T,CONT>::pop()
{
	if (elems.empty()) {
		throw std::out_of_range("Stack_2<>::pop(): empty Stack_2");
	}
	elems.pop_back(); // �Ƴ����һ��Ԫ��
}
template <typename T, typename CONT>
T Stack_2<T,CONT>::top() const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack_2<>::top(): empty Stack_2");
	}
	return elems.back(); // �������һ��Ԫ�صĿ���
}
