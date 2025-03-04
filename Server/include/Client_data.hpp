#pragma once

#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <array>

using boost::asio::ip::tcp;

class Client_data : public std::enable_shared_from_this<Client_data> {
private:
    std::shared_ptr<tcp::socket> socket_;
    std::string name_;
    std::array<char, 1024> data_;
    bool has_message_;
    std::string message_;

    void do_read();
public:
    Client_data();
    Client_data(std::shared_ptr<tcp::socket> socket_ptr);

    bool check_message() const;
    const std::string& get_message() const;
};