#pragma once

#include <boost/asio.hpp>

#include <iostream>

using boost::asio::ip::tcp;

class Client {
private:
    boost::asio::io_context io_context_;
    tcp::endpoint ep_;
    tcp::socket socket_;

    void start();
public:
    Client();
};