#pragma once
/**
* Class that wraps functionality of SPI GPIO functionality.
* This class leverages the WiringPi library standardard on a Raspberry PI
**/

#define SPI_SPEED_DEFAULT 1000000

class tcSPI
{
public:
	/**
	* Standard Contstructur.
	* Defaults to interfacing with SPI Channel 0, if the MCP3008 is connected with SPI channel 1 then you need to use the other constructure
	**/
	tcSPI();
	
	/**
	* Constructur that accepts defining which SPI Channel and SPI Speed to use.
	*
	* @param asSPIChannel - references the SPI channel the MCP3008 is connected to (0 or 1)
	* @param asSPISpeed - speed in Hz.  500,000 - 32,000,000 Hz
	**/
	tcSPI(const int asSPIChannel, const int asSPISpeed);
	virtual ~tcSPI();

	int GetSPIChannel(void);
	int GetSPISpeed(void);

protected:	//methods

	/** 
	* Wrapper of WiringPI wiringPiSPIDataRW function call
	**/
	int AnalogSPIRead(unsigned char* buffer, int len);


private:	//members
	int mdFileDesc;
	int msSPIChannel;
	int msSPISPeed;
};

