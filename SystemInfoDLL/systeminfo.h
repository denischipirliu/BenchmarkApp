#pragma once

#define DLL_EXPORT __declspec(dllexport)

extern "C" {

    struct SystemInfo {
        const char* CPU_model;
        const char* CPU_arch;
        int CPU_logical_cores;
        int CPU_physical_cores;
        int CPU_clock;
        unsigned long long RAM_size;
		int RAM_load;
		const char* GPU_model;
    };

    DLL_EXPORT SystemInfo getSystemInfo();
	DLL_EXPORT int updateCPUClock();
	DLL_EXPORT int updateRAMLoad();
}
