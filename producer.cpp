#include "producer.hpp"
#include <fstream>
#include <iostream>

void Producer::produce(BlockingQueue<std::string>& queue) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
	queue.set_finished();
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        queue.push(line);
    }
    queue.set_finished();
}
