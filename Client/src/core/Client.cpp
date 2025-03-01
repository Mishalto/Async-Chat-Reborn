#include <Client.hpp>

Client::Client() : ep_(boost::asio::ip::make_address_v4("127.0.0.1"), 12345), socket_(io_context_) {
    is_connected = false;
}

void Client::start() {
    std::cout << "Hello, waiting for connection...\n";

    boost::system::error_code err;
    socket_.connect(ep_, err);
    if (err) {
        std::cerr << err.message() << '\n';
    }
    std::cout << "Connected.\n";

    is_connected = true;
    while (is_connected)
    {
        do_read();
    }
}

void Client::do_read() {
    socket_.async_read_some(boost::asio::buffer(data_), [this](const boost::system::error_code err, size_t length){
        if (!err) {
            std::cout << std::string(data_.data(), length);
        }
    });
}