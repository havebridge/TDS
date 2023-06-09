#pragma once

#include "queue.h"

#include <queue>

namespace Hthread
{
	class Thread_pool
	{
	private:
		std::vector<std::thread> pool; 
		//HQ::Queue<std::function<void()>> jobs;
		std::queue<std::function<void()>> jobs;

		mutable std::mutex mutex;
		std::condition_variable cv;
		bool terminated;

		unsigned int thread_count = std::thread::hardware_concurrency();

	public:
		Thread_pool()
		{
			for (unsigned i = 0; i != thread_count; ++i)
			{
				pool.emplace_back(std::thread(Thread_worker(this)));
			}
		}

		~Thread_pool();
		
	public:

		template<typename F, typename... Args>
		auto addTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
		{
			auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
			auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
			auto wrapper = [task_ptr]() { (*task_ptr)(); };

			{
				std::lock_guard<std::mutex> lock(mutex);
				jobs.push(wrapper);
				cv.notify_one();
			}

			return task_ptr->get_future();
		}

	private:
		class Thread_worker
		{
		private:
			Thread_pool* thread_pool;
		public:
			Thread_worker(Thread_pool* thread_pool)
				:
				thread_pool(thread_pool) {}
		public:
			void operator()()
			{
				std::unique_lock<std::mutex> lock(thread_pool->mutex);
				
				while (!thread_pool->terminated && !thread_pool->jobs.empty())
				{
					thread_pool->cv.wait(lock, [this]() {
						return this->thread_pool->terminated || !this->thread_pool->jobs.empty();
						});

					auto job = thread_pool->jobs.front();
					thread_pool->jobs.pop();
					lock.unlock();
					job();
					lock.lock();
				}
			}
		};
	};
}