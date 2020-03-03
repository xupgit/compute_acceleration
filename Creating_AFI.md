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

# Creating an Amazon FPGA Image (AFI)

This document guides you through the steps to create an AWS Amazon FPGA Image (AFI) which can be run AWS EC2 F1 instance to verify that the deign works in hardware. It assumes that a full system (SDx project) is built which consists of an *host* application (.exe) and an FPGA binary file (.xclbin). 

### Create an AFI

To execute the application on F1, the following files are needed:

- Host application (exe)
- Amazon FPGA Image (awsxclbin)

The awsxclbin is an Amazon specific version of the FPGA binary file (xclbin) produced by the SDx software.

The awsxclbin can be created by running the *create\_sdaccel\_afi.sh* script which is included in the aws-fpga Git repository. 

The script can be found in the following location in the aws-fpga repository:

```
./aws-fpga/SDAccel/tools/create_sdaccel_afi.sh
```

Before running the commands below, make sure the SDx setup script has been sourced (the following command assumes the aws-fpga Git repository is cloned to the user home area)

```
source ~/aws-fpga/sdaccel_setup.sh
```

* Create an AFI by running the create\_sdaccel\_afi.sh script and wait for the completion of the AFI creation process

```
$SDAccel/tools/create_sdaccel_afi.sh –xclbin=<filename>.xclbin –s3_bucket=<bucket-name> -s3_dcp_key=<dcp-folder-name> -s3_logs_key=<logs-folder-name>
```
In the above command, set the *xclbin* <filename>; the Amazon S3 &lt;bucket-name&gt;, &lt;dcp-folder-name&gt;, and &lt;logs-folder-name&gt; with the names you had given when running CLI script.  You can choose any valid folder name for the dcp and logs folder. The Amazon S3 bucket name should match an S3 bucket you have set up. 

Learn more about setting up S3 buckets at [https://github.com/aws/aws-fpga/blob/master/SDAccel/docs/Setup_AWS_CLI_and_S3_Bucket.md](https://github.com/aws/aws-fpga/blob/master/SDAccel/docs/Setup_AWS_CLI_and_S3_Bucket.md)  

The create\_sdaccel\_afi.sh script does the following:

- Starts a background process to create the AFI
- Generates a \_afi\_id.txt which contains the FPGA Image Identifier (or AFI ID) and Global FPGA Image Identifier (or AGFI ID) of the generated AFIs
- Creates the \*.awsxclbin AWS FPGA binary file which is passed to the host application to determine which AFI should be loaded to the FPGA.
- Uploads the xclbin to the AWS cloud for processing.
## Check the AFI status

The AFI will become available after some time in the AWS cloud and can then be used to program the FPGA in an AWS EC2 F1 instance. To check the AFI status, the AFI ID is required. 

- In the directory the *create_sdaccel_afi.sh* script was run, enter the following command to find the AFI ID  
   
   ```
   cat *afi_id.txt
   ```
* Enter the **describe-fpga-images** API command to check the status of the AFI generation process:

```
   aws ec2 describe-fpga-images --fpga-image-ids <AFI ID>
```
* For example, 

```
aws ec2 describe-fpga-images --fpga-image-ids afi-0b9167434a1c74ba9
```

Note: When AFI creation is in progress, the *State* will be pending. When the AFI creation is finished, the output should show *available*:

```
   ...
   "State": {
       "Code": "available"
   },
   
   ...
```

Wait until the AFI becomes available before proceeding to execute on the F1 instance.

