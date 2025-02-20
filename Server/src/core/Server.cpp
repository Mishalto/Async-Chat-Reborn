#include <Server.hpp>
#include <iostream>
#include <memory>
#include <functional>

// They must be initialized through/через the constructor initializer list
Server::Server() : ep(tcp::v4(), server_port), acc(io_context, ep) {
    server_is_running = false; // The default state of the server is disabled
    std::cout << server_port;
}

void Server::start() {
    server_is_running = true;
    std::cout << "Server is running...\n";
    while(server_is_running) {
        auto socket_ptr = std::make_shared<tcp::socket>(io_context);
        start_accept(socket_ptr);
        io_context.run();
    }
}

void Server::start_accept(std::shared_ptr<tcp::socket> socket_ptr) {
    acc.async_accept(*socket_ptr, boost::bind(handle_accept, socket_ptr, std::placeholders::_1));
}

void Server::handle_accept(std::shared_ptr<tcp::socket> socket_ptr, const boost::system::error_code& err) {
    if(err) {
        std::cerr << err.message() << '\n';
    } else {
        socket_ptr->async_read_some();
    }
}