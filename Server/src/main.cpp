#include <Server.hpp>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");

    Server server{12345};
    std::cout << "Started\n";

    server.run();

    std::cout << "End\n";
    return 0;
}