#include "testThread.h"



void testThread::run()
{
	cout << "this is child thread " << endl;
	Sleep(3);
	while (1)
	{
		Sleep(3000);
		break;
	}
	cout << "wake up, child thread is over." << endl;

}