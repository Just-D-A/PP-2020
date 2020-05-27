#pragma once
#include "LinkedList.h"
#include <Windows.h>
#include <mutex>

class LogBuffer {
public:
	LogBuffer();
	void push(std::string val, std::mutex& mtx);
	void checkEmpty();
private:
	LinkedList m_linkedList;
	int m_fileNum;
};