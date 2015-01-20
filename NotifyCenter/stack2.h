#pragma once

#include <deque>
#include <string>
#include <stdexcept>
#include "Stack.h"

template<>
class Stack<std::string> {
private:
	std::deque<std::string> elems; // Ԫ��
public:
	void push(std::string const&); // push Ԫ��
	void pop(); // pop Ԫ��
	std::string top() const; // ���� stack ���Ԫ��
	bool empty() const { // stack �Ƿ�Ϊ��
		return elems.empty();
	}
};

void Stack<std::string>::push (std::string const& elem)
{
	elems.push_back(elem); // ׷��Ԫ��
}
void Stack<std::string>::pop ()
{
	if (elems.empty()) {
			throw std::out_of_range("Stack<std::string>::pop(): empty stack");
	}
	elems.pop_back(); // �Ƴ����һ��Ԫ��
}
std::string Stack<std::string>::top () const
{
	if (elems.empty()) {
		throw std::out_of_range("Stack<std::string>::top(): empty stack");
	}
	return elems.back(); // �������һ��Ԫ�صĿ���
}
