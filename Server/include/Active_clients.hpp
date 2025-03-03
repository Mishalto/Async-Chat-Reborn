#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#include <boost/asio.hpp>

#include <Client_data.hpp>

using boost::asio::ip::tcp;

class Active_clients {
private:
    std::unordered_map<std::string, Client_data> active_clients_;
public:
    Active_clients();
    void add_client(const std::string& ip, std::shared_ptr<tcp::socket> socket_ptr);

    void start_listening() const;
};