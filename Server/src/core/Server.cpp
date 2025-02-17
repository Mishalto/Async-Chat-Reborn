#include <Server.hpp>
#include <iostream>

// Since tcp::endpoint and tcp::acceptor are complex object
// They must be initialized through the constructor initializer list
Server::Server() : ep(tcp::v4(), server_port), acc(io_context, ep) {
    std::cout << "Server was successfully build\n";
}