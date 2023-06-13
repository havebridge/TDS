#pragma once

#include "../include/thread_pool.h"

using namespace HQ;

namespace QueueTest
{
	template<typename T>
	inline void testPush(Queue<T>& a)
	{
		a.Enqueue(2);
		a.Enqueue(1);
		a.Enqueue(51);
		a.Enqueue(4);
		std::cout << '\n';
	}

	template<typename T>
	inline void testPrint(Queue<T>& a)
	{
		a.print();
	}


	template<typename T>
	inline void testPop(Queue<T>& a)
	{
		a.Dequeue();
		a.Dequeue();
		a.Dequeue();
		std::cout << '\n';
	}
}