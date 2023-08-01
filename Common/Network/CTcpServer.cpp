#include "CTcpServer.h"
#include <iostream>

namespace name_network
{
namespace name_tcp
{
	CTcpServer::CTcpServer()
	{
		// Loop Back Data
		m_strServerAddr = "127.0.0.1";
		m_nPort = 88;
	}

	CTcpServer::CTcpServer(std::string strServerAddr, int nPort)
		: m_strServerAddr(strServerAddr), m_nPort(nPort)
	{
	}

	CTcpServer::~CTcpServer()
	{
		closesocket(m_serverSock);
		WSACleanup();
	}

	int CTcpServer::InitialWinSock()
	{
		WSADATA ws;
		return WSAStartup(MAKEWORD(2, 2), &ws);
	}

	int CTcpServer::CreateSock()
	{
		//----------------------
		// The sockaddr_in structure specifies the address family,
		// IP address, and port of the server to be connected to.
		// setup address structure
		memset((char*)&m_server, 0, sizeof(m_server));
		m_server.sin_family = AF_INET;
		m_server.sin_addr.S_un.S_addr = inet_addr(m_strServerAddr.c_str());
		m_server.sin_port = htons(m_nPort);

		//----------------------
		// Create a SOCKET for connecting to server
		m_serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_serverSock == INVALID_SOCKET) // <<< UDP socket
		{
			printf("socket() failed with error code: %d", WSAGetLastError());
			return false;
		}

		return true;
	}

	int CTcpServer::Bind()
	{
		return bind(m_serverSock, (sockaddr*)&m_server, sizeof(m_server));
	}

	int CTcpServer::Listen()
	{
		return listen(m_serverSock, SOMAXCONN);
	}

	int CTcpServer::Accept()
	{
		return accept(m_serverSock, NULL, NULL);
	}

	bool CTcpServer::StartUdp()
	{
		system("title UDP Server");

		//----------------------
		// Initialize Winsock
		std::cout << "Initializing Winsock..." << std::endl;
		if (InitialWinSock() != NO_ERROR)
		{
			std::cout << "Failed. Error Code: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << "Initialized Complete" << std::endl;

		//----------------------
		// Create a SOCKET for connecting to server
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

		//----------------------
		// Listen for incoming connection requests 
		// on the created socket
		while (Listen() == SOCKET_ERROR)
		{
			std::cout << "listen function failed with error : " << WSAGetLastError() << std::endl;
		}

		//-----------------------
		// Accept Client Socket
		if (Accept() == INVALID_SOCKET)
		{
			std::cout << "Accept Failed : " << WSAGetLastError() << std::endl;
			return false;
		}

		return true;
	}

	bool CTcpServer::ReConnect()
	{
		//----------------------
		// Listen for incoming connection requests 
		// on the created socket
		while (Listen() == SOCKET_ERROR)
		{
			std::cout << "listen function failed with error : " << WSAGetLastError() << std::endl;
		}

		//-----------------------
		// Accept Client Socket
		if (Accept() == INVALID_SOCKET)
		{
			std::cout << "Accept Failed : " << WSAGetLastError() << std::endl;
			return false;
		}

		return true;
	}

	int CTcpServer::RecvUdpMessage(char* pBuf, int nSize)
	{
		memset((void*)pBuf, 0, DEFAULT_BUFLEN);
		int nLen = sizeof(sockaddr_in);
		int nResultValue = recv(m_serverSock, pBuf, DEFAULT_BUFLEN, 0);
		//std::cout << "Recv Data = " << pBuf << std::endl;

		return nResultValue;
	}

	int CTcpServer::SendUdpMessage(char* pBuf, int& nSize)
	{
		return send(m_serverSock, pBuf, DEFAULT_BUFLEN, 0);
	}

}	/* namespace name_udp */
}	/* namespace name_network */
