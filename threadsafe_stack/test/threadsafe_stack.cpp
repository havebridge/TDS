#include "..\include\threadsafe_stack.h"

namespace ThreadsafeStackTest
{
	template<typename T>
	inline void testPush(Threadsafe_stack<T>& st)
	{
		std::vector<std::thread> workers;

		for (int i = 0; i < 5; i++) 
		{
			workers.push_back(std::thread([&]()
				{
					st.push(i);
				}));
		}

		std::for_each(workers.begin(), workers.end(), [](std::thread& t)
			{
				t.join();
			});

#ifdef StackTest
		st.print();
#endif
	}

	template<typename T>
	inline void testPop(Threadsafe_stack<T>& st)
	{
		std::vector<std::thread> workers;

		for (T i = 0; i < 5; i++)
		{
			workers.push_back(std::thread([&]()
				{
					st.pop();
				}));
		}

		std::for_each(workers.begin(), workers.end(), [](std::thread& t)
			{
				t.join();
			});

#ifdef StackTest
		st.print();
#endif
	}
}