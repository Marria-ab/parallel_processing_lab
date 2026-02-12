#include <iostream>
#include <fstream>
#include <thread>
#include <map>
#include <mutex>
#include <vector>
#include "blocking_queue.hpp"
#include "producer.hpp"
#include "consumer.hpp"

int main() {
    std::ios::sync_with_stdio(false);

    BlockingQueue<std::string> queue;
    std::map<std::string, std::string> result_map;
    std::mutex result_mutex;

    std::string input_file = "../test.txt";
    std::string output_file = "../result.txt";

    Producer producer(input_file);

    std::thread prod_thread(&Producer::produce, &producer, std::ref(queue));

    std::thread consumer1(
        consumer,
        std::ref(queue),
        std::ref(result_map),
        std::ref(result_mutex),
        1
    );

    std::thread consumer2(
        consumer,
        std::ref(queue),
        std::ref(result_map),
        std::ref(result_mutex),
        2
    );

    prod_thread.join();
    consumer1.join();
    consumer2.join();

    std::map<char, std::vector<std::string>> grouped_lines;

    for (const auto& pair : result_map) {
        const std::string& surname = pair.first;
        const std::string& line = pair.second;

        if (!surname.empty()) {
            grouped_lines[surname[0]].push_back(line);
        }
    }

    std::ofstream out(output_file);
    if (!out.is_open()) {
        std::cerr << "Не удалось создать файл: " << output_file << std::endl;
        return 1;
    }

    for (const auto& group : grouped_lines) {
        out << group.first << ":" << std::endl;
        for (const auto& line : group.second) {
            out << "  " << line << std::endl;
        }
        out << std::endl;
    }

    std::cout << "Готово. Результаты в файле " << output_file << std::endl;
    return 0;
}
