#include <chrono>
#include <iostream>
#include <thread>
#include <string>

class ScopedTimer {
public:
    explicit ScopedTimer(std::string label): label_(std::move(label)), start_(std::chrono::steady_clock::now()) {}

    ~ScopedTimer() {
        auto end_ = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
        
        std::cout << label_ << ": " << ms << "ms\n";
    }

private:
    std::string label_;
    std::chrono::steady_clock::time_point start_;
    // add whatever else you need
};

int main() {
    {
        ScopedTimer t("work");
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }

    {
        ScopedTimer t("early");
        return 0;
    }
}
