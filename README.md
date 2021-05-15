# PPTLCheck+

PPTLCheck+ is a distributed network-based runtime verification tool. 

The input of PPTLCheck+ is the monitored Xd-C program and the desired property specified by a PPTL formula. 

PPTLCheck+ consists of three modules: a translator used to convert an Xd-C program into an MSVL program, a compiler employed to compile an MSVL program into executable code, and a verifier to complete the verification task, which is contained in the folder "/tools".

# Introduction of each folder

## The folder "Examples" 

It contains the conducted experiments in Section 5 in the submitted paper, in the folder:

* The subfolder "Efficiency_Evaluation_Examples" contains Xd-C and corresponding MSVL programs utilized to achieve the Efficiency Evaluation in Section 5.1. In total, there are 35 programs.
* The subfolder "Effectiveness_Evaluation_Examples" contains Xd-C and corresponding MSVL programs utilized to achieve the Effectiveness Evaluation in Section 5.2. In total, there are 10 programs.
* The subfolder "Scalability_Evaluation_Examples" contains an MSVL program, "gzip+.m", utilized to achieve the Scalability Evaluation in Section 5.3.
* The subfolder "Performance_Comparison_Examples" contains 10 MSVL programs utilized to achieve the Performance Comparison in Section 5.4.
* The subfolder "Examples_Input/input" contains the program inputs for the programs in the folders "Effectiveness_Evaluation_Examples", "Scalability_Evaluation_Examples" and "Performance_Comparison_Examples".

## The folder "tools" 

It contains the necessary environment and modules to accomplish our tool PPTLCheck+, in the folder:

* The subfolder "LLVM" contains the necessary files to build the LLVM environment. It should be copied to C:\ .
* The compressed file "C2M.7z" contains the translator to translate Xd-C programs to MSVL programs.
* The subfolder "distributedMachines" contains the sub-tool implemented in each distributed machine (M1-Mn), which is employed to accomplish the verification task for each segment.
* The compressed file "DNRV-MMRV.7z" contains the sub-tool in machine M0 to accomplish the program execution, verification tasks distribution and verification results collection.

# Building and running the project

The project is built and run in the Windows platform. For the compressed files, it is needed to decompress them at first.

## The tool C2M

It is not neccssary to build it. Instead, it can be executed directly.

(1) Open command prompt and enter the file folder where C2M.exe is located;

(2) Type C2M.exe D:\inputfile.c, where D:\inputfile.c is the file path of the input file inputfile.c;

(3) The translated MSVL program result.txt is generated at the folder which contains C2M.exe.

## The sub-tool in distributed machines M1-Mn

(1) Install the microsoft vs 2013;

(2) Build the project in the folder "distributedMachines".

(3) Run the project, then it will be listening the port to receive socket information, as the following picture. The first line, 0, means that this is a release version (While 1 means this is a debug version). The second line, 8003, is the port number used to socket communication between M0 and M1-Mn.

![360截图17100813153429](https://user-images.githubusercontent.com/11765210/118350542-e9a53f00-b589-11eb-8ca4-92fdd06dde4a.png)

## The sub-tool in machine M0

(1) Copy the file folder LLVM to C:\ in machine M0;

(2) Decompress the file "DNRV-MMRV.7z" and build the project;

(3) The configuration information is written in the file /MSV/Info.txt. An example is shown as follows.

![360截图17100813153429](https://user-images.githubusercontent.com/11765210/118353353-6b9c6480-b598-11eb-96c7-3fbca04052e5.png)

* In the first line, 1 means the distributed network-based runtime verification (DNRV) is utilized, while 0 means the multi-core machine-based runtime verification (MMRV) is utilized. Since this paper presents the DNRV, the number in this line is set as 1.
* The second line should be 0, meaning this is a release version. While 1 means this is a debug version.
* The third line is the port number used to socket communication between M0 and M1-Mn.
* The fourth line is the number of distributed machines.
* The fifth line is the number of states in each segment, which is 500000 in our paper.
* From the sixth line, the IP addresses of distributed machines should be written.

(4) The monitored MSVL program and the desired property are written in the file "\_MSVInput.m". In more detail, the desired property is in front of the monitored MSVL program. The following picture shows the example CTCS-3. Each example contains four kinds of properties, including the liveness, safety, weak fairness and periodically repeated properties. Each property is written in the format </ ... />. Since each time, only one property can be verified, the other three properties are commented our by /* ... */.

![360截图17100813153429](https://user-images.githubusercontent.com/11765210/118352204-ad2a1100-b592-11eb-90be-569dec82fb38.png)

(5) Run the project and the following result can be obtained. 

![360截图17100813153429](https://user-images.githubusercontent.com/11765210/118353300-38f26c00-b598-11eb-91c7-bb2826969a3e.png)

The left picture shows the result produced by machine M0, including the final verification result and the verification time, while the right picture shows the result produced by machines M1-Mn, including some socket communiction information and intermediate results.
