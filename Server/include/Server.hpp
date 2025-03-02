#pragma once
#include <boost/asio.hpp>

#include <unordered_map>
#include <string>

using boost::asio::ip::tcp;

class Server {
private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor_;

    std::unordered_map<std::string, std::string> clients_list;

    void start_accept();
public:
    Server(short port);

    void run();
};