#pragma once

#include "../include/threadsafe_queue.h"

namespace ThreadsafeQueueTest
{
	template<typename T>
	T randomizer()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist(1, INT8_MAX);

		return dist(rng);
	}


	template <typename T>
	bool inline testPush(Threadsafe_queue<T>& queue)
	{
		for (unsigned i = 0; i != std::thread::hardware_concurrency() - 1; ++i)
		{
			queue.push(randomizer<T>());
		}

		return queue.empty();
	}


	template <typename T>
	std::shared_ptr<T> inline testTryPop(Threadsafe_queue<T>& queue)
	{
		return queue.tryPop();
	}


	template <typename T>
	std::shared_ptr<T> inline testWaitAndPop(Threadsafe_queue<T>& queue)
	{
		return queue.waitAndPop();
	}
}