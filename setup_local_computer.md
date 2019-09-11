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

# Setup SDx on your own computer

To run (or build) these labs on your own computer, install SDAccel and the SDAccel license. For non-commercial/academic use, SDAccel licenses are available from the [Xilinx University Program](www.xilinx.com/university).

[Download SDAccel 2018.3](https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/sdaccel-development-environment/2018-3.html) and install the tools. 

[Download XRT and the U200 package](https://www.xilinx.com/products/boards-and-kits/alveo/u200.html#gettingStarted) for your computer, and install both packages.

### Setup the tools

Add the following to your environment setup. 

```csh
source /opt/xilinx/xrt/setup.(c)sh
source $XILINX_SDX/settings64.(c)sh
setenv PLATFORM_REPO_PATHS
```

```bash
export PLATFORM_REPO_PATHS=$ALVEO_PLATFROM_INSTALLATION_DIRECTORY
```