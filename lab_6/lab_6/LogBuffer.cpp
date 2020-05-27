#include "LogBuffer.h"

//#include <synchapi.h>

CRITICAL_SECTION critsect;
LogBuffer::LogBuffer():m_linkedList(LinkedList()), m_fileNum(0) {
	
}

void LogBuffer::push(std::string val, std::mutex& mtx) {
	//йпхрхвеяйюъ яейжхъ
	mtx.lock();
	if (m_linkedList.checkSize()) {
		m_linkedList.append(val);
	}
	else {
		m_linkedList.writeAndClearList(m_fileNum);
		m_linkedList.append(val);
		m_fileNum++;

	}
	mtx.unlock();
	//йнмеж йпхрхвеяйни яейжхх
}

void LogBuffer::checkEmpty() {
	if (m_linkedList.getHead()) {
		m_linkedList.writeAndClearList(m_fileNum);
	}
}