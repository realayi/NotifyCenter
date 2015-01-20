#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Stack
{
private:
	std::vector<T> elems;	//Ԫ��
public:
	Stack();
	void push(T const&);	//pushԪ��
	void pop(void);			//popԪ��
	T top(void) const;		//�������Ԫ��
	bool empty(void) const	//stack�Ƿ�Ϊ��
	{
		return elems.empty();
	}

	//Stack(Stack<T> const&);					//��������
	//Stack<T>& operator==(Stack<T> const&);	//assignment������
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
