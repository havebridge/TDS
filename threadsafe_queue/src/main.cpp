#include "../test/threadsafe_queue.h"
#include "../test/queue.h"


int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Hthread::Thread_pool threadPool;
	Threadsafe_queue<int> q;
	
//	Adding to a thread pool push function as much as hardware cores on pc 
	std::vector<std::future<bool>> res;

	/*for (int i = 0; i != std::thread::hardware_concurrency() - 1; ++i)
	{
		res.emplace_back(threadPool.addTask(ThreadsafeQueueTest::testPush<int>, std::ref(q)));
	}*/
	res.emplace_back(threadPool.addTask(ThreadsafeQueueTest::testPush<int>, std::ref(q)));

	//std::future<bool> answer = std::async(ThreadsafeQueueTest::testPush<int>, std::ref(q));

	for (auto&& f : res)
	{
		f.get();
	}
	//answer.get();

	q.print();

	/*std::future<bool> answer1 = std::async(ThreadsafeQueueTest::testTryPop<int>, std::ref(q));
	answer1.get();*/
	std::future<bool> res1 = std::async(ThreadsafeQueueTest::testTryPop<int>, std::ref(q));
	//res1.emplace_back(threadPool.addTask(ThreadsafeQueueTest::testTryPop<int>, std::ref(q)));
	//res1.emplace_back(threadPool.addTask(ThreadsafeQueueTest::testWaitAndPop<int>, std::ref(q)));

	//res1 = threadPool.addTask(ThreadsafeQueueTest::testWaitAndPop<int>, std::ref(q));

	/*for (auto&& f : res1)
	{
		f.get();
	}*/

	res1.get();

	q.print();

	/*QueueTest::testPush<int>(q);
	QueueTest::testPrint<int>(q);
	QueueTest::testPop<int>(q);
	QueueTest::testPrint<int>(q);*/
	return 0;
}