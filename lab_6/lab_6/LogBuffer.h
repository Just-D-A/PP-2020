#pragma once
#include "LinkedList.h"
#include <windows.h>
#include <mutex>

class LogBuffer {
public:
	LogBuffer(std::mutex& mtx);
	void push(std::string val);
	void checkEmpty();
	void NotifyThread();
	void StartThread();
	
	
private:
	static DWORD WINAPI LogSizeMonitoringThread(CONST LPVOID lp_param);
	LinkedList m_linkedList;
	int m_fileNum;
	std::mutex& m_mutex;
	HANDLE overflow_event;
	HANDLE overflow_thread;
};