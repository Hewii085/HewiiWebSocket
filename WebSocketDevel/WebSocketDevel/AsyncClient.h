#pragma once
#include <process.h>
#include <winsock2.h>


class AsyncClient
{
public:
	AsyncClient();
	AsyncClient(int port);
	~AsyncClient();

private:
	int m_port;

	SOCKET m_ServerSock;
	SOCKADDR_IN m_serverAddr;

};
