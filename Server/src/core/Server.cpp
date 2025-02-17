#include <Server.hpp>
#include <iostream>

// Since tcp::endpoint and tcp::acceptor are complex object
// They must be initialized through the constructor initializer list
Server::Server() : ep(tcp::v4(), server_port), acc(io_context, ep) {
    is_running.store(false); // The default state of the server is disabled
    std::cout << "Server initialized successfully.\n";
}


// Starting the server
void Server::start() {
    is_running.store(true);
    std::cout << "The server has started on port " << server_port << "..." << '\n';
    std::cout << "Waiting the connections...\n";
    while(is_running) {

        tcp::socket socket(io_context);
        boost::system::error_code ec;
        acc.accept(socket, ec);
        if (ec) {
            std::cout << ec.message() << '\n';
        }
        else {
            std::cout << "Client connected.\n";
        }
    }
    std::cout << "Server is shutting down\n";
}

// Stoping the server
void Server::stop() {
    is_running.store(false);
}

// void Server::error_handler(boost::system::error_code& ec) const
// {
// }