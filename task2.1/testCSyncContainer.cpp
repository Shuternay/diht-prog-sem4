#include "gtest/gtest.h"

#include <vector>
#include <queue>
#include <list>
#include <thread>

#include "CSyncContainer.h"

TEST (CSyncContainer, constructor) {
    CSyncContainer<int, std::vector<int>> sc_vector;
    CSyncContainer<int, std::deque<int>> sc_deque;
    CSyncContainer<int, std::list<int>> sc_list;
}

TEST (CSyncContainer, sc_vector_push_pop) {
    CSyncContainer<int, std::vector<int>> sc;

    sc.push(1);
    sc.push(2);

    ASSERT_EQ(2, sc.popOrSleep());
    ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
}

TEST (CSyncContainer, sc_deque_push_pop) {
    CSyncContainer<int, std::deque<int>> sc;

    sc.push(1);
    sc.push(2);

    ASSERT_EQ(2, sc.popOrSleep());
    ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
}

TEST (CSyncContainer, sc_list_push_pop) {
    CSyncContainer<int, std::list<int>> sc;

    sc.push(1);
    sc.push(2);

    ASSERT_EQ(2, sc.popOrSleep());
    ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
}


TEST (CSyncContainer, sc_multithread) {
    CSyncContainer<int, std::vector<int>> sc;

    std::thread writer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        sc.push(1);
        sc.push(2);
    });

    std::thread reader([&]() {
        ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
        ASSERT_EQ(2, sc.popOrSleep());
        ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    });

    writer.join();
    reader.join();
}


TEST (CSyncContainer_stack, constructor) {
    CSyncContainer<int, std::stack<int>> sc_stack;
}

TEST (CSyncContainer_stack, push_pop) {
    CSyncContainer<int, std::stack<int>> sc;

    sc.push(1);
    sc.push(2);

    ASSERT_EQ(2, sc.popOrSleep());
    ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
}

TEST (CSyncContainer_stack, sc_multithread) {
    CSyncContainer<int, std::stack<int>> sc;

    std::thread writer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        sc.push(1);
        sc.push(2);
    });

    std::thread reader([&]() {
        ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
        ASSERT_EQ(2, sc.popOrSleep());
        ASSERT_EQ(std::make_pair(true, 1), sc.popNoSleep());
    });

    writer.join();
    reader.join();
}


TEST (CSyncContainer_queue, constructor) {
    CSyncContainer<int, std::queue<int>> sc_queue;
}

TEST (CSyncContainer_queue, push_pop) {
    CSyncContainer<int, std::queue<int>> sc;

    sc.push(1);
    sc.push(2);

    ASSERT_EQ(1, sc.popOrSleep());
    ASSERT_EQ(std::make_pair(true, 2), sc.popNoSleep());
    ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
}

TEST (CSyncContainer_queue, sc_multithread) {
    CSyncContainer<int, std::queue<int>> sc;

    std::thread writer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        sc.push(1);
        sc.push(2);
    });

    std::thread reader([&]() {
        ASSERT_EQ(std::make_pair(false, 0), sc.popNoSleep());
        ASSERT_EQ(1, sc.popOrSleep());
        ASSERT_EQ(std::make_pair(true, 2), sc.popNoSleep());
    });

    writer.join();
    reader.join();
}
