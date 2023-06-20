#pragma once
#include "stack.h"

#include <thread>
#include <mutex>

#include <vector>
#include <stack>

#include <fstream>

#include <algorithm>

template<typename T>
class Threadsafe_stack
{
private:
#ifdef StackTest
	Stack<T> data;
#endif
#ifdef QuicksortTest
	std::stack<T> data;
#endif
	mutable std::mutex mt;
private:
	friend std::ostream& operator<<(std::ostream& os, std::stack<T> stack);

public:
	Threadsafe_stack() : data() {}

	Threadsafe_stack(const Threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(mt);
		data = other.data;
	}

	Threadsafe_stack& operator=(const Threadsafe_stack&) = delete;
	~Threadsafe_stack() = default;
public:
	void push(T new_data)
	{
		std::lock_guard<std::mutex> lock(mt);
		data.push(std::move(new_data));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(mt);
#ifdef StackTest
		std::shared_ptr<T> res(std::make_shared<T>(std::move(data.peek())));
#endif
#ifdef QuicksortTest
		std::shared_ptr<T> res(std::make_shared<T>(std::move(data.top())));
#endif
		data.pop();
		return res;
	}

	bool isEmpty() const
	{
		std::lock_guard<std::mutex> lock(mt);
		return data.isEmpty();
	}

#ifdef StackTest
	void print() const
	{
		std::lock_guard<std::mutex> lock(mt);
		data.print();
	}
#endif

#ifdef QuicksortTest
	void print() const
	{
		std::lock_guard<std::mutex> lock(mt);
		std::cout << data;
	}
#endif

};

#ifdef QuicksortTest
template<typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> stack) //function header
{
	while (!stack.empty()) //body
	{
		os << stack.top() << '\n';
		stack.pop();
	}

	return os; // end of function
}
#endif