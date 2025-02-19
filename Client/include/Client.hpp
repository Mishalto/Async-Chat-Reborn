#pragma once

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Client
{
private:
    boost::asio::io_context io_context;
    // Setting up a connection to the server
    tcp::endpoint ep;
public:
    Client();

    // Connect methods
    void start_connection();
    // Sending/receiving
    std::string receive_message(tcp::socket& socket);
    void receive_loop(tcp::socket& socket);
    void send_message(tcp::socket& socket);
    // Main
    void chat(tcp::socket& socket);
};