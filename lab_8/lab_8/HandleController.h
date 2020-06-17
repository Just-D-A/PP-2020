#pragma once
#include "BMP.h"
#include "Pool.h"
#include <iostream>
#include <string>

using namespace std;

const int MIN_NUMBER_ARGUMENTS = 6;
const std::string ERROR_MESSAGE = "To learn how to use the program, enter: SchedulerBlurBmp.exe /";
const int BLUR_R = 5;

class HandleController
{
public:
	void Run(int argc, char* argv[]);
};