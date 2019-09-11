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

# Connecting to AWS

To get started with AWS, you will need an Amazon account. You will also need AWS credit to run the tutorial. If you are a professor or a student, you may be eligible to free credit by registering with [AWS educate](https://aws.amazon.com/education/awseducate/). 



## Set up an AWS instance

Use the following guide to setup and AWS instance. 

<https://docs.aws.amazon.com/efs/latest/ug/gs-step-one-create-ec2-resources.html>

Make sure to use the FPGA Developer AMI. Version 1.6.0 includes the Xilinx SDx 2018.3 tools that this tutorial is based on: <https://aws.amazon.com/marketplace/pp/B06VVYBLZZ>

### Login into the AWS and starting an F1 instance

1. Once you have an account, log in to the EC2 AWS Console:

    https://console.aws.amazon.com/ec2

    This should bring you to the EC2 dashboard (Elastic Compute).

    In the EC2 dashboard, select Launch Instance. From here you should be able to start your instance. 

## Additional setup

You may want to do some additional setup to allow you to VNC to your instance. You can also follow the instructions in [Setup XUP AWS Workshop](setup_xup_aws_workshop) to connect to your instance. 

### VNC server setup

When setting up an instance for the first time, you need to install vncserver software. 

#### Install VNC server
In a terminal, execute the following commands

```
   sudo yum install -y tigervnc-server
   sudo yum groupinstall -y "Server with GUI"
```

When installing vncserver, you will be prompted to set up a password that you will need later. 

### Start vncserver

Each time you start an instance, you will need to start vncserver 


```
   vncserver -geometry 1920x1080
```

You can choose your preferred geometry (screensize)

You should see a status message in the terminal once *vncserver* has started. 

Take note of the number after the “:”

In this case, 1. This is the port the VNC viewer will connect to on the VNC server and needs to be specified as a two digit number below: 01.

Connect to AWS instance from VNC viewer
From VNC viewer, specify the IP address of your AWS instance, followed by the VNC port number (as identified above), in this case :1

When prompted, enter the VNC server password set up earlier.

You should then be connected to the AWS instance.

### Verify XRT and SDx tools

Open a terminal and verify the Xilinx SDx tools have been preinstalled and are on the path:

```
   which sdx
```

Note that the XRT tools are installed (/opt/xilinx/xrt) but are not included on the path by default. 

```
   sudo chmod 777 /opt/xilinx/xrt/setup.sh
```

Execute the following to add `source /opt/xilinx/xrt/setup.sh` to ~/.bashrc (or manually edit ~/.bashrc and add the line).

```
   echo "source /opt/xilinx/xrt/setup.sh" >> ~/.bashrc
```

AWS_FPGA_REPO_DIR is defined in /etc/profile.d/aws-f1.sh 


```
   cd ~/src/project_data
   git clone https://github.com/aws/aws-fpga
   cd $AWS_FPGA_REPO_DIR                                         
   source sdaccel_setup.sh
   echo "export PLATFORM_REPO_PATHS=/home/centos/src/project_data/aws-fpga/SDAccel/aws_platform/xilinx_aws-vu9p-f1-04261818_dynamic_5_0" >> ~/.bashrc
    
```

For more details see:

https://github.com/aws/aws-fpga/blob/master/SDAccel/README.md


