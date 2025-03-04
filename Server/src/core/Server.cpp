#include <Server.hpp>
#include <iostream>

using boost::asio::ip::tcp;

Server::Server(short port) : is_running(false), acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {}

void Server::start() {
    is_running = true;
    std::cout << "[Server]Server started.\n";

    std::thread accept_thread(&Server::do_accept, this, std::ref(active_client_));
    while(is_running) {

    }
    accept_thread.join();
}

void Server::do_accept(ActiveClients& ac) {
    std::cout << "[Server]Waiting client...\n";
    for (;;) {
        auto socket = std::make_shared<tcp::socket>(io_context_);
        boost::system::error_code err;
        acceptor_.accept(*socket, err);
        if (!err) {
            std::cout << "[Server]Client connected.\n";
            ac.add_client(socket->remote_endpoint().address().to_string(), std::move(socket));
        } else {
            std::cerr << err.message() << '\n';
        }
    }
}

void Server::io_run() {
    io_context_.run();
}

// void Server::start_accept() {
//     std::cout << "[Server]Waiting client...\n";
//     auto socket = std::make_shared<tcp::socket>(io_context_);
//     acceptor_.async_accept(*socket, [socket, this](const boost::system::error_code err){
//         if (!err) {
//             active_client_.add_client(socket->remote_endpoint().address().to_string(), socket);
//             std::cout << "[Server]Client connected.\n";
//             start_accept();
//         }
//     });
// }