#pragma once
#include "stack.h"

#include <thread>
#include <mutex>

#include <vector>
#include <stack>

#include <algorithm>

template<typename T>
class Threadsafe_stack
{
private:
	Stack<T> data;
	mutable std::mutex mt;
public:
	Threadsafe_stack() = default;

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
		std::shared_ptr<T> res(std::make_shared<T>(std::move(data.peek())));
		data.pop();
		return res;
	}

	bool isEmpty() const
	{
		std::lock_guard<std::mutex> lock(mt);
		return data.isEmpty();
	}

	void print() const
	{
		std::lock_guard<std::mutex> lock(mt);
		data.print();
	}
};