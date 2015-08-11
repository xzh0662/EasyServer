/*
 * ClientTcpServer.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef CLIENTTCP_CLIENTTCPSERVER_H_
#define CLIENTTCP_CLIENTTCPSERVER_H_

#include "TcpServer.h"
using namespace Easy;

class ClientTcpServer : public TcpServer
{
	typedef TcpServer super;
private:
	ClientTcpServer(void);

	virtual ~ClientTcpServer(void);

public:
	static ClientTcpServer *instance(void);
	static void destroy(void);

	int start(void);
	virtual int stop(void);

	virtual int receive(int fd, Buffer *buffer);
	virtual int send(int fd, Buffer *buffer);
private:
	static ClientTcpServer* instance_;
};

#define CLIENT_TCP_SERVER ClientTcpServer::instance()

#endif /* CLIENTTCP_CLIENTTCPSERVER_H_ */
