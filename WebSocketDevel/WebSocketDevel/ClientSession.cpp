#include "ClientSession.h"

ClientSession::ClientSession()
{
	m_m_SocketSock = WSASocket(AF_INET, SOCK_STREAM, IPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

}