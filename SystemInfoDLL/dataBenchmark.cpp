#include "pch.h"
#include "dataBenchmark.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <psapi.h>
#include <winbase.h>
#include <filesystem>

using namespace std;

extern "C" DataBenchmark getDataBenchmark()
{
    DataBenchmark data_benchmark;
    const size_t dataSize = 1024 * 1024 * 1024; // 1 GB
    const string fileName = "C:\\Users\\Public\\Documents\\benchmark.bin";
    const size_t chunkSize = 256 * 1024 * 1024; // 256 MB

    // Write speed
    ofstream write_file(fileName, ios::binary);
    if (!write_file) {
        cerr << "Error: Cannot create file at " << fileName << endl;
        data_benchmark.writeSpeed = 0;
        data_benchmark.readSpeed = 0;
        return data_benchmark;
    }

    vector<char> chunk(chunkSize, 'A');
    size_t chunks = dataSize / chunkSize;

    auto start_time = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < chunks; ++i) {
        write_file.write(chunk.data(), chunkSize);
    }
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    write_file.close();

    data_benchmark.writeSpeed = (dataSize / (1024 * 1024)) / (duration / 1000.0);

    // Read speed
    ifstream read_file(fileName, ios::binary);
    if (!read_file) {
        cerr << "Error: Cannot open file " << fileName << endl;
        data_benchmark.writeSpeed = 0;
        data_benchmark.readSpeed = 0;
        return data_benchmark;
    }

    start_time = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < chunks; ++i) {
        read_file.read(chunk.data(), chunkSize);
    }
    end_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    read_file.close();

    data_benchmark.readSpeed = (dataSize / (1024 * 1024)) / (duration / 1000.0);

	// Delete file
    if (remove(fileName.c_str()) != 0) {
        cerr << "Error: Cannot delete file " << fileName << endl;
    }


    return data_benchmark;
}