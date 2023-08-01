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
	class CUdpClient
	{
	public:
		CUdpClient();
		CUdpClient(std::string strServerAddr, int nPort);
		virtual ~CUdpClient();

	private:
		sockaddr_in m_server;
		SOCKET m_clientSock;

		std::string m_strServerAddr;
		int m_nPort;

		int InitialWinSock();
		bool CreateSock();

	public:
		bool StartUdp();

		int RecvUdpMessage(char* pBuf, int nSize);
		int SendUdpMessage(char* pBuf, int& nSize);
	};
}	/* namespace name_udp */
}	/* namespace name_network */

