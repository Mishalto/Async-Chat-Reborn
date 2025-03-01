#include <Session.hpp>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start() {
    std::thread read_thread(&Session::do_read, this);
    read_thread.join();
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_), [this, self](const boost::system::error_code err, size_t length){
        if (!err) {
            std::cout << std::string(data_.data(), length);
            do_read();
        } else {
            if(err == boost::asio::error::eof) {
                std::cerr << "Client disconnected.\n";
            } else {
                std::cerr << err.message() << '\n';
            }
        }
    });
}

void Session::send() {
    std::cout << "Message: ";
    std::string message;
    std::cin >> message;
    boost::system::error_code err;
    boost::asio::write(socket_, boost::asio::buffer(message), err);
    if (err) {
        std::cerr << err.message() << '\n';
    }
}