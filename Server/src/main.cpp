#include <boost/asio.hpp>
#include <Server.hpp>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Server server;
    std::thread server_thread(&Server::start, std::ref(server));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    server.stop();

    server_thread.join();

    return 0;
}