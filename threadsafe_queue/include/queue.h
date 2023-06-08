#pragma once

#include "default.h"


namespace HQ
{
	template<typename T>
	class Queue
	{
	private:
		T* data;
		T head;
		T tail;
		int capacity;
		int size;

	public:
		explicit Queue() noexcept
			:
			data(new T[1024]),
			head(0),
			tail(0),
			capacity(1024),
			size(0) {}

		explicit Queue(int size) noexcept
			:
			data(new T[size]),
			head(0),
			tail(0),
			capacity(size),
			size(0) {}

		Queue(const Queue& other) noexcept	// shallow copy
		{
			assert(other.data != nullptr);

			data = new T[capacity];
			size = other.size;
			head = other.head;
			tail = other.tail;

			for (int i = 0; i != size; ++i)
			{
				data[i] = other.data[i];
			}
		}


		Queue operator=(const Queue& other) noexcept	// deep copy
		{
			if (&other == this)
			{
				return *this;
			}

			delete[] data;

			if (other.data)
			{
				data = new T[capacity];

				for (int i = 0; i != size; ++i)
				{
					data[i] = other.data[i];
				}

				head = other.head;
				tail = other.tail;
			}
			else
			{
				data = nullptr;
			}
		}

		~Queue()
		{
			delete[] data;
		}

	public:
		void Enqueue(const T& new_data)
		{
			if (isFull())
			{
				std::cerr << "The queue is full\n";
				exit(EXIT_FAILURE);
			}

			data[tail] = std::move(new_data);
			if (tail == capacity)
			{
				tail = 1;
				return;
			}

			tail++;
			size++;
		}

		T Dequeue()
		{
			if (isEmpty())
			{
				std::cerr << "The queue is empty\n";
				exit(EXIT_FAILURE);
			}

			T res = data[head];
			if (head == capacity)
			{
				head = 1;
				return res;
			}

			head++;
			size--;

			return res;
		}

		[[nodiscard]] T Peek() const noexcept
		{
			return data[head];
		}


		[[nodiscard]] size_t Size() const noexcept
		{
			return size;
		}

		[[nodiscard]] bool isEmpty() const noexcept
		{
			return size == 0;
		}

		[[nodiscard]] bool isFull() const noexcept
		{
			return size == capacity;
		}

		void print() const noexcept
		{
			std::cout << "Queue:\n";
			for (int i = head; i != tail; ++i)
			{
				std::cout << data[i] << '\n';
			}
			std::cout << "head: " << data[head] << '\n';
			std::cout << "tail: " << data[tail] << '\n';
		}
	};
}