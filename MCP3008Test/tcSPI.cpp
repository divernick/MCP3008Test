#include "tcSPI.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_SPEED_DEFAULT 1000000


tcSPI::tcSPI()
{
	tcSPI(0, SPI_SPEED_DEFAULT);
}


tcSPI::tcSPI(const int asSPIChannel, const int asSPISpeed)
{
	msSPIChannel = asSPIChannel;
	msSPISPeed = asSPISpeed;

	wiringPiSetup();
	if ((mdFileDesc = wiringPiSPISetup(msSPIChannel, msSPISPeed)) < 0)
	{
		fprintf(stderr, "Can't open the SPI bus: %s\n", strerror(errno));
		//to do
		// Add throwing an exception
	}
}

tcSPI::~tcSPI()
{
	close(mdFileDesc);
}

int tcSPI::GetSPIChannel(void)
{
	return msSPIChannel;
}

int tcSPI::GetSPISpeed(void)
{
	return msSPISPeed;
}

int tcSPI::AnalogSPIRead(unsigned char* buffer, int len)
{
	return wiringPiSPIDataRW(msSPIChannel, buffer, len);
}
