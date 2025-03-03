#pragma once
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Client_data {
private:
    std::shared_ptr<tcp::socket> socket_;
    std::string name_;

public:
    Client_data() {}
    Client_data(std::shared_ptr<tcp::socket> socket_ptr) : socket_(std::move(socket_ptr)), name_("<blank>") {}
};