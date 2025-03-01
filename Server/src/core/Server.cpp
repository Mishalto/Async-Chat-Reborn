#include <Server.hpp>
#include <iostream>
#include <Session.hpp>

using boost::asio::ip::tcp;

Server::Server(short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    std::cout << "Waiting client...\n";
    auto socket = std::make_shared<tcp::socket>(io_context);
    acceptor_.async_accept(*socket, [socket](const boost::system::error_code err){
        if (!err) {
            std::cout << "Connected: " << socket->remote_endpoint() << '\n';
            auto session = std::make_shared<Session>(std::move(*socket));
            session->start();
        }
    });
}


void Server::run() {
    io_context.run();
}