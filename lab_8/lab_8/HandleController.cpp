#include "HandleController.h";
#include "Task.h"

vector<BMP> filesBMP;
int x;

void HandleController::Run(int argc, char* argv[])
{
	if (strcmp(argv[1], "/") == 0)
	{
		std::cout << "lab_8.exe <Processing type> <input image> <output image> <number threads> <number core> <threads priorities>\n"			
			"Processing type:\n"
			"0 - normal\n 1 - with pool\n"
			"Priority types:\n"
			"-1 - below normal\n 0 - normal\n 1 - above normal\n";
		return;	
	}

	if (argc < MIN_NUMBER_ARGUMENTS)
	{
		throw std::invalid_argument("The number of arguments does not match the task condition\n" + ERROR_MESSAGE);
	}

	WIN32_FIND_DATAA wfd;
	HANDLE const hFind = FindFirstFileA(string(string(argv[2]) + "\\*").data(), &wfd);
	vector<string> infileNames;
	vector<string> outfileNames;
	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			string fileName = &wfd.cFileName[0];
			if (fileName.size() >= 4)
			{
				infileNames.push_back(string(argv[2]) + "\\" + fileName);
				fileName = fileName.substr(0, fileName.find("."));
				outfileNames.push_back(string(argv[3]) + "\\" + fileName + "_blured.bmp");
			}
		} while (FindNextFileA(hFind, &wfd) != NULL);
		FindClose(hFind);
	}
	int threadCount = atoi(argv[4]);
	int coreCount = atoi(argv[5]);

	if (argc != MIN_NUMBER_ARGUMENTS + threadCount)
	{
		throw std::invalid_argument("The number of priorities should be the same as the number of threads\n" + ERROR_MESSAGE);
	}

	std::vector<int> threadPriorities(threadCount);

	for (size_t i = 0; i < threadPriorities.size(); ++i)
	{
		threadPriorities[i] = atoi(argv[MIN_NUMBER_ARGUMENTS + i]);
	}
	if (string(argv[1]) == "0")
	{
		for (size_t i = 0; i < infileNames.size(); i++)
		{
			BMP blurBmp(infileNames[i], outfileNames[i], threadCount, coreCount, BLUR_R, threadPriorities);
			blurBmp.Run();
		}
	} 
	else if (string(argv[1]) == "1")
	{		
		vector<Task*> tasks;
		for (size_t i = 0; i < infileNames.size(); i++)
		{
			BMP blurBmp(infileNames[i], outfileNames[i], threadCount, coreCount, BLUR_R, threadPriorities);
			tasks.push_back(new Task(blurBmp));
		}
		Pool pool(tasks, tasks.size());
		
		pool.ExecuteTasks();
	}
	else 
	{
		std::cout << argv[1];
		return;
	}
}