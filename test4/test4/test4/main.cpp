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
				TranslateMessage(&msg);///TranslateMessage�������������Ϣת�����ַ���Ϣ

				 /*�ú�������һ����Ϣ�����ڳ���ͨ�����ȴ�GetMessageȡ�õ���Ϣ��
				  ��Ϣ�����ȵ��Ĵ��ڳ�����MainProc()����*/
				DispatchMessage(&msg);
				//break; //�˴������һ���������Ȼò��Killtimer�������˶�ʱ��������.
			}
		}
		KillTimer(NULL, 1);
	return 0;
}