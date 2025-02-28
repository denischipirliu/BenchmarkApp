#include "pch.h"
#include "systeminfo.h"
#include "sysinfoapi.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <intrin.h>
#include <chrono>
#include <thread>

using namespace std;

int GetPhysicalCoreCount()
{
    DWORD length = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &length);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)malloc(length);
    if (!buffer) return 0;

    int physicalCoreCount = 0;
    if (GetLogicalProcessorInformationEx(RelationProcessorCore, buffer, &length))
    {
        SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info = buffer;
        while (length > 0)
        {
            if (info->Relationship == RelationProcessorCore)
                ++physicalCoreCount;
            length -= info->Size;
            info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)((char*)info + info->Size);
        }
    }
    free(buffer);
    return physicalCoreCount;
}

const char* getCPUModel()
{
    static char CPUBrandString[0x40];
    int CPUInfo[4] = { -1 };

    __cpuid(CPUInfo, 0x80000002);
    memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000003);
    memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
    __cpuid(CPUInfo, 0x80000004);
    memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));

    return CPUBrandString;
}

const char* getCPUArch()
{
    static char arch[64];

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

    if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		memcpy(arch, "x64 (AMD or Intel)", 18);
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM)
        memcpy(arch, "ARM", 3);
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64)
        memcpy(arch, "ARM64", 5);
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
		memcpy(arch, "Intel Itanium-based", 20);
    else if (sysInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		memcpy(arch, "x86", 3);
    else
		memcpy(arch, "Unknown", 7);
    
    return arch;
}

int getCPUClock()
{
    auto start_time = chrono::high_resolution_clock::now();
    unsigned long long start_cycles = __rdtsc();
    this_thread::sleep_for(chrono::seconds(1));
    auto end_time = chrono::high_resolution_clock::now();
    unsigned long long end_cycles = __rdtsc();

    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time).count();

    unsigned long long cpu_speed = end_cycles - start_cycles;

    return cpu_speed / duration / 1'000'000;
}

const char* getGPUModel()
{
    static char gpuModel[128];
    for (int i = 0; ; i++) {
        DISPLAY_DEVICEA dd = { sizeof(dd), 0 };
        BOOL f = EnumDisplayDevicesA(NULL, i, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
        if (!f)
            break;
        strncpy_s(gpuModel, dd.DeviceString, sizeof(gpuModel) - 1);
        gpuModel[sizeof(gpuModel) - 1] = '\0'; // Ensure null-termination
        return gpuModel;
    }
    return nullptr;
}

extern "C" DLL_EXPORT SystemInfo getSystemInfo()
{
    SystemInfo sys_info;

    // CPU model and architecture
    sys_info.CPU_model = getCPUModel();
    sys_info.CPU_arch = getCPUArch();

    // Logical and physical cores
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    sys_info.CPU_logical_cores = siSysInfo.dwNumberOfProcessors;
    sys_info.CPU_physical_cores = GetPhysicalCoreCount();

    // CPU clock
    sys_info.CPU_clock = getCPUClock();

    // RAM size
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    sys_info.RAM_size = statex.ullTotalPhys / 1024 / 1024;

	// RAM usage
	sys_info.RAM_load = statex.dwMemoryLoad;

	// GPU model
	sys_info.GPU_model = getGPUModel();

    return sys_info;
}

extern "C" DLL_EXPORT int updateCPUClock()
{
	return getCPUClock();
}

extern "C" DLL_EXPORT int updateRAMLoad()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return statex.dwMemoryLoad;
}
