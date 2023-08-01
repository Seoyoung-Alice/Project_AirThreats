#pragma once
#include <winsock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

// 다른곳으로 옮겨질 예정
#define MAX_BUF		512

namespace name_network
{
namespace name_udp
{
	class CUdpServer
	{
	public:
		CUdpServer();
		CUdpServer(std::string strServerAddr, int nPort);
		virtual ~CUdpServer();

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

