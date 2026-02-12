#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

std::atomic<int> counter(0);
int counter2 = 0;


void work(int id) {

    for (int i = 0; i < 10000; i++) {
        counter++;
        counter2++;
    }
    
    std::cout << "Thread: " << id << std::endl;

}

int main() {
    std::vector<std::thread> threads;

    unsigned int n = std::thread::hardware_concurrency();

    for (unsigned int i = 0; i < n; i++) {
        threads.emplace_back(work, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << counter << std::endl;
    std::cout << counter2 << std::endl;

}