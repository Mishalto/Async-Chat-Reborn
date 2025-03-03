#include <Active_clients.hpp>

void Active_clients::add_client(const std::string& ip, std::shared_ptr<tcp::socket> socket_ptr) {
    active_clients_[ip] = {std::move(socket_ptr)};
}