#pragma once

#define DLL_EXPORT __declspec(dllexport)

extern "C" {
	struct DataBenchmark {
		int writeSpeed;
		int readSpeed;
	};

	DLL_EXPORT DataBenchmark getDataBenchmark();
}