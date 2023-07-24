#include<iostream>
#include<process.h>
#include<Windows.h>

using namespace std;

int Value = 0;
int ValuePlusOne = 1;

int Cnt = 0;
bool isChecked = false;

CRITICAL_SECTION cs;

DWORD WINAPI ThFunc1(LPVOID IpParam);
DWORD WINAPI ThFunc2(LPVOID IpParam);

DWORD WINAPI ThFunc3(LPVOID IpParam);
DWORD WINAPI ThFunc4(LPVOID IpParam);

DWORD WINAPI ThFunc5(LPVOID IpParam);
DWORD WINAPI ThFunc6(LPVOID IpParam);

unsigned __stdcall ThFunc7(LPVOID IpParam);
unsigned __stdcall ThFunc8(LPVOID IpParam);

unsigned __stdcall ThFunc9(LPVOID IpParam);
unsigned __stdcall ThFunc10(LPVOID IpParam);
unsigned __stdcall ThFunc11(LPVOID IpParam);



const int Max_Count = 10000;
DWORD dwThIDs[3];
HANDLE hThreads[3];


int main()
{
	DWORD dwThID1, dwThID2;
	HANDLE hThread[2];

	unsigned long ulStackSize = 0;

	dwThID1 = 0;
	dwThID2 = 0;
	hThread[0] = NULL;
	hThread[1] = NULL;

	for (int i = 0; i < 3; i++)
	{
		dwThIDs[i] = 0;
		hThreads[i] = NULL;
	}


	InitializeCriticalSection(&cs);

	//hThread[0] = CreateThread(NULL, ulStackSize, ThFunc5,NULL,CREATE_SUSPENDED,&dwThID1);
	//hThread[1] = CreateThread(NULL, ulStackSize, ThFunc6,NULL,CREATE_SUSPENDED,&dwThID2);

	//ResumeThread(hThread[0]);
	//ResumeThread(hThread[1]);

	//WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//CloseHandle(hThread[0]);
	//CloseHandle(hThread[1]);

	hThreads[0] = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))ThFunc10, NULL, 0, (unsigned*)&dwThIDs[0]);
	hThreads[1] = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))ThFunc10, NULL, 0, (unsigned*)&dwThIDs[1]);
	hThreads[2] = (HANDLE)_beginthreadex(NULL, 0, (unsigned(__stdcall*)(void*))ThFunc10, NULL, 0, (unsigned*)&dwThIDs[2]);

	if (hThreads[0] == 0 || hThreads[1] == 0 || hThreads[2] == 0)
	{
		exit(1);
	}

	WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);

	for (int i = 0; i < 3; i++)
	{
		CloseHandle(hThreads[i]);
	}

	DeleteCriticalSection(&cs);

	return 0;
}

DWORD __stdcall ThFunc1(LPVOID IpParam)
{

	while (1)
	{
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
	}
	return 0;
}

DWORD __stdcall ThFunc2(LPVOID IpParam)
{
	while (1)
	{
		if ((Value + 1) != ValuePlusOne)
		{
			printf("%d\n", ++Cnt);
		}
	}
	return 0;
}

DWORD __stdcall ThFunc3(LPVOID IpParam)
{

	while (1)
	{
		isChecked = false;
		Value = rand() % 1000;
		ValuePlusOne = Value + 1;
		isChecked = true;
	}
	return 0;
}

DWORD __stdcall ThFunc4(LPVOID IpParam)
{
	while (1)
	{
		if (isChecked)
		{
			if ((Value + 1) != ValuePlusOne)
			{
				printf("%d\n", ++Cnt);
			}
		}
	}
	return 0;
}

DWORD __stdcall ThFunc5(LPVOID IpParam)
{

	while (1)
	{
		EnterCriticalSection(&cs);
		{
			Value = rand() % 1000;
			ValuePlusOne = Value + 1;
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

DWORD __stdcall ThFunc6(LPVOID IpParam)
{
	while (1)
	{
		EnterCriticalSection(&cs);
		{
			if ((Value + 1) != ValuePlusOne)
			{
				printf("%d\n", ++Cnt);
			}
		}
		LeaveCriticalSection(&cs);
	}
	return 0;
}

unsigned __stdcall ThFunc7(LPVOID IpParam)
{
	while (Cnt<Max_Count)
	{
		EnterCriticalSection(&cs);
		{
			Value = rand() % 1000;
			ValuePlusOne = Value + 1;
		}
		LeaveCriticalSection(&cs);
		Sleep(1); // 올바르게 switching 발생 1:1
	}
	return 0;
}

unsigned __stdcall ThFunc8(LPVOID IpParam)
{
	while (Cnt < Max_Count)
	{
		EnterCriticalSection(&cs);
		{
			if ((Value + 1) != ValuePlusOne)
			{
				printf("%d\n", ++Cnt);
			}

			else
			{
				++Cnt;
			}
		}
		LeaveCriticalSection(&cs);
		Sleep(1);
	}
	return 0;
}

unsigned __stdcall ThFunc9(LPVOID IpParam)
{
	//while (1)
	{
		EnterCriticalSection(&cs);
		printf("---------------------------------------\n");
		LeaveCriticalSection(&cs);
		Sleep(1);
	}

	return 0;
}

unsigned __stdcall ThFunc10(LPVOID IpParam)
{
	//while (1)
	{
		EnterCriticalSection(&cs);
		printf("#######################################\n");
		LeaveCriticalSection(&cs);
		Sleep(1);
	}

	return 0;
}

unsigned __stdcall ThFunc11(LPVOID IpParam)
{
	//while (1)
	{
		EnterCriticalSection(&cs);
		printf("000000000000000000000000000000000000000\n");
		LeaveCriticalSection(&cs);
		Sleep(1);
	}

	return 0;
}
