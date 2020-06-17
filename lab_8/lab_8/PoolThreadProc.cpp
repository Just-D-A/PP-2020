#include "PoolThreadProc.h"

DWORD WINAPI PoolThreadProc(CONST LPVOID lpParam)
{
	Task* task = (Task*)lpParam;
	task->Execute();

	ExitThread(0);
}