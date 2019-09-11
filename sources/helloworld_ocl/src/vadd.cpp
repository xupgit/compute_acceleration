/*******************************************************************************
Vendor: Xilinx
Associated Filename: vadd.cpp
Purpose: SDAccel vector addition

*******************************************************************************
Copyright (C) 2017 XILINX, Inc.

This file contains confidential and proprietary information of Xilinx, Inc. and
is protected under U.S. and international copyright and other intellectual
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials
distributed herewith. Except as otherwise provided in a valid license issued to
you by Xilinx, and to the maximum extent permitted by applicable law:
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY,
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether
in contract or tort, including negligence, or under any other theory of
liability) for any loss or damage of any kind or nature related to, arising under
or in connection with these materials, including for any direct, or any indirect,
special, incidental, or consequential loss or damage (including loss of data,
profits, goodwill, or any type of loss or damage suffered as a result of any
action brought by a third party) even if such damage or loss was reasonably
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any
application requiring fail-safe performance, such as life-support or safety
devices or systems, Class III medical devices, nuclear facilities, applications
related to the deployment of airbags, or any other applications that could lead
to death, personal injury, or severe property or environmental damage
(individually and collectively, "Critical Applications"). Customer assumes the
sole risk and liability of any use of Xilinx products in Critical Applications,
subject only to applicable laws and regulations governing limitations on product
liability.

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT
ALL TIMES.

*******************************************************************************/
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <numeric>
#include "vadd.h"

static const int DATA_SIZE = 4096;

int main(int argc, char* argv[]) {
    
    const char *kernel_name = "krnl_vadd"; // Open CL Kernel name
    int init_value; // Initialization value for vector arrays
    std::vector<cl::Device> devices; // OpenCL devices
    cl::Device device;

    if(argc != 2 and argc != 3) {
        std::cout << "Usage: " << argv[0] <<"<xclbin> [vector initialization value]\n" << std::endl;
        return EXIT_FAILURE;
    }
    char* xclbinFilename = argv[1];
    char* p;

    // Check if vector init value was passed, and convert to int, otherwise default to 0
    if(argc == 3){
        errno = 0;
        long conv = strtol(argv[2], &p, 10);
        if(errno !=0 || *p != '\0' || conv > INT_MAX){
            printf("Invalid vector initialization value %s\nValue should be an Integer\nExiting\n", argv[2]);
        return -1;
        }else{
            init_value = conv;
        }
    }else{
        init_value = 0;
    }

    // Compute the size of array in bytes
    size_t size_in_bytes = DATA_SIZE * sizeof(int);
    
    // Creates a vector of DATA_SIZE elements 
    // using customized allocator for getting buffer alignment to 4k boundary
    std::vector<int,aligned_allocator<int>> source_a(DATA_SIZE);
    std::vector<int,aligned_allocator<int>> source_b(DATA_SIZE);
    std::vector<int,aligned_allocator<int>> source_results(DATA_SIZE);
    
    // Read in a user defined initial value for the arrays

    printf("Init arrays\n");
    // Initialize the arrays
    std::iota (std::begin(source_a), std::end(source_a), init_value);
    std::iota (std::begin(source_b), std::end(source_b), init_value);
    
    // Check for the Xilinx device on the current platform
    std::cout << "Get Xilinx platform" << std::endl;
    get_xilinx_platform(&device, &devices);

    // Creating Context and Command Queue for selected device
    cl::Context context(device);
    cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE);
    cl::Kernel krnl_vector_add;
    
    krnl_vector_add = load_xcl_bin(kernel_name, xclbinFilename, &context, &devices);
    
    // Allocate memory on the Device. The cl::Buffer objects can
    // be used to reference the memory locations on the device. 
    cl::Buffer buffer_a(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_a.data());
    cl::Buffer buffer_b(context, CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY,  
            size_in_bytes, source_b.data());
    cl::Buffer buffer_result(context, CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, 
            size_in_bytes, source_results.data());
    
    // Data will be transferred from host memory over PCIe to the FPGA on-board
    // DDR memory.
    q.enqueueMigrateMemObjects({buffer_a,buffer_b},0/* 0 means from host*/);

    // set the kernel Arguments
    int narg=0;
    krnl_vector_add.setArg(narg++,buffer_a);
    krnl_vector_add.setArg(narg++,buffer_b);
    krnl_vector_add.setArg(narg++,buffer_result);
    krnl_vector_add.setArg(narg++,DATA_SIZE);

    /*
       Launch the Kernel
    */
    q.enqueueTask(krnl_vector_add);

    // Get the results: Transfer data from FPGA DDR to host memory "source_results"
    q.enqueueMigrateMemObjects({buffer_result},CL_MIGRATE_MEM_OBJECT_HOST);
    q.finish();

    // Verify the result
    int match = 0;
    for (int i = 0; i < DATA_SIZE; i++) {
        int host_result = source_a[i] + source_b[i];
        printf(results_message.c_str(), source_a[i], source_b[i], source_results[i]);
        if (source_results[i] != host_result) {
            printf(error_message.c_str(), i, host_result, source_results[i]);
            match = 1;
            break;
        }
    }

    std::cout << "TEST " << (match ? "FAILED" : "PASSED") << std::endl; 
    return (match ? EXIT_FAILURE :  EXIT_SUCCESS);

}
