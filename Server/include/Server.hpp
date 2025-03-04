#pragma once

#include <boost/asio.hpp>

#include <string>

#include <Client_data.hpp>
#include <Active_clients.hpp>

using boost::asio::ip::tcp;

class Server {
private:
    bool is_running;
    ActiveClients active_client_;
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
public:
    Server(short port);

    void start();
    void do_accept(ActiveClients& ac);
    void io_run();
};
