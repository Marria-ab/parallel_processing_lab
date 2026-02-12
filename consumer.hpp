#pragma once
#include <string>
#include <map>
#include <mutex>
#include "blocking_queue.hpp"

void consumer(
    BlockingQueue<std::string>& queue,
    std::map<std::string, std::string>& result_map,
    std::mutex& result_mutex,
    int consumer_id
);

