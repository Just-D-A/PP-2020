#pragma once
#include <windows.h>
#include "BMP.h"

class Task
{
public:
	 Task(BMP bmp): m_bmp(bmp) {}
	~Task() = default;

	void Execute() {
		m_bmp.Run();
	}

	private:
		BMP m_bmp;
};
