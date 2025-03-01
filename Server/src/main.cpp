#include <Server.hpp>
#include <iostream>
int main()
{
    setlocale(LC_ALL, "");

    Server server{12345};

    server.run();
    
    return 0;
}