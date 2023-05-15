#pragma once
#include "quicksort.h"

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
}