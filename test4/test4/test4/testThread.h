#pragma once
#include <OpenThreads/Thread>
#include <iostream>
#include <Windows.h>

using namespace std;
class testThread
	: public OpenThreads::Thread
{
public:
	virtual void run();
};

class timers
{
public:
	timers();
	~timers();

private:

};


