#pragma once

#include <iostream>
#include <cassert>
#include <queue>

std::queue<int> q;

void test()
{
	
}

template<typename T>
class Queue
{
private:
	T* data;
	T front;
	T rear;
	int capacity;
	int count;

public:
	explicit Queue() noexcept
		:
		data(new T[1024]),
		front(0),
		rear(-1),
		capacity(1024),
		count(0) {}
	
	~Queue()
	{
		delete[] data;
	}
};