//
// Created by ksg on 20.03.16.
//

#ifndef DIHT_PROG_SEM4_CSYNCCONTAINER_H
#define DIHT_PROG_SEM4_CSYNCCONTAINER_H

#include <mutex>
#include <condition_variable>
#include <stack>

template<typename T, typename Container>
class CSyncContainer {
    Container container;
    std::mutex mtx;
    std::condition_variable cond_var;

public:
    CSyncContainer() {}

    void push(const T& x) {
        std::unique_lock<std::mutex> lock(mtx);

        container.push_back(x);
        cond_var.notify_one();
    }

    T popOrSleep() {
        std::unique_lock<std::mutex> lock(mtx);

        while (container.empty()) {
            cond_var.wait(lock);
        }

        T ret_val = container.back();
        container.pop_back();
        return ret_val;
    }

    std::pair<bool, T> popNoSleep() {
        std::lock_guard<std::mutex> lock(mtx);

        if (!container.empty()) {
            T ret = container.back();
            container.pop_back();
            return std::make_pair(true, ret);
        }
        else {
            return std::make_pair(false, T());
        }
    }
};


template<typename T>
class CSyncContainer<T, std::stack<T>> {
    std::stack<T> container;
    std::mutex mtx;
    std::condition_variable cond_var;

public:
    CSyncContainer() {}

    void push(const T& x) {
        std::unique_lock<std::mutex> lock(mtx);

        container.push(x);
        cond_var.notify_one();
    }

    T popOrSleep() {
        std::unique_lock<std::mutex> lock(mtx);

        while (container.empty()) {
            cond_var.wait(lock);
        }

        T ret_val = container.top();
        container.pop();
        return ret_val;
    }

    std::pair<bool, T> popNoSleep() {
        std::lock_guard<std::mutex> lock(mtx);

        if (!container.empty()) {
            T ret = container.top();
            container.pop();
            return std::make_pair(true, ret);
        }
        else {
            return std::make_pair(false, T());
        }
    }
};


template<typename T>
class CSyncContainer<T, std::queue<T>> {
    std::queue<T> container;
    std::mutex mtx;
    std::condition_variable cond_var;

public:
    CSyncContainer() {}

    void push(const T& x) {
        std::unique_lock<std::mutex> lock(mtx);

        container.push(x);
        cond_var.notify_one();
    }

    T popOrSleep() {
        std::unique_lock<std::mutex> lock(mtx);

        while (container.empty()) {
            cond_var.wait(lock);
        }

        T ret_val = container.front();
        container.pop();
        return ret_val;
    }

    std::pair<bool, T> popNoSleep() {
        std::lock_guard<std::mutex> lock(mtx);

        if (!container.empty()) {
            T ret = container.front();
            container.pop();
            return std::make_pair(true, ret);
        }
        else {
            return std::make_pair(false, T());
        }
    }
};
#endif //DIHT_PROG_SEM4_CSYNCCONTAINER_H
