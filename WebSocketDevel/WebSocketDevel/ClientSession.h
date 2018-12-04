#pragma once
#include <winsock.h>
class ClientSession
{
public:
	ClientSession();
	~ClientSession();

	inline SOCKET GetSocket() { return m_Socket; }
private:

	SOCKET m_Socket;
};
