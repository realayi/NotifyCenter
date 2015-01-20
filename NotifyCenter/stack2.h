#pragma once

#include <deque>
#include <string>
#include <stdexcept>
#include "Stack.h"

template<>
class Stack<std::string> {
private:
	std::deque<std::string> elems; // 元素
public:
	void push(std::string const&); // push 元素
	void pop(); // pop 元素
	std::string top() const; // 传回 stack 最顶端元素
	bool empty() const { // stack 是否为空
		return elems.empty();
	}
};

void Stack<std::string>::push (std::string const& elem)
{
	elems.push_back(elem); // 追加元素
}
void Stack<std::string>::pop ()
{
	if (elems.empty()) {
			throw std::out_of_range("Stack<std::string>::pop(): empty stack");
	}
	elems.pop_back(); // 移除最后一个元素
}
std::string Stack<std::string>::top () const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack<std::string>::top(): empty stack");
	}
	return elems.back(); // 传回最后一个元素的拷贝
}
