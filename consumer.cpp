#include "consumer.hpp"
#include <regex>
#include <sstream>
#include <iostream>
#include <thread>

static std::mutex cout_mutex;

bool is_valid_line(const std::string& line) {
    std::regex pattern(R"(^[^;]+;[^;]+;[^;]+;\+7\d{10}$)");
    return std::regex_match(line, pattern);
}

void consumer(
    BlockingQueue<std::string>& queue,
    std::map<std::string, std::string>& result_map,
    std::mutex& result_mutex,
    int consumer_id
) {
    std::string line;

    while (queue.pop(line)) {
        if (!is_valid_line(line)) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cerr << "[consumer #" << consumer_id
                      << "] Неверная строка: "
                      << line << std::endl;
            continue;
        }

        std::istringstream ss(line);
        std::string surname;
        std::getline(ss, surname, ';');

        {
            std::lock_guard<std::mutex> lock(result_mutex);
            result_map[surname] = line;
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[consumer #" << consumer_id
                      << "] обработал строку: "
                      << surname << std::endl;
        }
    }
}
