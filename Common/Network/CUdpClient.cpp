#include "CUdpClient.h"
#include <iostream>

namespace name_network
{
namespace name_udp
{
	CUdpClient::CUdpClient()
	{
		// Loop Back Data
		m_strServerAddr = "127.0.0.1";
		m_nPort = 88;
	}

	CUdpClient::CUdpClient(std::string strServerAddr, int nPort)
		: m_strServerAddr(strServerAddr), m_nPort(nPort)
	{
	}

	CUdpClient::~CUdpClient()
	{
		closesocket(m_clientSock);
		WSACleanup();
	}

	int CUdpClient::InitialWinSock()
	{
		WSADATA ws;
		return WSAStartup(MAKEWORD(2, 2), &ws);
	}

	bool CUdpClient::CreateSock()
	{
		// setup address structure
		memset((char*)&m_server, 0, sizeof(m_server));
		m_server.sin_family = AF_INET;
		m_server.sin_port = htons(m_nPort);
		m_server.sin_addr.S_un.S_addr = inet_addr(m_strServerAddr.c_str());

		m_clientSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (m_clientSock == SOCKET_ERROR) // <<< UDP socket
		{
			printf("socket() failed with error code: %d", WSAGetLastError());
			return false;
		}

		return true;
	}

	bool CUdpClient::StartUdp()
	{
		system("title UDP Client");

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
		return true;
	}

	int CUdpClient::RecvUdpMessage(char* pBuf, int nSize)
	{
		int nLen = sizeof(sockaddr_in);

		return recvfrom(m_clientSock, pBuf, nSize, 0, (sockaddr*)&m_server, &nLen);
	}

	int CUdpClient::SendUdpMessage(char* pBuf, int& nSize)
	{
		return sendto(m_clientSock, pBuf, strlen(pBuf), 0, (sockaddr*)&m_server, sizeof(sockaddr_in));
	}

}	/* namespace name_udp */
}	/* namespace name_network */