#pragma once
/**
* Class that wraps functionality of the MCP3008 Analog to Digital chip.  
* This class leverages the WiringPi library standardard on a Raspberry PI
**/
#include "tcSPI.h"

class tcMCP3008 : public tcSPI
{
public:
	/** 
	* Standard Contstructur.  
	* Defaults to interfacing with SPI Channel 0, if the MCP3008 is connected with SPI channel 1 then you need to use the other constructure
	**/
	tcMCP3008();   //defaults to SPI Channel 0

	/**
	* Constructur that accepts defining which SPI Channel and SPI Speed to use.
	*
	* @param asSPIChannel - references the SPI channel the MCP3008 is connected to (0 or 1)
	* @param asSPISpeed - speed in Hz.  500,000 - 32,000,000 Hz
	**/
	tcMCP3008(const int asSPIChannel, const int asSPISpeed = SPI_SPEED_DEFAULT);
	virtual ~tcMCP3008();

	/** 
	* Returns the integer value of the channel identified.
	*
	* @param asChannel References the channel of the 8 channel MCP3008.  Channel #'s are 0 - 7
	* @return The value on the MCP3008 runs between 0 and 1023
	**/
	int ReadValue(const int asChannel);

	/**
	* Provides the value in the form of a percentage between 0 and 100
	*
	* @param asChannel References the channel of the 8 channel MCP3008.  Channel #'s are 0 - 7
	* @return Returns a value between 0 and 100 representing a %.  This is useful with devices like
	* a potentiometer that has a min and max. 
	**/
	int ReadValuePercent(const int asChannel);

private:  //methods
	int AnalogRead(const int asChannel);
};

