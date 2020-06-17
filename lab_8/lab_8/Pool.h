#pragma once

#include "Task.h"
#include <vector>

class Pool
{
public:
	Pool(std::vector<Task*> tasks, unsigned threadsCount);

	void ExecuteTasks();

private:
	HANDLE* _handles;
	unsigned _tasksCount;
	unsigned _threadsCount;
};