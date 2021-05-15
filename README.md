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

* The subfolder "LLVM" contains the necessary files to build the LLVM environment. It should be copied to C:\.
* The compressed file "C2M.7z" contains the translator to translate Xd-C programs to MSVL programs.
* The subfolder "distributedMachines" contains the sub-tool implemented in each distributed machine (M1-Mn), which is employed to accomplish the verification task for each segment.
* The compressed file "DNRV-MMRV.7z" contains the sub-tool in machine M0 to accomplish the program execution, verification tasks distribution and verification results collection.

# Building and running the project

## The tool C2M

(1) For Windows, open command prompt and enter the file folder where C2M.exe is located;

(2) Type C2M.exe D:\inputfile.c, where D:\inputfile.c is the file path of the input file inputfile.c;

(3) The translated MSVL program result.txt is generated at the folder which contains C2M.exe.

## The sub-tool in distributed machines M1-Mn

(1) Install the microsoft vs 2013;

(2) Build the project in the folder "distributedMachines".

(3) Copy the file folder LLVM to C:\ in machine M0
