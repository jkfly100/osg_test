#include "testThread.h"


#if 0
int main()
{
	testThread childThread;
	childThread.start();

	cout << "this is main thread.\n" << endl;

	childThread.join();

	if (!childThread.isRunning())
	{
		cout << "join success!" << endl;
	}
}
#endif

void CALLBACK print()
{
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	cout << "timeNow: " << sysTime.wSecond << endl;
}

int main()
{
	MSG msg;
		SetTimer(NULL, 1, 2000, (TIMERPROC)print);
		while (GetMessage(&msg, NULL, NULL, NULL))
		{
			if (msg.message == WM_TIMER)
			{
				TranslateMessage(&msg);///TranslateMessage函数将虚拟键消息转换成字符消息

				 /*该函数调度一个消息给窗口程序。通常调度从GetMessage取得的消息。
				  消息被调度到的窗口程序即是MainProc()函数*/
				DispatchMessage(&msg);
				//break; //此处最好有一个这个，不然貌似Killtimer结束不了定时器的样子.
			}
		}
		KillTimer(NULL, 1);
	return 0;
}