#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
private:
	std::vector<T> elems;	//元素
public:
	Stack();
	void push(T const&);	//push元素
	void pop(void);			//pop元素
	T top(void) const;		//传回最顶端元素
	bool empty(void) const	//stack是否为空
	{
		return elems.empty();
	}

	//Stack(Stack<T> const&);					//拷贝构造
	//Stack<T>& operator==(Stack<T> const&);	//assignment操作符
};

template <typename T>
Stack<T>::Stack()
{

}

template <typename T>
void Stack<T>::push( T const& elem)
{
	elems.push_back(elems);
}

template <typename T>
void Stack<T>::pop()
{
	if (elems.empty())
	{
		throw std::out_of_range("stack<>::top empty stack");
	}

	elems.pop_back();
}

template <typename T>
T Stack<T>::top() const
{
	if (elems.empty())
	{
		throw std::out_of_range("stack<>::top empty stack");
	}

	return elems.back();
}
