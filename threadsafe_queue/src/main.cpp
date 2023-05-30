#include "../include/queue.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	Queue<int> a;
	a.Enqueue(2);
	a.Enqueue(1);
	a.Enqueue(51);
	a.Enqueue(4);

	a.print();

	a.Dequeue();
	a.print();
	return 0;
}