#pragma once

#include "default.h"
#include "thread_pool.h"


template<typename T>
class Threadsafe_queue
{
private:
	struct node
	{
		std::shared_ptr<T> data;
		std::unique_ptr<node> next;
	};

	std::unique_ptr<node> head;
	node* tail;

	mutable	std::mutex head_mutex;
	mutable std::mutex tail_mutex;
	mutable std::shared_mutex print_mutex;

	std::condition_variable cv;

private:
//	trying pop head without any condition
	node* getTail() const noexcept
	{
		std::lock_guard<std::mutex> tail_lock(tail_mutex);
		return tail;
	}

	node* getHead() const noexcept
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);
		return head.get();
	}

	std::unique_ptr<node> popHead()
	{
		std::unique_ptr<node> old_head = std::move(head);
		head = std::move(old_head->next);
		return old_head;
	}

	std::unique_ptr<node> tryPopHead()
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);

		if (head.get() == getTail())
		{
			return std::unique_ptr<node>();
		}

		return popHead();
	}

	std::unique_ptr<node> tryPopHead(T& some_value)
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);

		if (head.get() == getTail())
		{
			return std::unique_ptr<node>();
		}

		some_value = std::move(*head->data);
		return popHead();
	}
//	when queue is not empty then pop head, using conditional variable
	std::unique_lock<std::mutex> waitForCondititon()
	{
		std::unique_lock<std::mutex> head_lock(head_mutex);
		cv.wait(head_lock, [&]() {
			return head.get() != getTail();
			});
		return std::move(head_lock);
	}

	std::unique_ptr<node> waitPopHead()
	{
		std::unique_lock<std::mutex> head_lock(waitForCondititon());
		return popHead();
	}

	std::unique_ptr<node> waitPopHead(T& some_value)
	{
		std::unique_lock<std::mutex> head_lock(waitForCondititon());
		some_value = std::move(*head->data);
		return popHead();
	}

public:
	Threadsafe_queue() 
		:
		head(new node),
		tail(head.get()) {}

	Threadsafe_queue(const Threadsafe_queue&) = delete;
	Threadsafe_queue operator=(const Threadsafe_queue&) = delete;

	void push(const T& new_value)
	{
		std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));

		std::unique_ptr<node> p(new node);
		{
			node* const new_tail = p.get();
			std::lock_guard<std::mutex> tail_lock(tail_mutex);
			tail->data = std::move(new_data);
			tail->next = std::move(p);
			tail = new_tail;
		}
		
		cv.notify_one();
	}

//	try pop head without any condition
	std::shared_ptr<T> tryPop()
	{
		std::unique_ptr<node> old_head = tryPopHead();
		return old_head ? old_head->data : std::shared_ptr<T>();
	}


	bool tryPop(T& value)
	{
		const std::unique_ptr<node> old_head = tryPopHead(value);
		return old_head;
	}

//	pop head when queue is not empty(head != tail)
	std::shared_ptr<T> waitAndPop()
	{
		const std::unique_ptr<node> old_head = waitPopHead();
		return old_head->data;
	}

	void waitAndPop(T& some_value)
	{
		const std::unique_ptr<node> old_head = waitPopHead(some_value);
	}

	bool empty() const noexcept
	{
		std::lock_guard<std::mutex> head_lock(head_mutex);
		return head.get() != getTail();
	}

	void print() const noexcept
	{
		std::cout << "Queue:\n";
		unsigned i = 0;

		std::lock_guard<std::shared_mutex> print_lock(print_mutex);
		node* n = getHead();

		while (n->next != nullptr)
		{
			std::cout << '[' << i << ']';
			std::cout << *n->data << '\n';
			n = n->next.get();
			i++;
		}
		std::cout << '\n';
	}
};