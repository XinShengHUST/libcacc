/*
 * Copyright (C) 2015, Nils Moehrle
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms
 * of the BSD 3-Clause license. See the LICENSE.txt file for details.
 */

#ifndef CACC_UTIL_HEADER
#define CACC_UTIL_HEADER

#include <iostream>

#include "defines.h"

#define TERM_WIDTH 76

CACC_NAMESPACE_BEGIN

void
print_cuda_devices(void) {
    int count;
    CHECK(cudaGetDeviceCount(&count));
    std::cout << "Found " << count << " CUDA Devices:" << std::endl;
    std::cout << std::string(TERM_WIDTH, '=') << std::endl;
    for (int i = 0; i < count; ++i) {
        cudaDeviceProp prop;
        CHECK(cudaGetDeviceProperties(&prop, i));
        std::cout << std::string(TERM_WIDTH, '-') << std::endl;    
        std::cout << "Device:\t" << prop.name << std::endl; 
        std::cout << std::string(TERM_WIDTH, '-') << std::endl;
        std::cout << "\tCompute Capability:\t" << prop.major <<
            "." << prop.minor << std::endl 
            << "\tMultiprocessor Count:\t"
            << prop.multiProcessorCount << std::endl 
            << "\tGPU Clock Rate:\t\t"
            << prop.clockRate / 1000 << " Mhz" << std::endl 
            << "\tTotal Global Memory:\t"
            << prop.totalGlobalMem / (2 << 20) << " MB" << std::endl 
            << "\tL2 Cache Size:\t\t"
            << prop.l2CacheSize / (2 << 10) << " KB" << std::endl 
            << "\tMax Block Size:\t\t"
            << prop.maxThreadsDim[0] << "x"
            << prop.maxThreadsDim[1] << "x"
            << prop.maxThreadsDim[2] << std::endl
            << "\tMax Threads Per Block:\t"
            << prop.maxThreadsPerBlock << std::endl 
            << "\tShared Memory Size:\t"
            << prop.sharedMemPerBlock / (2 << 10) << " KB" << std::endl; 
    }
    std::cout << std::string(TERM_WIDTH, '=') << std::endl;
}
    
int
select_cuda_device(int major, int minor) {
    int device;
    cudaDeviceProp prop;
    prop.major = major;
    prop.minor = minor;
    CHECK(cudaChooseDevice(&device, &prop));
    CHECK(cudaGetDeviceProperties(&prop, device));
    std::cout << "Using " << prop.name << " as CUDA device" << std::endl;
    CHECK(cudaSetDevice(device));
    return device;
}

CACC_NAMESPACE_END

#endif /* CACC_UTIL_HEADER */
