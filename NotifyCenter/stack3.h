#pragma once

#include <vector>
#include <stdexcept>

template <typename T, typename CONT = std::vector<T> >
class Stack_2 {
private:
	CONT elems; // 元素
public:
	void push(T const&); // push 元素
	void pop(); // pop 元素
	T top() const; // 传回 Stack_2 的顶端元素
	bool empty() const { // Stack_2 是否为空
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
	if ((void*)this == (void*)&op2)			//判断是否自己
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
	elems.push_back(elem); // 追加元素
}
template <typename T, typename CONT>
void Stack_2<T,CONT>::pop()
{
	if (elems.empty()) {
		throw std::out_of_range("Stack_2<>::pop(): empty Stack_2");
	}
	elems.pop_back(); // 移除最后一个元素
}
template <typename T, typename CONT>
T Stack_2<T,CONT>::top() const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack_2<>::top(): empty Stack_2");
	}
	return elems.back(); // 传回最后一个元素的拷贝
}
