#include <Server.hpp>
#include <iostream>

using boost::asio::ip::tcp;

Server::Server(short port) : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
}

void Server::start_accept() {
    std::cout << "Waiting client...\n";
    auto socket = std::make_shared<tcp::socket>(io_context);
    acceptor_.async_accept(*socket, [socket, this](const boost::system::error_code err){
        if (!err) {
            active_client_.add_client(socket->remote_endpoint().address().to_string(), socket);
            std::cout << "Client connected.\n";
            start_accept();
        }
    });
}


void Server::run() {
    io_context.run();
}
