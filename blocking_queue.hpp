#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
    bool finished_ = false;

public:
    void push(const T& item) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(item);
        }
        cond_.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]{
            return !queue_.empty() || finished_;
         });
        if (queue_.empty())
            return false;
        item = queue_.front();
        queue_.pop();
        return true;
    }

    void set_finished() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            finished_ = true;
        }
        cond_.notify_all();
    }
};
