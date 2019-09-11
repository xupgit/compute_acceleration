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

# Setup SDx

There are two main parts to this tutorial - using the [Xilinx SDx software](https://www.xilinx.com/products/design-tools/software-zone/sdaccel.html) and building (compiling) designs, and using and testing those designs in hardware. 

You can run this tutorial in different ways. 

* If you have an Alveo board, you can run all parts of the tutorial on a local machine. 

* You can use the SDx software in the cloud, with hardware in the cloud (AWS or Nimbix).

* You can use the SDx software on a local machine for building designs, and only switch to the cloud to test in hardware.

This tutorial shows how to use SDx with either AWS EC2 F1 or Alveo U200 (locally, or in the Nimbix cloud). Sources and precompiled and solutions are provided for AWS EC2 F1 x2.large and Alveo U200. You may be able to use the SDx tutorial instructions with other cloud providers, and other hardware. 

Once you have decided how you want to run the tutorial, follow the appropriate instructions below. 

## Local computer 

To use your own computer, [install and set up SDx and install the Alveo U200 packages](./setup_local_computer.md)

## Use Nimbix (Alveo)

The Xilinx SDx tools and Alveo U200 hardware is available in the Nimbix cloud. Use the following instructions to [connect to a Nimbix Alveo instance](./setup_nimbix.md). A [free 100 hr Alveo trial](https://www.nimbix.net/alveo/) is currently available from Nimbix. This is the easiest way to work through this tutorial with Alveo U200 hardware. However, please note the debug lab is not currently supported on Nimbix as the Xilinx Virtual Cable is not available. 

## AWS EC2 F1

An [FPGA Developer AMI](https://aws.amazon.com/marketplace/pp/B06VVYBLZZ) (Amazon Machine Image) is available with the Xilinx SDx software preinstalled. This can be used to target AWS EC2 F1 hardware. An AMI is like a Virtual Machine image. You can use this AMI and the following instructions to [set up and connect to an AWS instance](./setup_aws.md)

You can also install Xilinx SDx on your local machine, build design offline, and use AWS F1 hardware for testing. See the Amazon guide to using [AWS EC2 FPGA Development Kit](https://github.com/aws/aws-fpga) for details on setting up your machine. 

## XUP AWS Tutorial

If you are attending a live instructor-led XUP AWS tutorial, preconfigured AWS F1 instances will be provided for you. Use the following instructions to [connect to your assigned AWS XUP tutorial instance](./setup_xup_aws_workshop.md)

# Getting started with the tutorials

Once you have setup your computer/cloud instance, you can *git clone* this repository to get started running the tutorial. The repository includes these instructions, and also a copy of source files, and solutions you will need for the tutorial. 

The tutorial assumes you will clone this repository to your Linux home area. If you choose to clone it somewhere else, you will need to adjust the path where specified in the tutorial instructions.

**This repository does not exist yet. The material currently exists here: <https://github.com/cathalmccabe/awslabs/tree/sdaccel> **

```console
   cd ~
   git clone https://github.com/xupgit/sdxlabs
```

Proceed to the first lab [introducing SDx](sdx_introduction.md) 



