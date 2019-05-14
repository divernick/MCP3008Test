#pragma once
#include "tcGPIO.h"

namespace RaspIO
{
	class tcRelay :
		public tcGPIO
	{
	public:
		tcRelay();
		virtual ~tcRelay();
	};
}
