/*
 * main.cpp
 *
 *  Created on: Aug 11, 2015
 *      Author: root
 */

#include "GameSwitcher.h"
#include "stdlib.h"
#include "stdio.h"


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("argc < 2 is error");
		return -1;
	}

	printf("argc = %d\n", argc);
	printf("argv0 = %s argv1 = %s\n", argv[0], argv[1]);

	GAME_SWITCHER->start(atoi(argv[1]));

	return 0;
}


