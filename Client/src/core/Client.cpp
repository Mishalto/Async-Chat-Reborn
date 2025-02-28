#include <Client.hpp>

Client::Client() : ep_(boost::asio::ip::make_address_v4("127.0.0.1"), 12345), socket_(io_context_) {
    std::cout << "Hello, waiting for connection...\n";
    Client::start();
}

void Client::start() {
    boost::system::error_code err;
    socket_.connect(ep_, err);
    if(err) {
        std::cerr << err.message() << '\n';
    }
    std::cout << "Connected.\n";
}