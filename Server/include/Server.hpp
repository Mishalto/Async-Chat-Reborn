#pragma once

#include <atomic>

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server
{
private:
    boost::asio::io_context io_context;

    // Server settings
    const int server_port = 12345;  // This port is open on the server
    tcp::endpoint ep;
    tcp::acceptor acc;
    std::atomic<bool> is_running;   // std::atomic is needed for multithreading, for this project just bool will be enough / будет достаточно
public:
    Server();
};