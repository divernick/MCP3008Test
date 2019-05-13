/*
 *  readMcp3008.c:
 *  read value from ADC MCP3008
 *
 * Requires: wiringPi (http://wiringpi.com)
 * Copyright (c) 2015 http://shaunsbennett.com/piblog
 ***********************************************************************
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "tcMCP3008.h"

#define	TRUE	            (1==1)
#define	FALSE	            (!TRUE)
#define CHAN_CONFIG_SINGLE  0
#define CHAN_CONFIG_DIFF    0

static int myFd;

char* usage = "Usage: mcp3008 all|analogChannel[1-8] [-l] [-ce1] [-d]";
// -l   = load SPI driver,  default: do not load
// -ce1  = spi analogChannel 1, default:  0
// -d   = differential analogChannel input, default: single ended

void loadSpiDriver()
{
	if (system("gpio load spi") == -1)
	{
		fprintf(stderr, "Can't load the SPI driver: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}



int main(int argc, char* argv[])
{
	int loadSpi = FALSE;
	int analogChannel = 0;
	int spiChannel = 0;
	int channelConfig = CHAN_CONFIG_SINGLE;

	

	if (argc < 2)
	{
		fprintf(stderr, "%s\n", usage);
		return 1;
	}
	if ((strcasecmp(argv[1], "all") == 0))
		argv[1] = "0";
	if ((sscanf(argv[1], "%i", &analogChannel) != 1) || analogChannel < 0 || analogChannel > 8)
	{
		printf("%s\n", usage);
		return 1;
	}
	int i;
	for (i = 2; i < argc; i++)
	{
		if (strcasecmp(argv[i], "-l") == 0 || strcasecmp(argv[i], "-load") == 0)
			loadSpi = TRUE;
		else if (strcasecmp(argv[i], "-ce1") == 0)
			spiChannel = 1;
		else if (strcasecmp(argv[i], "-d") == 0 || strcasecmp(argv[i], "-diff") == 0)
			channelConfig = CHAN_CONFIG_DIFF;
	}
	//
	if (loadSpi == TRUE)
		loadSpiDriver();

	tcMCP3008 lcADChip(spiChannel, SPI_SPEED_DEFAULT);
	//
	if (analogChannel > 0)
	{
		printf("MCP3008(CE%d,%s): analogChannel %d = %d\n", spiChannel, (channelConfig == CHAN_CONFIG_SINGLE)
			? "single-ended" : "differential", analogChannel, lcADChip.ReadValue(analogChannel-1));
	}
	else
	{
		do
		{
			for (i = 0; i < 8; i++)
			{
				printf("MCP3008(CE%d,%s): analogChannel %d = %d (%d%)\n", spiChannel, (channelConfig == CHAN_CONFIG_SINGLE)
					? "single-ended" : "differential", i + 1, lcADChip.ReadValue(i),lcADChip.ReadValuePercent(i));
			}
			delay(500);
		} while (true);
	}
	close(myFd);
	return 0;
}