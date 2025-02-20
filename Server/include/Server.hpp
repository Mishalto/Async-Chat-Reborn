#pragma once

#include <atomic>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

class Server
{
private:
    boost::asio::io_context io_context;

    // Server settings
    tcp::endpoint ep;
    const int server_port = 12345;  // This port is open on the server
    tcp::acceptor acc;
    std::atomic<bool> server_is_running;   // std::atomic is needed for multithreading, for this project just bool will be enough / будет достаточно
public:
    Server();

    void start();
    void start_accept(std::shared_ptr<tcp::socket> socket_ptr);
    void handle_accept(std::shared_ptr<tcp::socket> socket_ptr, const boost::system::error_code& err);
};