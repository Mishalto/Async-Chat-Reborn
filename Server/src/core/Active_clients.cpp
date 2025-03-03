#include <Active_clients.hpp>

Active_clients::Active_clients() {
    std::thread listening_thread(&Active_clients::start_listening, this);
    std::cout << "[Active_clients]Listening thread created and detached.\n";
    listening_thread.detach();
}

void Active_clients::add_client(const std::string& ip, std::shared_ptr<tcp::socket> socket_ptr) {
    active_clients_[ip] = {std::move(socket_ptr)};
}

void Active_clients::start_listening() const
{
    std::cout << "[Active_clients]Listening started.\n";
    for (;;) {
        for (auto &client : active_clients_) {
            if (client.second.check_message()) {
                std::cout << client.second.get_message() << '\n';
            }
        }
    }
}