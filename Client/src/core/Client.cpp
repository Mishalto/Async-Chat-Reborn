#include <Client.hpp>

Client::Client() : ep_(boost::asio::ip::make_address_v4("127.0.0.1"), 12345), socket_(io_context_) {
    std::cout << "Start connecting.\n";
    Client::start();
}

void Client::start() {
    socket_.connect(ep_);
    std::cout << "Connected.\n";
}