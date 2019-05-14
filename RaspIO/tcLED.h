#pragma once
#include "tcGPIO.h"

namespace RaspIO
{
	class tcLED :
		public tcGPIO
	{
	public:
		tcLED();
		virtual ~tcLED();
	};

}