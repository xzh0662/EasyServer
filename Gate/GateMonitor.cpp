/*
 * GateMonitor.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */


#include "GateMonitor.h"
#include "ClientTcpServer.h"
//#include "SceneTcpClient.h"
#include "SsdbClient.h"
#include "GameSwitcher.h"

GateMonitor::GateMonitor(void)
	: ssdbClient_(0)
{

}

GateMonitor::~GateMonitor(void)
{

}

GateMonitor* GateMonitor::instance_ = 0;

GateMonitor* GateMonitor::instance(void)
{
    if (instance_ == 0)
    {
        instance_ = new GateMonitor();
    }
    return instance_;
}

void GateMonitor::destroy(void)
{
    if (instance_ != 0)
    {
        delete instance_;
        instance_ = 0;
    }
}

int GateMonitor::start(void)
{
	CLIENT_TCP_SERVER->start();
	//SCENE_TCP_CLIENT->start();

	this->ssdbClient_ = new SsdbClient();
	InetAddr addr(8888);
	this->ssdbClient_->eventBase(GAME_SWITCHER->eventBase());
	this->ssdbClient_->connect(addr);
	//for(int i = 0; i < 2000; ++i)
	//{
		this->ssdbClient_->get("key");
	//}
		this->ssdbClient_->get("key11");
	return 0;
}

int GateMonitor::stop(void)
{
	CLIENT_TCP_SERVER->stop();
	//SCENE_TCP_CLIENT->stop();

	if (this->ssdbClient_ != 0)
	{
		delete this->ssdbClient_;
	}
	return 0;
}
