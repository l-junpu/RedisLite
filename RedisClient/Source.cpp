#include "src/Client.h"

int main()
{
    soba::TcpClient client;
    
    client.InitializeClient("127.0.0.1", 27015);
    client.Run();
}