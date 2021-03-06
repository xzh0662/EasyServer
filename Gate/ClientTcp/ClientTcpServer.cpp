/*
 * ClientTcpServer.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#include "ClientTcpServer.h"
#include "GameSwitcher.h"
#include "stdio.h"
#include "InetAddr.h"
#include "Buffer.h"

ClientTcpServer::ClientTcpServer(void)
{

}

ClientTcpServer:: ~ClientTcpServer(void)
{

}

ClientTcpServer* ClientTcpServer::instance_ = 0;

ClientTcpServer* ClientTcpServer::instance(void)
{
    if (instance_ == 0)
    {
        instance_ = new ClientTcpServer();
    }
    return instance_;
}

void ClientTcpServer::destroy(void)
{
    if (instance_ != 0)
    {
        delete instance_;
        instance_ = 0;
    }
}

int ClientTcpServer::start(void)
{
	this->eventBase(GAME_SWITCHER->eventBase());
	InetAddr addr(1234);
	this->listen(addr);
	return 0;
}

int ClientTcpServer::stop(void)
{
	super::stop();
	return 0;
}

int ClientTcpServer::receive(int fd, Buffer *buffer)
{
	if (super::receive(fd, buffer) != 0 )
	{
		return -1;
	}
	//buffer->addBeginShort(50);

	printf("buffer len %d\n", buffer->Length());
	std::string str;
	*buffer >> str;

	printf("ClientTcpServer::receive %s\n", str.c_str());

	{
		Buffer *buf;
		BUFFER_NEW_RETURN(buf, 1024, -1);
		*buf << str;
		this->send(fd, buf);
	}
	return 0;
}

int ClientTcpServer::send(int fd, Buffer *buffer)
{

	return super::send(fd, buffer);
}

