#include "BMP.h"
#include <iostream>

const int MIN_NUMBER_ARGUMENTS = 5;
const std::string ERROR_MESSAGE = "To learn how to use the program, enter: SchedulerBlurBmp.exe /";
const int BLUR_R = 5;

class HandleController
{
public:
	void Run(int argc, char* argv[]);
};

