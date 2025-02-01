#include "src/Client.h"

int main()
{
    std::string host = "127.0.0.1";
    soba::TcpClient client;
    
    client.InitializeClient(host, 27015);
    client.Run();
}