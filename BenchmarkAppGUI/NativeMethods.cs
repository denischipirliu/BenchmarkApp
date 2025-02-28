using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct SystemInfo
{
    public IntPtr CPU_model;
    public IntPtr CPU_arch;
    public int CPU_logical_cores;
    public int CPU_physical_cores;
    public int CPU_clock;
    public ulong RAM_size;
    public int RAM_load;
    public IntPtr GPU_model;
}

public struct DataBenchmark
{
    public int writeSpeed;
    public int readSpeed;
}

public static class NativeMethods
{
    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern SystemInfo getSystemInfo();

    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int updateCPUClock();

    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int updateRAMLoad();

    public static string GetCpuModelString(SystemInfo info)
    {
        return Marshal.PtrToStringAnsi(info.CPU_model);
    }

    public static string GetCpuArchString(SystemInfo info)
    {
        return Marshal.PtrToStringAnsi(info.CPU_arch);
    }

    public static string GetGpuModelString(SystemInfo info)
    {
        return Marshal.PtrToStringAnsi(info.GPU_model);
    }

    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern DataBenchmark getDataBenchmark();

    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getSingleCoreCPUBenchmark();

    [DllImport("BenchmarkAppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int getMultiCoreCPUBenchmark();


}

