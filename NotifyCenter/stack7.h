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
	CONT<T> elems; // 元素
public:
	void push(T const&); // push 元素
	void pop(); // pop 元素
	T top() const; // 传回 Stack7 的顶端元素
	bool empty() const { // Stack7 是否为空
		return elems.empty();
	}
	// 赋予一个「元素类型为 T2」的 Stack7
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
	elems.push_back(elem); // 追加元素
}
template<typename T, template <typename,typename> class CONT>
void Stack7<T,CONT>::pop ()
{
	if (elems.empty()) {
			throw std::out_of_range("Stack7<>::pop(): empty Stack7");
	}
	elems.pop_back(); // 移除最后一个元素
}
template <typename T, template <typename,typename> class CONT>
T Stack7<T,CONT>::top () const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack7<>::top(): empty Stack7");
	}
	return elems.back(); // 传回最后一个元素的拷贝
}
template <typename T, template <typename,typename> class CONT>
template <typename T2, template <typename,typename> class CONT2>
Stack7<T,CONT>&
	Stack7<T,CONT>::operator= (Stack7<T2,CONT2> const& op2)
{
	if ((void*)this == (void*)&op2) { // 是否赋值给自己
		return *this;
	}
	Stack7<T2,CONT2> tmp(op2); // 创建 assigned Stack7 的一份拷贝
	elems.clear(); // 移除所有元素
	while (!tmp.empty()) { // 复制所有元素
		elems.push_front(tmp.top());
		tmp.pop();
	}
	return *this;
}
