#pragma once



#define SPI_SPEED_DEFAULT 1000000

class tcMCP3008
{
public:
	tcMCP3008();   //defaults to SPI Channel 0
	tcMCP3008(const int asSPIChannel, const int asSPISpeed);
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


private:	//methods
	int AnalogRead(const int asChannel);


private:	//members
	int mdFileDesc;
	int msSPIChannel;
	int msSPISPeed;
};

