#include "timer.h"

namespace test
{
	timer::timer(int initilaTime, int periodicTime, timer::timerCallBack && cb)
		: _cb(std::move(cb))
		, _initialTime(initilaTime)
		, _periodicTime(periodicTime)
		, _isStart(false)
		, _fd(creatThread())
	{}

	timer::~timer()
	{
		if (_isStart)
		{
			stop();
		}
	}

	void start()
	{

	}
}