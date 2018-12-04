#include "ClientSession.h"

ClientSession::ClientSession()
{
	m_Socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	PreRecv();
}

ClientSession::ClientSession()
{

}