#pragma once

#include "../include/quicksort.h"

namespace QuicksortTest
{
	template<typename T>
	inline std::list<T> test(std::list<T>& data_to_sort)
	{
		if (data_to_sort.empty())
		{
			return data_to_sort;
		}

		Quicksort<T> q;

		return q.do_sort(data_to_sort);
	}

	template<typename T>
	inline void example()
	{
		std::list<T> data;

		for (T i = 5; i != 0; --i)
		{
			data.push_back(i);
		}

		std::list<T> a = QuicksortTest::test<T>(data);

		std::cout << "Sorted List:\n";

		std::for_each(a.cbegin(), a.cend(), [](const T& entity)
			{
				std::cout << entity << '\n';
			});
	}
}