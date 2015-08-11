/*
 * GateMonitor.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */


#include "GateMonitor.h"
#include "ClientTcpServer.h"
//#include "SceneTcpClient.h"

GateMonitor::GateMonitor(void)
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

	return 0;
}

int GateMonitor::stop(void)
{
	CLIENT_TCP_SERVER->stop();
	//SCENE_TCP_CLIENT->stop();

	return 0;
}
