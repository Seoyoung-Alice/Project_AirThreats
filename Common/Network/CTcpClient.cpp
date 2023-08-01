#include "CTcpClient.h"
#include <iostream>

namespace name_network
{
namespace name_tcp
{
	CTcpClient::CTcpClient()
	{
		// Loop Back Data
		m_strServerAddr = "127.0.0.1";
		m_nPort = 88;
	}

	CTcpClient::CTcpClient(std::string strServerAddr, int nPort)
		: m_strServerAddr(strServerAddr), m_nPort(nPort)
	{
	}

	CTcpClient::~CTcpClient()
	{
		closesocket(m_clientSock);
		WSACleanup();
	}

	int CTcpClient::InitialWinSock()
	{
		//----------------------
		// Initialize Winsock
		WSADATA ws;
		return WSAStartup(MAKEWORD(2, 2), &ws);
	}

	bool CTcpClient::CreateSock()
	{
		//----------------------
		// The sockaddr_in structure specifies the address family,
		// IP address, and port of the server to be connected to.
		// setup address structure
		memset((char*)&m_server, 0, sizeof(m_server));
		m_server.sin_family = AF_INET;
		m_server.sin_port = htons(m_nPort);
		m_server.sin_addr.S_un.S_addr = inet_addr(m_strServerAddr.c_str());

		//----------------------
		// Create a SOCKET for connecting to server
		m_clientSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_clientSock == INVALID_SOCKET)
		{
			printf("socket() failed with error code: %d", WSAGetLastError());
			WSACleanup();
			return false;
		}

		return true;
	}

	bool CTcpClient::StartUdp()
	{
		system("title UDP Client");

		// initialise winsock
		std::cout << "Initializing Winsock..." << std::endl;
		if (InitialWinSock() != NO_ERROR)
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

		Connect();
		std::cout << "Connected to Server!" << std::endl;

		return true;
	}

	int CTcpClient::Connect()
	{
		//----------------------
		// Connect to server.
		while (SOCKET_ERROR == connect(m_clientSock, (SOCKADDR*)&m_server, sizeof(m_server)))
		{
			std::cout << "ERROR : Socket Connect Fail : " << WSAGetLastError() << std::endl;
		}

		return 0;
	}

	bool CTcpClient::ReConnect()
	{
		return Connect();
	}

	int CTcpClient::RecvUdpMessage(char* pBuf, int nSize)
	{
		memset((void*)pBuf, 0, DEFAULT_BUFLEN);
		int nLen = sizeof(sockaddr_in);

		return recv(m_clientSock, pBuf, DEFAULT_BUFLEN, 0);
	}

	int CTcpClient::SendUdpMessage(char* pBuf, int& nSize)
	{
		return send(m_clientSock, pBuf, DEFAULT_BUFLEN, 0);
	}

}	/* namespace name_tcp */
}	/* namespace name_network */