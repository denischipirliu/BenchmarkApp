#pragma once

#define DLL_EXPORT __declspec(dllexport)

extern "C" {
	DLL_EXPORT int getSingleCoreCPUBenchmark();
	DLL_EXPORT int getMultiCoreCPUBenchmark();
}