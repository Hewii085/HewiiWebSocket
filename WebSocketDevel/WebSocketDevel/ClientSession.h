#pragma once
#include <winsock2.h>

class ClientSession
{
public:
	ClientSession();
	~ClientSession();

	inline SOCKET GetSocket() { return m_Socket; }
	void PreRecv();
private:

	SOCKET m_Socket;
};
