#pragma once
#include <string>
#include "blocking_queue.hpp"

class Producer {
private:
    std::string filename;
public:
    Producer(const std::string& fname) : filename(fname) {}
    void produce(BlockingQueue<std::string>& queue);
};
