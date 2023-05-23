#include "../include/default.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

#ifdef StackTest
	Threadsafe_stack<int> st;
	ThreadsafeStackTest::testPush<int>(st);
	ThreadsafeStackTest::testPop<int>(st);
#endif

#ifdef QuicksortTest
	QuicksortTest::example<int>();
#endif

	return 0;
}