
#include <iostream>
#include <queue>
#include <random>

#include <thread>
#include <mutex>
#include <condition_variable>

int main()
{
    std::queue<int> data{};
    std::mutex data_mutex{};
    std::condition_variable data_size_cv{};

    const int max_data_size = 5;

    auto produce_function = [&](){
        while (true)
        {
            std::unique_lock<std::mutex> lock(data_mutex);
            data_size_cv.wait(lock, [&data](){ return data.size() < max_data_size; });

            int item = std::rand() % 10 + 1;
            data.push(item);
            std::cout << "Produced " << std::to_string(item) << ", container size: " << data.size()<< std::endl;

            data_size_cv.notify_one();
        }
    };
    auto consume_function = [&](){
        while (true)
        {
            std::unique_lock<std::mutex> lock(data_mutex);
            data_size_cv.wait(lock, [&data](){ return !data.empty() ;});

            auto var = data.front();
            data.pop();
            std::cout << "Consumed " << std::to_string(var) << ", container size: " << data.size()<< std::endl;

            data_size_cv.notify_one();
        }
    };

    auto producer_thread = std::thread(produce_function);
    auto consumer_thread = std::thread(consume_function);

    if (producer_thread.joinable())
        producer_thread.join();
    if (consumer_thread.joinable())
        consumer_thread.join();

    return 0;
}