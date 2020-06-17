#include "LogBuffer.h"
#include <iostream>

LogBuffer::LogBuffer(std::mutex& mtx) :m_linkedList(LinkedList()), m_fileNum(0), m_mutex(mtx)
{
	overflow_event = CreateEvent(nullptr, TRUE, FALSE, TEXT("OverflowEvent"));
	StartThread();
}

void LogBuffer::push(std::string val) 
{	
	//ÊĞÈÒÈ×ÅÑÊÀß ÑÅÊÖÈß
	m_mutex.lock();
	if (m_linkedList.checkSize()) 
	{
		m_linkedList.append(val);
		
	} 
	else 
	{				
		//ñîîáùèòü â ïîòîê ìîíèòîğèíãà
		NotifyThread();
	}
	m_mutex.unlock();
	//ÊÎÍÅÖ ÊĞÈÒÈ×ÅÑÊÎÉ ÑÅÊÖÈÈ
}


void LogBuffer::StartThread()
{
	overflow_thread = CreateThread(nullptr, 0, &LogSizeMonitoringThread, static_cast<void*>(this), 0, nullptr);
}

void LogBuffer::NotifyThread()
{
	if (!SetEvent(overflow_event))
	{
		std::cout << "SetEvent failed";	
	}
	DWORD wait_result = WaitForSingleObject(overflow_thread, INFINITE);
	switch (wait_result)
	{
	case WAIT_OBJECT_0:
		ResetEvent(overflow_event);
		StartThread();
		break;
	default:
		std::cout <<"WaitForSingleObject failed";
	}
}

DWORD WINAPI LogBuffer::LogSizeMonitoringThread(CONST LPVOID lp_param)
{
	LogBuffer* context = static_cast<LogBuffer*>(lp_param);
	const DWORD wait_result = WaitForSingleObject(context->overflow_event, INFINITE);

	if (wait_result == WAIT_OBJECT_0)
	{
		context->m_linkedList.writeAndClearList(context->m_fileNum);
		context->m_fileNum++;;
	}

	ExitThread(EXIT_SUCCESS);
}

void LogBuffer::checkEmpty() 
{
	if (m_linkedList.getHead()) 
	{
		m_linkedList.itIsEnd();
		m_linkedList.writeAndClearList(m_fileNum);
	}
}