#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include <Windows.h>
#include <iostream>
#include <functional>
#include <Windows.h>

namespace test
{
	class timer
	{
		using timerCallBack = std::function<void(void)>;
	public:
		timer(int initilaTime, int periodicTime, timer::timerCallBack && cb);
		~timer();

		void start();
		void stop();

	private:
		int creatThread();
		void setTimer(int initialTime, int periodicTime);

	private:
		timerCallBack _cb;
		int _fd;
		int _initialTime;
		int _periodicTime;
		bool _isStart;
		timerCallBack _cb;
	};

}

#endif // !__TIMER_H__


