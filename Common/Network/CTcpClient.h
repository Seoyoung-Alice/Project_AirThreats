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
	class CTcpClient
	{
	public:
		CTcpClient();
		CTcpClient(std::string strServerAddr, int nPort);
		virtual ~CTcpClient();

	private:
		sockaddr_in m_server;
		SOCKET m_clientSock;

		std::string m_strServerAddr;
		int m_nPort;

		int InitialWinSock();
		bool CreateSock();
		int Connect();

	public:
		bool StartUdp();
		bool ReConnect();

		int RecvUdpMessage(char* pBuf, int nSize);
		int SendUdpMessage(char* pBuf, int& nSize);
	};
}	/* namespace name_tcp */
}	/* namespace name_network */

