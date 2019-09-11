<table style="width:100%">
  <tr>
    <th width="100%" colspan=6><h2>XUP SDx Labs (2018.3)</h2></th>
  </tr>
  <tr>
    <td align="center"><a href="setup_sdx.md">1. Setup SDx</a></td>
    <td align="center"><a href="sdx_introduction.md">2. Introduction to SDx</a></td>
    <td align="center"><a href="Optimization_lab.md">3. Optimization</a></td>
    <td align="center"><a href="rtl_kernel_wizard_lab.md">4. RTL Kernel Wizard</a></td>
    <td align="center"><a href="debug_lab.md">5. Debugging</a></td>
    <td align="center"><a href="sources/helloworld_ocl/command_line.ipynb">6. SDx command line</a></td>
  </tr>
</table>

### Introduction

Welcome to the XUP SDx tutorial. These labs will provide hands-on experience using the SDx software tools with Xilinx FPGA hardware. 

The SDx tools can be run on your local machine, or in the cloud (e.g. AWS or Nimbix). 

The tutorial instructions target the following hardware and software:

* SDx 2018.3
* AWS EC2 F1 f1.2xlarge (cloud)
* Alveo U200 (local board, or cloud)

You can build designs locally or in the cloud, and test on hardware locally (if you have an Alveo board) or in the cloud (AWS EC2 F1, Nimbix Alveo U200).

You will learn how to develop applications using the SDx development environment that supports OpenCL/C/C++ and RTL kernels.

#### Overview of the SDx flow

![alt tag](./images/f1_platform.png)


1. SDx is the development environment used to create host applications and hardware accelerators. It includes host CPU and FPGA compilers, and profiling and debugging tools.
2. The host application can be written in C or C++ and uses the OpenCL API or the XRT (Xilinx Runtime Library) to interact with the accelerated hardware functions running in the FPGA. The accelerated hardware functions (also referred to as kernels) can be written in C, C++, OpenCL or RTL.


#### Tutorial overview

 It is recommended to complete each lab before proceeding to the next.

* [**Setup SDx**](setup_sdx.md)
This will show you how to setup SDx on your own machine, or how to use it in the cloud (instructions are provided for AWS and Nimbix clouds).

* [**Introduction to SDx**](sdx_introduction.md)
This lab guides you through the steps involved in using a GUI flow to create an SDx project. After creating a project, you will run CPU and hardware emulation to verify the functionality. You will then use an AWS F1 instance to validate the design on F1.

* [**Optimization**](Optimization_lab.md)
This lab guides you through the steps involved in creating a project and adding a kernel function. After creating a project, you will run CPU and hardware emulation to verify the functionality, analyze various generated reports and then apply techniques both on host and kernel side to improve throughput and data transfer rate.

* [**RTL-Kernel Wizard**](rtl_kernel_wizard_lab.md)
This lab guides you through the steps involved in using a RTL Kernel wizard to wrap a user RTL-based IP so the generated IP can be used in SDx project.

* [**Debug**](debug_lab.md)
This lab will show you how to carry out host application debug, and debug of the hardware kernel.

* [**SDx command line**](command_line.md)
This lab guides you through the steps involved in using the SDx command line (using a Makefile) to build and perform CPU and hardware emulation of your design. You will then test the design using FPGA hardware. 

---------------------------------------


When you have setup your instance, go to the first lab [Introduction to SDx](sdx_introduction.md)

