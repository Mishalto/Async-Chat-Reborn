#pragma once

#include <boost/asio.hpp>

#include <Session.hpp>

#include <iostream>
#include <array>

using boost::asio::ip::tcp;

class Client {
private:
    boost::asio::io_context io_context_;
    tcp::endpoint ep_;

public:
    Client();

    void run();
};