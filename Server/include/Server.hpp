#pragma once
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server {
private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor_;

    void start_accept();
public:
    Server(short port);

    void run();
};