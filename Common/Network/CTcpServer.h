#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_BUFLEN 512

namespace name_network
{
namespace name_tcp
{
	class CTcpServer
	{
	public:
		CTcpServer();
		CTcpServer(std::string strServerAddr, int nPort);
		virtual ~CTcpServer();

	private:
		sockaddr_in m_server;
		sockaddr_in m_client;
		SOCKET m_serverSock;

		std::string m_strServerAddr;
		int m_nPort;

		bool InitialWinSock();
		int CreateSock();
		int Bind();

	public:
		bool StartUdp();

		int RecvUdpMessage(char* pBuf, int nSize);
		int SendUdpMessage(char* pBuf, int& nSize);
	};
}	/* namespace name_udp */
}	/* namespace name_network */

