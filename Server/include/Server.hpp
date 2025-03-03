#pragma once

#include <boost/asio.hpp>

#include <string>

#include <Client_data.hpp>
#include <Active_clients.hpp>

using boost::asio::ip::tcp;

class Server {
private:
    boost::asio::io_context io_context;
    tcp::acceptor acceptor_;

    Active_clients active_client_;

    void start_accept();
public:
    Server(short port);

    void run();
};