#pragma once
#include <process.h>
#include <winsock2.h>
#include <MSWSock.h>
#include "ClientSession.h"
#define MAX_BUFFER 8192

enum IO_TYPE
{
	IO_NONE,
	IO_SEND,
	IO_RECV,
	IO_RECV_ZERO,
	IO_ACCEPT,
	IO_DISCOONECT
};

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	WSABUF dataBuffer;
	SOCKET socket;
	char messageBuffer[MAX_BUFFER];
	int receiveBytes;
	int sendBytes;
};

struct OverlappedIOContext
{
	OverlappedIOContext(ClientSession* sess, IO_TYPE type) :
		clntSession(sess)
		, mIoType(type) {};

	OVERLAPPED mOverlapped;
	ClientSession* clntSession;
	IO_TYPE	   mIoType;
	WSABUF	   mWsaBuf;
};


class AsyncServer
{
public:
	AsyncServer();
	AsyncServer(int port);
	~AsyncServer();


	void Initialize(int port);
	void StartAccept();

private:
	int m_port;

	int procCnt;
	bool m_isContinue;
	char m_AcceptBuffer[64];
	HANDLE hIOCP;
	HANDLE* m_procHandles;
	SOCKET m_ServerSock;
	SOCKADDR_IN m_serverAddr;
};