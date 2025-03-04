#include <Client_data.hpp>

Client_data::Client_data() {}

Client_data::Client_data(std::shared_ptr<tcp::socket> socket_ptr) : socket_(std::move(socket_ptr)), name_("<blank>") {
    std::cout << "[Client_data]The message flag set by default.\n";
    has_message_ = false;
    message_ = "<blank>";
    do_read();
}

void Client_data::do_read() {
    std::cout << name_ << " is listening.\n";
    auto self(shared_from_this());
    socket_->async_read_some(boost::asio::buffer(data_), [this, self](const boost::system::error_code err, size_t length) {
        if (!err) {
            std::cout << "[Client_data]Message from" << name_ << "received.\n";
            message_ = std::string(data_.data(), length);
            has_message_ = true;
            do_read();
        } else {
            std::cerr << err.message() << '\n';
        }
    });
}

bool Client_data::check_message() const {
    return has_message_;
}

const std::string& Client_data::get_message() const {
    return message_;
}