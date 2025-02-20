#include <boost/asio.hpp>
#include <Server.hpp>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    setlocale(LC_ALL, "");

    Server server;
    std::thread server_thread(&Server::start, std::ref(server));

    server_thread.join();

    return 0;
}