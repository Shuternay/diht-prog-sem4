#include <iostream>
#include <atomic>
#include <thread>
#include <ctime>
#include <vector>
#include <mutex>
#include <sstream>


class futex {

	std::atomic<int> lock_state;

public:
	futex() : lock_state(-1) {}

	void lock(int thread_id) {
		int expected = -1;
		while(!lock_state.compare_exchange_weak(expected, thread_id)) {
			expected = -1;
			std::this_thread::yield();  // !!!
		}
	}

	void unlock(int thread_id) {
		int expected = thread_id;
		lock_state.compare_exchange_weak(expected, -1);
	}
};

futex task_futex;
int x = 0;
int max_value = 1200000000;

void task (int thread_id, int *ticks_count) {
	while (true) {
		task_futex.lock(thread_id);

		if (x == max_value) {
			task_futex.unlock(thread_id);
			break;
		}

		++x;
		++*ticks_count;

		task_futex.unlock(thread_id);
	}
}



int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " THREADS_NUM" << std::endl;
		return 1;
	}
	int threads_num = atoi(argv[1]);

	std::vector<std::thread> threads(threads_num);
	std::vector<int> ticks_count(threads_num);

	for (int i = 0; i < threads_num; ++i) {
		threads[i] = std::thread(task, i, &ticks_count[i]);
	}


	for (int i = 0; i < threads_num; ++i) {
		threads[i].join();
	}

	for (int i = 0; i < threads_num; ++i)
		std::cout << "thread " << i << ": " << ticks_count[i] << "\n";

	std::cout << x << "\n";
}