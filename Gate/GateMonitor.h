/*
 * GateMonitor.h
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#ifndef GATEMONITOR_H_
#define GATEMONITOR_H_

class GateMonitor
{
private:
	GateMonitor(void);
	~GateMonitor(void);

public:
	static GateMonitor *instance(void);
	static void destroy(void);

    int start(void);
    int stop(void);

private:
	static GateMonitor* instance_;
};

#define GATE_MONITOR GateMonitor::instance()



#endif /* GATEMONITOR_H_ */
