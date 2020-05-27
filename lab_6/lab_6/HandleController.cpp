#pragma once
#include "HandleController.h";
void HandleController::Run(int argc, char* argv[])
{
	if (strcmp(argv[1], "/") == 0)
	{
		std::cout << "lab_6.exe <input image> <output image> <number threads> <number core> <threads priorities>\n"
			"Priority types:\n"
			"-1 - below normal\n 0 - normal\n 1 - above normal\n";
		return;
	}

	if (argc < MIN_NUMBER_ARGUMENTS)
	{
		throw std::invalid_argument("The number of arguments does not match the task condition\n" + ERROR_MESSAGE);
	}

	std::string inputImage = argv[1];
	std::string outputImage = argv[2];

	int threadCount = atoi(argv[3]);
	int coreCount = atoi(argv[4]);

	if (argc != MIN_NUMBER_ARGUMENTS + threadCount)
	{
		throw std::invalid_argument("The number of priorities should be the same as the number of threads\n" + ERROR_MESSAGE);
	}

	std::vector<int> threadPriorities(threadCount);

	for (size_t i = 0; i < threadPriorities.size(); ++i)
	{
		threadPriorities[i] = atoi(argv[MIN_NUMBER_ARGUMENTS + i]);
	}

	BMP blurBmp(inputImage, outputImage, threadCount, coreCount, BLUR_R, threadPriorities);
	blurBmp.Run();
}