simulation of the scheduler portion of a memory
controller capable serving a 12-core 4.8 GHz processor employing a single 16GB PC5-
38400 DIMM. The system uses a relaxed consistency (XC) model. The controller uses
the two channels of the DIMM independently. The DIMM is constructed with memory
chips organized as x8 devices with a 1KB page size and 40-39-39-76 timing. These
devices have 8 bank groups of 4 banks each. The DIMM uses 1N mode for commands
requiring two cycles. There is no system-level ECC.

## Project File Structure

```
ddr5_command.c
headers.h
trace.text
```
# Simulation and Debugging Commands
## To Create .exe file
```bash
"gcc ddr5_command.c -o ddr5_command"
```
## To execute the .exe file
```bash
"./ddr5_command"
```
## To give and generate custom input and output file
```bash
 "./ddr5_command 'input_file' 'output_file'"
```

## Key Features
### Timing constraints
Your memory controller simulation must correctly schedule DRAM commands to comply
with the following DDR-5 timing values. Unless otherwise indicated, all values are given
in DRAM clock cycles.
Parameter Value
tRC 115
tRAS 76
tRRD_L 12
tRRD_S 8
tRP 39
tRFC 295ns
CWL (tCWD) 38
tCAS (CL) 40
tRCD 39
tWR 30
tRTP 18
tCCD_L 12
tCCD_S 8
tCCD_L_WR 48
tCCD_S_WR 8
tBURST 8
tCCD_L_RTW 16
tCCD_S_RTW 16
tCCD_L_WTR 70
tCCD_S_WTR 52


---

This project was undertaken as part of the **ECE585 course** at **Portland State University** under the guidance of **Prof. Mark G. Faust**.
