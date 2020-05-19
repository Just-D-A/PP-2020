#include "BMP.h"

BMP::BMP(const std::string input, const std::string output, const int threadCount, const int coreCount, const int blurRadius)
	: m_input(input)
	, m_output(output)
	, m_threadCount(threadCount)
	, m_coreCount(coreCount)
	, m_blurRadius(blurRadius)
{
}

std::vector<rgb_t> GetPixels(const int height, const int width, const ThreadData& thread)
{
	std::vector<rgb_t> pixels;

	int blurRadius = thread.blurRadius;

	for (int i = height - blurRadius; i <= height + blurRadius; ++i)
	{
		for (int j = width - blurRadius; j <= width + blurRadius; ++j)
		{
			int minHeight = std::min(thread.indexFinishHeight - 1, std::max(i, 0));
			int minWidth = std::min(thread.indexFinisWidth - 1, std::max(j, 0));

			rgb_t pixel = thread.inputImage.get_pixel(minWidth, minHeight);
			pixels.push_back(pixel);
		}
	}

	return pixels;
}

void Blur(ThreadData& thread)
{
	for (int height = thread.indexStartHeight; height < thread.indexFinishHeight; ++height)
	{
		for (int width = thread.indexStartWidth; width < thread.indexFinisWidth; ++width)
		{
			std::vector<rgb_t> pixels = GetPixels(height, width, thread);

			int totalRed = 0, totalGreen = 0, totalBlue = 0;

			for (const auto& pixel : pixels)
			{
				totalRed += pixel.red;
				totalGreen += pixel.green;
				totalBlue += pixel.blue;
			}

			rgb_t colour;
			colour.red = (unsigned char)(totalRed / pixels.size());
			colour.green = (unsigned char)(totalGreen / pixels.size());
			colour.blue = (unsigned char)(totalBlue / pixels.size());

			thread.outputImage->set_pixel(width, height, colour);
		}
	}
}

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	ThreadData* thread = (ThreadData*)lpParam;

	int width = thread->inputImage.width();
	int height = thread->inputImage.height();
	int threadCount = thread->threadCount;
	int threadNumber = thread->threadNumber;

	int longWidth = width / threadCount;
	int longHeight = height / threadCount;

	for (int i = 0; i < threadCount; ++i)
	{
		int finishHeight = (threadNumber + 1) * longHeight;
		thread->indexStartHeight = threadNumber * longHeight;
		thread->indexFinishHeight = finishHeight + (threadNumber == threadCount - 1 ? height - finishHeight : 0);

		int finishWidth = (i + 1) * longWidth;
		thread->indexStartWidth = i * longWidth;
		thread->indexFinisWidth = finishHeight + (i == threadCount - 1 ? width - finishHeight : 0);
		
		Blur(*thread);
	}
	ExitThread(0);
}

std::vector<ThreadData> BMP::GetThreadsData(const bitmap_image& inputImage, bitmap_image* outputImage) const
{
	std::vector<ThreadData> threadsData;

	for (int i = 0; i < m_threadCount; ++i)
	{
		ThreadData threadData;
		threadData.inputImage = inputImage;
		threadData.outputImage = outputImage;
		threadData.blurRadius = m_blurRadius;
		threadData.threadCount = m_threadCount;
		threadData.threadNumber = i;

		threadsData.push_back(threadData);
	}

	return threadsData;
}

void BMP::Run()
{
	bitmap_image inputImage(m_input);

	if (!inputImage)
	{
		return;
	}

	bitmap_image outputImage(inputImage);

	std::vector<ThreadData> threadsData = GetThreadsData(inputImage, &outputImage);

	std::vector<HANDLE> handles(threadsData.size());
	int affinityMask = (1 << m_coreCount) - 1;
	for (size_t i = 0; i < threadsData.size(); ++i)
	{
		handles[i] = CreateThread(NULL, 0, &ThreadProc, &threadsData[i], CREATE_SUSPENDED, NULL);
		SetThreadAffinityMask(handles[i], affinityMask);
	}

	for (const auto& handle : handles)
	{
		ResumeThread(handle);
	}

	WaitForMultipleObjects((DWORD)handles.size(), handles.data(), true, INFINITE);
	outputImage.save_image(m_output);
}
