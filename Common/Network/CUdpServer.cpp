#include "CUdpServer.h"
#include <iostream>

namespace name_network
{
namespace name_udp
{
	CUdpServer::CUdpServer()
	{
		// Loop Back Data
		m_strServerAddr = "127.0.0.1";
		m_nPort = 88;
	}

	CUdpServer::CUdpServer(std::string strServerAddr, int nPort)
		: m_strServerAddr(strServerAddr), m_nPort(nPort)
	{
	}

	CUdpServer::~CUdpServer()
	{
		closesocket(m_serverSock);
		WSACleanup();
	}

	bool CUdpServer::InitialWinSock()
	{
		WSADATA ws;
		return WSAStartup(MAKEWORD(2, 2), &ws);
	}

	int CUdpServer::CreateSock()
	{
		// setup address structure
		memset((char*)&m_server, 0, sizeof(m_server));
		m_server.sin_family = AF_INET;
		m_server.sin_addr.S_un.S_addr = inet_addr(m_strServerAddr.c_str());
		m_server.sin_port = htons(m_nPort);

		m_serverSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (m_serverSock == SOCKET_ERROR) // <<< UDP socket
		{
			printf("socket() failed with error code: %d", WSAGetLastError());
			return false;
		}

		return true;
	}

	int CUdpServer::Bind()
	{
		return bind(m_serverSock, (sockaddr*)&m_server, sizeof(m_server));
	}

	bool CUdpServer::StartUdp()
	{
		system("title UDP Server");

		// initialise winsock
		std::cout << "Initializing Winsock..." << std::endl;
		if (InitialWinSock())
		{
			std::cout << "Failed. Error Code: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << "Initialized Complete" << std::endl;

		// create socket
		if (CreateSock() == SOCKET_ERROR)
		{
			std::cout << "socket() failed with error code: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << "Create Socket complete!" << std::endl;

		// Bind
		if (Bind() == SOCKET_ERROR)
		{
			std::cout << "Bind failed with error code: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << "Bind complete!" << std::endl;

		return true;
	}

	int CUdpServer::RecvUdpMessage(char* pBuf, int nSize)
	{
		int nLen = sizeof(sockaddr_in);
		int nResultValue = recvfrom(m_serverSock, pBuf, nSize, 0, (sockaddr*)&m_client, &nLen);
		//std::cout << "Recv Data = " << pBuf << std::endl;

		return nResultValue;
	}

	int CUdpServer::SendUdpMessage(char* pBuf, int& nSize)
	{
		return sendto(m_serverSock, pBuf, strlen(pBuf), 0, (sockaddr*)&m_client, sizeof(sockaddr_in));
	}

}	/* namespace name_udp */
}	/* namespace name_network */