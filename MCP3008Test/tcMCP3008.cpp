#include "tcMCP3008.h"



 
tcMCP3008::tcMCP3008() :
	tcSPI(0, SPI_SPEED_DEFAULT){}

tcMCP3008::tcMCP3008(const int asSPIChannel,const int asSPISpeed) :
	tcSPI(asSPIChannel,asSPISpeed){}


tcMCP3008::~tcMCP3008()
{

}

int tcMCP3008::ReadValue(const int asChannel)
{
	return AnalogRead(asChannel);
}

int tcMCP3008::ReadValuePercent(const int asChannel)
{
	int lsResult = AnalogRead(asChannel);
	return (lsResult * 100) / 1023;
}

int tcMCP3008::AnalogRead(const int asChannel)
{
	if (asChannel < 0 || asChannel>7)
		return -1;
	unsigned char buffer[3] = { 1 }; // start bit
	buffer[1] = (asChannel) << 4;
	tcSPI::AnalogSPIRead(buffer, 3);
	return ((buffer[1] & 3) << 8) + buffer[2]; // get last 10 bits
}


