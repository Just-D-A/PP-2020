#include "HandleController.h"
#include <ctime>
#include <iostream>


const int blurR = 5;
const std::string ErrorInput = "Input: file.exe <input image> <output image> <number threads> <number core> <threads prioritis>";

int main(int argc, char* argv[])
{
	std::clock_t start = std::clock();

	HandleController hc;
	hc.Run(argc, argv);

	std::clock_t end = std::clock();
	std::cout << "Runtime: " << std::difftime(end, start) << " ms" << std::endl;

	return 0;
}