#pragma once

#include <iostream>
#include <cassert>

#define StackTest 
//#define QuicksortTest

template <typename T>
class Stack
{
private:
	T* data;
	T top;
	int size;
public:
	explicit Stack() noexcept 
		: 
		data(new T[1024]), 
		top(0), 
		size(1024) {}

	explicit Stack(int size) noexcept
		: 
		data(new T[size]), 
		top(0), 
		size(size) {}

	Stack(const Stack& other) noexcept // shallow copy
	{
		assert(other.data != nullptr);

		data = new T[size];
		size = other.size;

		for (int i = 0; i != size; ++i)
		{
			data[i] = other.data[i];
		}
	}

	Stack& operator=(const Stack& other) noexcept // deep copy
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

	Stack operator<=(int data)
	{
		return this.size <= data;
	}


	~Stack()
	{
		delete[] data;
	}
public:
	void push(const T& new_data)
	{
		assert(this->top <= this->size);
		data[top++] = new_data;
	}

	T pop()
	{
		assert(top != 0);
		return data[top--];
	}

	[[nodiscard]] T peek() const noexcept
	{
		return data[top];
	}

	[[nodiscard]] bool isEmpty() const noexcept
	{
		return top == 0;
	}

	[[nodiscard]] size_t getSize() const noexcept
	{
		return size;
	}


	void print() const
	{
		std::cout << "Stack: \n";
		for (int i = 0; i != top; ++i)
		{
			std::cout << data[i] << '\n';
		}
	}
};