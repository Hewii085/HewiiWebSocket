#include "AsyncServer.h"

unsigned int WINAPI MsgProc(void* arg);
LPFN_ACCEPTEX mFnAcceptEx = nullptr;

AsyncServer::AsyncServer(int port) :m_port(port)
{

}

AsyncServer::AsyncServer()
{

}

AsyncServer::~AsyncServer()
{

}

void AsyncServer::Initialize(int port)
{
	m_ServerSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	if (m_ServerSock == INVALID_SOCKET)
	{
		return;
	}

	DWORD bytes = 0;
	
	memset(&m_serverAddr, 0, sizeof(SOCKADDR_IN));
	m_serverAddr.sin_family = PF_INET;
	m_serverAddr.sin_port = htons(port);
	m_serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(m_ServerSock, (struct sockaddr*)&m_serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(m_ServerSock);
		WSACleanup();
		return;
	}

	hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);


	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	procCnt = systemInfo.dwNumberOfProcessors * 2;
	m_procHandles = new HANDLE[procCnt];

	for (int i = 0; i < procCnt; i++)
	{
		m_procHandles[i] = (HANDLE)_beginthreadex(NULL,0, &MsgProc, hIOCP, 0, (unsigned int*)&i);
	}

	GUID guidAcceptEx = WSAID_ACCEPTEX;
	WSAIoctl(m_ServerSock, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER, &guidAcceptEx, sizeof(GUID), &mFnAcceptEx,
		sizeof(LPFN_ACCEPTEX), &bytes, NULL, NULL);
}

void AsyncServer::StartAccept()
{
	SOCKET clnt;
	DWORD bytes;
	while (true)
	{
		ClientSession* clnt = new ClientSession();
		OverlappedIOContext* ctx = new OverlappedIOContext(clnt,IO_TYPE::IO_ACCEPT);

		if (FALSE == mFnAcceptEx(m_ServerSock, clnt->GetSocket(), m_AcceptBuffer, 0,
			sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytes, (LPOVERLAPPED)ctx))
		{

		}
	}
}

unsigned int WINAPI MsgProc(void* arg)
{
	HANDLE iocp = (HANDLE*)arg;
	DWORD recvBytes=0;
	DWORD completionKey=0;
	SOCKETINFO *clnt;

	while (true)
	{
		if (GetQueuedCompletionStatus(iocp, &recvBytes, &completionKey, (LPOVERLAPPED*)&clnt, INFINITE) == 0)
		{
			closesocket(clnt->socket);

		}

	}
	return 0;
}
