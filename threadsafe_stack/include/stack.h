#pragma once

#include <iostream>
#include <cassert>

template <typename T>
class Stack
{
private:
	T* data;
	T top;
	uint8_t size;
public:
	Stack() : data(new T[1024]), top(0), size(1024) {}

	Stack(int size) : data(new T[size]), top(0), size(size) {}

	Stack(const Stack& other) // shallow copy
	{
		assert(other.data != nullptr);

		data = new T[size];
		size = other.size;

		for (int i = 0; i != size; ++i)
		{
			data[i] = other.data[i];
		}
	}

	Stack& operator=(const Stack& other) // deep copy
	{
		if (&other == this)
		{
			return *this;
		}

		delete[] data;

		if (other.data)
		{
			data = new T[size];

			for (int i = 0; i != size; ++i)
			{
				data[i] = other.data[i];
			}
		}
		else
		{
			data = nullptr;
		}
	}

	~Stack()
	{
		delete[] data;
	}
public:
	void push(const T new_data)
	{
		assert(top <= size);
		data[top++] = new_data;
	}

	T pop()
	{
		assert(top != 0);
		return data[top--];
	}

	T peek() const
	{
		return top;
	}

	bool isEmpty() const
	{
		return top == 0;
	}

	void print() const
	{
		std::cout << "Stack: \n";
		for (int i = 0; i != top; ++i)
		{
			std::cout << data[i] << '\n';
		}
		std::cout << '\n';
	}
};