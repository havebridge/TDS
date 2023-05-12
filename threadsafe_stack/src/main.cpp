#include "../include/threadsafe_stack.h"

void testPush(Threadsafe_stack<int>& st)
{
	std::vector<std::thread> workers;
	for (int i = 0; i < 5; i++) {
		workers.push_back(std::thread([&]()
			{
				st.push(i);
			}));
	}
	
	std::for_each(workers.begin(), workers.end(), [](std::thread& t)
		{
			t.join();
		});

	st.print();

}

void testPop(Threadsafe_stack<int>& st)
{
	std::vector<std::thread> workers;

	for (int i = 0; i < 5; i++) {
		workers.push_back(std::thread([&]()
			{
				st.pop();
			}));
	}
	std::for_each(workers.begin(), workers.end(), [](std::thread& t)
		{
			t.join();
		});

	st.print();
}


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	Threadsafe_stack<int> st;


	testPush(st);
	testPop(st);

	return 0;
}