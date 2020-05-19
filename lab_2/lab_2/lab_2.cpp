#include "BMP.h"
#include <ctime>
#include <iostream>
//#include <string>

const int blurR = 5;
const std::string ErrorInput = "Input: file.exe <input image> <output image> <number threads> <number core>";

int main(int argc, char* argv[])
{
	std::clock_t start = std::clock();
	if (argc != 5)
	{
		std::cout << ErrorInput << std::endl;
		return 1;
	}

	std::string inputImg;
	std::string outputImg;
	int threadCount;
	int coreCount;
	

	try
	{
		inputImg = argv[1];
		outputImg = argv[2];
		threadCount = std::stoi(argv[3]);
		coreCount = std::stoi(argv[4]);
		
	}
	catch (const std::invalid_argument)
	{
		return 1;
	}

	BMP blurBmp(inputImg, outputImg, threadCount, coreCount, blurR);
	blurBmp.Run();

	std::clock_t end = std::clock();
	std::cout << "Runtime: " << std::difftime(end, start) << " ms" << std::endl;

	return 0;
}