#include <winsock2.h>
#include <stdio.h>
#include <time.h>
#pragma comment(lib, "wsock32.lib")
#pragma warning(disable: 4996)

void UDP_Conecting();
void TCP_Conecting();

int main(int argc, char* argv[])
{
    UDP_Conecting();
    //TCP_Conecting();
}

void UDP_Conecting()
{
    WSADATA WsaData;
    WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (handle <= 0)
    {
        printf("failed to create socket\n");
        WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
        system("pause");
        return 0;
    }

    SOCKADDR_IN address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons((unsigned short)1111);

    /*if (bind(handle, (const SOCKADDR*)&address, sizeof(SOCKADDR_IN)) < 0)
    {
        printf("failed to bind socket\n");
        system("pause");
        return 0;
    }*/

    /*DWORD nonBlocking = 1;
    if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
    {
        printf("failed to set non-blocking socket\n");
        return 0;
    }*/

    double check_time = 0;

    const int NUM_OF_PACKETS = 10000;
    //const int SIZE_OF_PACKETS = 256;

    char packet_data[65500] = "0";

    clock_t Cur_Check_Time_Start = clock(), Cur_Check_Time_Final = clock();

    for (int i = 0; i < NUM_OF_PACKETS; i++)
    {
        /*char Packet_data[256];
        strcpy(Packet_data, packet_data, 6);
        char Buffer[12];
        itoa(i, Buffer, 10);
        strcat(Packet_data, Buffer, sizeof(Buffer));*/
        int sent_bytes = sendto(handle, (const char*)packet_data, sizeof(packet_data),
            0, (SOCKADDR*)&address, sizeof(SOCKADDR_IN));
    }

    Cur_Check_Time_Final = clock();

    double res = (double)(Cur_Check_Time_Final - Cur_Check_Time_Start) / CLOCKS_PER_SEC;

    printf("%f \n", res);

    system("pause");
}

void TCP_Conecting()
{
    ADDRESS_FAMILY Type_of_socket = AF_INET;
    WSADATA wsadata;
    clock_t Cur_Time_Start, Cur_Time_Final;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsadata) != 0)
    {
        return 1;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = Type_of_socket;

    SOCKET sListen = socket(Type_of_socket, SOCK_STREAM, IPPROTO_TCP);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);

    SOCKET newConnection;
    newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if (newConnection == 0)
    {
        printf("Error 2");
    }
    else
    {
        printf("Client Connected!\n");
        /*char mgs[1024] = "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333"
            "0000000011111111222222223333333300000000111111112222222233333333";*/
        //char mgs = "0";

        char mgs[65536] = "0";

        Cur_Time_Start = clock();

        for (int i = 0; i < 1000000; i++)
        {
            if (send(newConnection, mgs, sizeof(mgs), NULL) == SOCKET_ERROR)
            {
                printf("Error UDP!\n");
                break;
            }
        }

        Cur_Time_Final = clock();

        //send(newConnection, mgs, sizeof(mgs), NULL);

        //for (int i = 0; i < 200000; i++)
        //{
        //    recv(newConnection, mgs, sizeof(mgs), NULL);
        //    //printf("%s \n", msg);
        //}

        double res = (double)(Cur_Time_Final - Cur_Time_Start) / CLOCKS_PER_SEC;

        printf("%f \n", res);
    }

    system("pause");
}